/* TODO
 * Troubleshoot the time settings. Dates from RTC are wrong. Firmware date correct.
 * Check sensor initialization with message exchange.
 * Sleep cycling
 *  full shutdown like original?
 *  soft shutdown is likely a lot easier to manage
 * Figure out optimal batching of iridium messages
 *  Maximum time between messages?
 *  Sending less often might save money (e.g. 50 bytes fits 2.5 messages)
 * Battery power
 *  Test solar setup from Adafruit
 *  do we need to bother with full shutdown like autonomous?
 * 
 */

#include <Wire.h>               //standard library
#include <SPI.h>                //standard library
#include <EEPROM.h>             //standard library
#include "SerialTransfer.h"     //Version 3.1.2 https://github.com/PowerBroker2/SerialTransfer
#include <SdFat.h>              //Version 2.0.7 https://github.com/greiman/SdFat //uses 908 bytes of memory
#include <DS3231.h>             //Updated Jan 2, 2017 https://github.com/kinasmith/DS3231
#include <MS5803_14.h>          // https://github.com/millerlp/MS5803_14
#include <IridiumSBD.h> // Click here to get the library: http://librarymanager/All#IridiumSBDI2C


//firmware data
const DateTime uploadDT = DateTime((__DATE__),(__TIME__)); //saves compile time into progmem
const char contactInfo[] PROGMEM = "If found, please contact tlang@live.unc.edu"; 
const char dataColumnLabels[] PROGMEM = "time,hydrostatic_pressure,barometric_pressure,ambient_light,scattered_light,water_temperature,air_temperature";
uint16_t serialNumber; 

//connected pins
#define pChipSelect 53       //chip select pin for SD card

//EEPROM addresses
#define SLEEP_ADDRESS 0
#define SN_ADDRESS 500
#define UPLOAD_TIME_ADDRESS 502

//gui communications vars
bool guiConnected = false;
const uint16_t COMMS_WAIT = 500;    //ms delay to try gui connection
const int MAX_CHAR = 60;            //max num character in messages
char messageBuffer[MAX_CHAR];       //buffer for sending and receiving comms

SerialTransfer myTransfer;
MS_5803 pressure_sensor = MS_5803(4096);

//data storage variables
typedef struct single_record_t {
  uint32_t logTime;
  uint32_t hydro_p;
  uint32_t baro_p;
  uint16_t tuBackground;
  uint16_t tuReading; 
  int16_t water_temp;
  int16_t air_temp;
}; //20 bytes
//max message is 340 bytes, but charged per 50 bytes.
#define N_RECORDS (int(50)/sizeof(single_record_t)) 
typedef union data_union_t{
 single_record_t records[N_RECORDS];
 byte serialPacket[sizeof(single_record_t)*N_RECORDS];
};
data_union_t data;
uint8_t recordCount = 0;

//initialization variable
typedef struct module_t {
  bool sd:1;
  bool clk:1;
  bool baro:1;
  bool iridium:1;
  byte sensor:2;
};
typedef union status_t {
  module_t module;
  byte b;
};
status_t status;
status.module.clk = true; //assume true, check on startup.

//time settings
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
int modemErr;

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(50);
  Wire.begin();
  EEPROM.get(SN_ADDRESS, serialNumber);
  
  //Start serial port connected to the sensor.
  Serial1.begin(38400);
  myTransfer.begin(Serial1);

  //initialize the Iridium modem.
  status.module.iridium = startIridium();
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
    status.module.clk = rtc.begin(); //reset the rtc
    rtc.adjust(uploadDT);
  }  
  //otherwise check if the GUI is connected
  //send a startup message and wait a bit for an echo from the gui
  else if (checkGuiConnection())
  else {
    //if no contact from GUI, read last stored value
    EEPROM.get(SLEEP_ADDRESS,sleepDuration_seconds);
  }
  
  //intialize SD card
  status.module.sd = sd.begin(pChipSelect,SPI_SPEED);
  if(!status.module.sd) serialSend("SDINIT,0");
  
  //initialize the RTC
  if(!status.module.clk) serialSend("CLKINIT,0");

  //initialize the pressure sensor
  status.module.baro = pressure_sensor.initializeMS_5803();
  if(!status.module.baro) serialSend("BAROINIT,0");

  if(!status.module.iridium) serialSend("IRIDIUMINIT,0");

//  check sensor status
  sensorRequest(1);
  delay(50); //give the sensor time to respond.
  if(myTransfer.available()) myTransfer.rxObj(status.module.sensor);
  if(status.module.sensor != 3) serialSend("SENSORINIT,0");

  //if we had any errors turn off battery power and stop program.
  //set another alarm to try again- intermittent issues shouldnt end entire deploy.
  //RTC errors likely are fatal though. Will it even wake if RTC fails?
  if(!(status.b && 0xFF)){
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
    sensorRequest(2);
    lastRequestTime = millis();
    delay(50); //allow time to respond.
  }

  //Receive data if it is available.
  if(myTransfer.available()){
    myTransfer.rxObj(data.records[recordCount]);
    //add data from logger
    data.records[recordCount].logTime = rtc.now().unixtime();
    pressure_sensor.readSensor();
    data.baro_p = pressure_sensor.pressure();
    data.air_temp = pressure_sensor.temperature(); //do we need atmospheric temperature?
    
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
    modemErr = modem.sendSBDBinary(data.serialPacket,sizeof(data));
    
    if (modemErr != ISBD_SUCCESS){
      Serial.print(F("sendSBDText failed: error "));
      Serial.println(modemErr);
      if (modemErr == ISBD_SENDRECEIVE_TIMEOUT)
        Serial.println(F("Try again with a better view of the sky."));
    } 
    else {
      Serial.println(F("Hey, it worked!"));
    }

    // Clear the Mobile Originated message buffer
    Serial.println(F("Clearing the MO buffer."));
    modemErr = modem.clearBuffers(ISBD_CLEAR_MO); // Clear MO buffer
    if (modemErr != ISBD_SUCCESS){
      Serial.print(F("clearBuffers failed: error "));
      Serial.println(modemErr);
    }

    */
    
    Serial.println();
    recordCount = 0; //clear our packet idx
    while(true){}; //for now, hang so we don't spam Iridium accidentally.
  }
}
