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
#include "LowPower.h"           
#include "SerialTransfer.h"     //Version 3.1.2 https://github.com/PowerBroker2/SerialTransfer
#include <SdFat.h>              //Version 2.0.7 https://github.com/greiman/SdFat //uses 908 bytes of memory
#include <DS3231.h>             //Updated Jan 2, 2017 https://github.com/kinasmith/DS3231
#include <IridiumSBD.h> // Click here to get the library: http://librarymanager/All#IridiumSBDI2C


//firmware data
const DateTime uploadDT = DateTime((__DATE__),(__TIME__)); //saves compile time into progmem
const char contactInfo[] PROGMEM = "If found, please contact tlang@live.unc.edu"; 
const char dataColumnLabels[] PROGMEM = "time,hydrostatic_pressure,ambient_light,scattered_light,water_temperature,battery_level";
uint16_t serialNumber; 

//connected pins
#define pChipSelect 53      
#define pRtcInterrupt 2
#define pSensorPower 4
#define pIridiumPower 5
#define pBatteryMonitor A0

//EEPROM addresses
#define SLEEP_ADDRESS 0
#define SN_ADDRESS 500
#define UPLOAD_TIME_ADDRESS 502

//gui communications vars
bool guiConnected = false;
const uint16_t COMMS_WAIT = 1000;    //ms delay to try gui connection
const int MAX_CHAR = 60;            //max num character in messages
char messageBuffer[MAX_CHAR];       //buffer for sending and receiving comms

SerialTransfer myTransfer;

//data storage variables
typedef struct single_record_t {
  uint32_t logTime;
  uint32_t hydro_p;
  uint16_t tuBackground;
  uint16_t tuReading; 
  int16_t water_temp;
}; //14 bytes
//max message is 340 bytes, but charged per 50 bytes.
#define N_RECORDS (int(50)/sizeof(single_record_t)) 
typedef union data_union_t{
  int16_t batteryLevel;
  single_record_t records[N_RECORDS];
  byte serialPacket[2 + sizeof(single_record_t)*N_RECORDS];
};
data_union_t data, data_failedPacket;
uint8_t recordCount = 0;
bool failedPacket = false;

//initialization variable
typedef struct module_t {
  bool sd:1;
  bool clk:1;
  bool iridium:1;
  byte sensor:2;
};
typedef union startup_t {
  module_t module;
  byte b;
};
startup_t startup;

//time settings
long currentTime = 0;
long sleepDuration_seconds = 3600;
long delayedStart_seconds = 0;
DateTime nextAlarm;
DS3231 RTC; //create RTC object

//serial transfer vars
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

//  pinMode(pRtcInterrupt, INPUT);
//  digitalWrite(pRtcInterrupt, HIGH);
  pinMode(pSensorPower,OUTPUT);
  pinMode(pIridiumPower,OUTPUT);


  //initialize the Iridium modem.
  startup.module.iridium = startIridium();
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
    startup.module.clk = RTC.begin(); //reset the RTC
    RTC.adjust(uploadDT);
  }  
  //otherwise check if the GUI is connected
  //send a startup message and wait a bit for an echo from the gui
  else if (checkGuiConnection());
  else {
    //if no contact from GUI, read last stored value
    EEPROM.get(SLEEP_ADDRESS,sleepDuration_seconds);
    startup.module.clk = true; //assume true if logger woke up.
  }
  
  //Initialize & check all the modules.
  startup.module.sd = sd.begin(pChipSelect,SPI_SPEED);
  if(!startup.module.sd) serialSend("SDINIT,0");
  if(!startup.module.clk) serialSend("CLKINIT,0");
  if(!startup.module.iridium) serialSend("IRIDIUMINIT,0");
  sensorWake();
  if(startup.module.sensor != 3) serialSend("SENSORINIT,0");

  //if we had any errors turn off battery power and stop program.
  //set another alarm to try again- intermittent issues shouldnt end entire deploy.
  //RTC errors likely are fatal though. Will it even wake if RTC fails?
  while(startup.b != 0b11111){ 
    nextAlarm = DateTime(RTC.now().unixtime() + sleepDuration_seconds);
    loggerSleep(nextAlarm);
    //Initialize & check all the modules.
    Serial.println(F("rechecking modules...."));
    startup.module.sd = sd.begin(pChipSelect,SPI_SPEED);
    if(!startup.module.sd) serialSend("SDINIT,0");
    if(!startup.module.clk) serialSend("CLKINIT,0");
    if(!startup.module.iridium) serialSend("IRIDIUMINIT,0");
    sensorWake();
    if(startup.module.sensor != 3) serialSend("SENSORINIT,0");
  }

  //if we have established a connection to the java gui, 
  //send a ready message and wait for a settings response.
  //otherwise, use the settings from EEPROM.
  if(guiConnected){
    receiveGuiSettings();
  }

  if(delayedStart_seconds>0){
    nextAlarm = DateTime(currentTime + delayedStart_seconds);
    loggerSleep(nextAlarm);
  }
}

