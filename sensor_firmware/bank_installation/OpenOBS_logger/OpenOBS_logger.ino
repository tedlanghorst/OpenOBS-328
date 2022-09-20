#include <Wire.h>               //standard library
#include <SPI.h>                //standard library
#include <EEPROM.h>             //standard library
#include "SerialTransfer.h"     //Version 3.1.2 https://github.com/PowerBroker2/SerialTransfer
#include <SdFat.h>              //Version 2.0.7 https://github.com/greiman/SdFat //uses 908 bytes of memory
#include <DS3231.h>             //Updated Jan 2, 2017 https://github.com/kinasmith/DS3231
#include <IridiumSBD.h> // Click here to get the library: http://librarymanager/All#IridiumSBDI2C


//firmware data
const DateTime uploadDT = DateTime((__DATE__),(__TIME__)); //saves compile time into progmem
const char contactInfo[] PROGMEM = "tlang@live.unc.edu"; 
const char dataColumnLabels[] PROGMEM = "time,ambient,turbidity,pressure,temperature";
uint16_t serialNumber; 

//connected pins
#define pChipSelect 53       //chip select pin for SD card

//EEPROM addresses
#define SLEEP_ADDRESS 0
#define SN_ADDRESS 500
#define UPLOAD_TIME_ADDRESS 502

//communications vars
bool guiConnected = false;
const uint16_t COMMS_WAIT = 500;    //ms delay to try gui connection
const int MAX_CHAR = 60;            //max num character in messages
char messageBuffer[MAX_CHAR];       //buffer for sending and receiving comms

SerialTransfer myTransfer;

//data storage
typedef struct single_record_t {
  uint32_t logTime;
  uint16_t tuBackground;
  uint16_t tuReading; 
  uint32_t p;
  int16_t temp;
};
//max message is 340 bytes, but charged per 50 bytes.
#define N_RECORDS (int(50)/sizeof(single_record_t)) 
typedef union data_union_t{
 single_record_t records[N_RECORDS];
 byte serialPacket[sizeof(single_record_t)*N_RECORDS];
};
data_union_t data;
uint8_t recordCount = 0;

//time settings
bool clk_init = true; //assume true, check on startup.
long currentTime = 0;
long sleepDuration_seconds = 1;
long delayedStart_seconds = 0;
DateTime nextAlarm;
DS3231 rtc; //create RTC object

uint32_t lastRequestTime = 0;
uint16_t sendSize;

//SD vars
#define SPI_SPEED SD_SCK_MHZ(50)
char filename[] = "YYYYMMDD.TXT"; 
SdFat sd;
SdFile file;

//Iridium
#define DIAGNOSTICS false // Change this to see diagnostics
IridiumSBD modem(Serial3); 
int err;

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(50);
  Wire.begin();
  EEPROM.get(SN_ADDRESS, serialNumber);
  
  //Start serial port connected to the sensor.
  Serial1.begin(38400);
  myTransfer.begin(Serial1);

  //initialize the Iridium modem.
  bool iridium_init = startIridium();
  int signalQuality = getIridiumSignalQuality();
  
  /* With power switching between measurements, we need to know what kind of setup() this is.
   *  First, check if the firmware was updated.
   *  Next, check if the GUI connection forced a reset.
   *  If neither, we assume this is a power cycle during deployment and use stored settings.
   */
   
  //if firmware was updated, take those settings and time.
  uint32_t storedTime;
  EEPROM.get(UPLOAD_TIME_ADDRESS,storedTime);
  if(uploadDT.unixtime()!=storedTime){
    EEPROM.put(UPLOAD_TIME_ADDRESS,uploadDT.unixtime());
    EEPROM.put(SLEEP_ADDRESS,sleepDuration_seconds);
    Serial.println("Firmware updated");
    clk_init = rtc.begin(); //reset the rtc
    rtc.adjust(uploadDT);
  }  
  //otherwise check if the GUI is connected
  //send a startup message and wait a bit for an echo from the gui
  else {
    guiConnected = checkGuiConnection();
  }
  if (guiConnected == false){
    //if no contact from GUI, read last stored value
    EEPROM.get(SLEEP_ADDRESS,sleepDuration_seconds);
  }
  
  //intialize SD card
  bool sd_init = sd.begin(pChipSelect,SPI_SPEED);
  if(!sd_init) serialSend("SDINIT,0");
  
  //initialize the RTC
  if(!clk_init) serialSend("CLKINIT,0");

  if(!iridium_init) serialSend("IRIDIUMINIT,0");

  //check sensor status
//  if(!sensor_init) serialSend("SENSORINIT,0");

  //if we had any errors turn off battery power and stop program.
  //set another alarm to try again- intermittent issues shouldnt end entire deploy.
  //RTC errors likely are fatal though. Will it even wake if RTC fails?
  if(!sd_init | !clk_init | !iridium_init){
    nextAlarm = DateTime(rtc.now().unixtime() + sleepDuration_seconds);
    sensorSleep(nextAlarm);
  }

  //if we have established a connection to the java gui, 
  //send a ready message and wait for a settings response.
  //otherwise, use the settings from EEPROM.
  if(guiConnected){
    receiveGuiSettings();
  }

  if(delayedStart_seconds>0){
    nextAlarm = DateTime(currentTime + delayedStart_seconds);
    sensorSleep(nextAlarm);
  }
  
  updateFilename();
  sprintf(messageBuffer,"FILE,OPEN,%s\0",filename);
  serialSend(messageBuffer);
}


void loop()
{
  //Request data if it is the right time.
  if((millis() - lastRequestTime)>(sleepDuration_seconds*1000)){
    requestData();
    lastRequestTime = millis();
    delay(50); //allow time to respond.
  }

  //Receive data if it is available.
  if(myTransfer.available()){
    myTransfer.rxObj(data.records[recordCount]);
    data.records[recordCount].logTime = rtc.now().unixtime();
    writeDataToSD(data.records[recordCount]);
    recordCount += 1;
  }

  //if we have filled out transmit packet...
  if(recordCount == N_RECORDS){
    for(int i=0; i<N_RECORDS; i++){
      Serial.print("time:\t\t");
      Serial.println(data.records[i].logTime);
      Serial.print("background:\t");
      Serial.println(data.records[i].tuBackground);
      Serial.print("reading:\t");
      Serial.println(data.records[i].tuReading);
      Serial.print("pressure:\t");
      Serial.println(data.records[i].p);
      Serial.print("temperature:\t");
      Serial.println(data.records[i].temp);
    }
    /*
    Serial.println(F("Trying to send the message.  This might take several minutes."));
    err = modem.sendSBDBinary(data.serialPacket,sizeof(data));
    
    if (err != ISBD_SUCCESS){
      Serial.print(F("sendSBDText failed: error "));
      Serial.println(err);
      if (err == ISBD_SENDRECEIVE_TIMEOUT)
        Serial.println(F("Try again with a better view of the sky."));
    } 
    else {
      Serial.println(F("Hey, it worked!"));
    }

    // Clear the Mobile Originated message buffer
    Serial.println(F("Clearing the MO buffer."));
    err = modem.clearBuffers(ISBD_CLEAR_MO); // Clear MO buffer
    if (err != ISBD_SUCCESS){
      Serial.print(F("clearBuffers failed: error "));
      Serial.println(err);
    }

    */
    
    Serial.println();
    recordCount = 0; //clear our packet idx
    while(true){}; //for now, hang so we don't spam Iridium accidentally.
  }
}