void loop()
{ 
  nextAlarm = DateTime(RTC.now().unixtime() + sleepDuration_seconds);

  updateFilename();
  sprintf(messageBuffer,"FILE,OPEN,%s\0",filename);
  serialSend(messageBuffer);
  
  //Request data
  while(startup.module.sensor != 3) sensorWake();
  sensorRequest(2);

 //wait for data to be available
  long tStart = millis();
  while (millis() - tStart < COMMS_WAIT) {
    if(myTransfer.available()){
      myTransfer.rxObj(data.records[recordCount]);
      data.records[recordCount].logTime = RTC.now().unixtime();
      data.batteryLevel = analogRead(pBatteryMonitor);
      sensorSleep();
      writeDataToSD(data.records[recordCount]);
      recordCount += 1;
      break;
    }
  }

  //if we have filled out transmit packet...
  if(recordCount == N_RECORDS){
    Serial.println();
    for(int i=0; i<N_RECORDS; i++){
      Serial.print("time:\t\t");
      Serial.println(data.records[i].logTime);
      Serial.print("background:\t");
      Serial.println(data.records[i].tuBackground);
      Serial.print("reading:\t");
      Serial.println(data.records[i].tuReading);
      Serial.print("hydro p:\t");
      Serial.println(data.records[i].hydro_p);
      Serial.print("water temp:\t");
      Serial.println(data.records[i].water_temp); 
      Serial.println();
      Serial.flush();
    }

    int tries = 0;
    bool messageSent = false;
    digitalWrite(pIridiumPower,HIGH);
    while (!messageSent && tries<2){
      Serial.println(F("Trying to send the message.  This might take a minute."));
      //This could be more elegant. Currently only care if the current packet sends. 
      //If we fail 2 in a row the older will be overwritten (still on SD card).
      //Should also pack this stuff in a function, could handle the 2 sends more elegantly that way.
      if (failedPacket){
        //send the old data if we have some.
        modemErr = modem.sendSBDBinary(data_failedPacket.serialPacket,sizeof(data_failedPacket));
        if (modemErr == ISBD_SUCCESS){
          Serial.println(F("Previous failed packet sent!"));
          failedPacket = false;
        }
      }
      //send the current data packet.
      modemErr = modem.sendSBDBinary(data.serialPacket,sizeof(data));
      tries++;
      
      if (modemErr != ISBD_SUCCESS){
        Serial.print(F("sendSBDText failed: error "));
        Serial.println(modemErr);
        if (modemErr == ISBD_SENDRECEIVE_TIMEOUT)
          Serial.println(F("Try again with a better view of the sky."));
      } 
      else {
        Serial.println(F("Message sent!"));
        messageSent = true;
      }
  
      // Clear the Mobile Originated message buffer
      modemErr = modem.clearBuffers(ISBD_CLEAR_MO); // Clear MO buffer
      if (modemErr != ISBD_SUCCESS){
        Serial.print(F("clearBuffers failed: error "));
        Serial.println(modemErr);
      }
    
    Serial.println();
    recordCount = 0; //reset our packet idx
    }
    if (!messageSent){
      data_failedPacket = data; //store failed data, try next time.
      failedPacket = true;
    }
  }

  //ensure a 5 second margin for the next alarm before shutting down.
  //if the alarm we set during this wake has already passed, the OBS will never wake up.
  long timeUntilAlarm = nextAlarm.unixtime()-RTC.now().unixtime();
  if(timeUntilAlarm > 5){
    loggerSleep(nextAlarm);
  }
}
