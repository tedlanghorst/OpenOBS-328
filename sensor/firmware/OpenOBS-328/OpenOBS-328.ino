#include <Wire.h>     //standard library
#include <SPI.h>      //standard library
#include <EEPROM.h>   //standard library
#include <SdFat.h>    //tested with Version 2.0.7 //uses 908 bytes of memory
#include "src/libs/DS3231/DS3231.h"
#include "src/libs/LowPower/LowPower.h"
#include "src/OpenOBS/Sensors.h"

static const uint8_t MS5803_VERSION = 0; //set to 0 for to disable
long sleepDuration_seconds = 0; 

//firmware data
const DateTime uploadDT = DateTime((__DATE__), (__TIME__)); //saves compile time into progmem
const char dataColumnLabels[] PROGMEM = "time,millis,A410,A435,A460,A485,A510,A535,A560,A585,A610,A645,A680,A705,A730,A760,A810,A860,A900,A940,B410,B435,B460,B485,B510,B535,B560,B585,B610,B645,B680,B705,B730,B760,B810,B860,B900,B940,pressure,water_temp,battery";
const char sensorVersion[] = "SENSOR,AS7265X";
uint16_t serialNumber;

//connected pins
#define pChipSelect 10              //chip select pin for SD card
#define pBatteryDivider A2

//EEPROM addresses
#define SLEEP_ADDR 0            //4 bytes. 0-3
#define SENSOR_SETTINGS_ADDR 4  //5 bytes. 4-8
#define SN_ADDR 500             //2 bytes. 500-501
#define UPLOAD_TIME_ADDR 502    //4 bytes. 502-505.

//gui communications vars
#define COMMS_TRY 3        //number of attemps for gui connection
#define MAX_CHAR 60           //max num character in messages
char messageBuffer[MAX_CHAR];       //buffer for sending and receiving comms
bool guiConnected = false;
bool newFirmware = false;

//data storage variables
struct {
  uint32_t timeSeconds;
  uint32_t timeMillis;
  uint32_t absPressure;
  float ambientLight[18]; // Array for 18 ambient channel values
  float backscatterLight[18]; // Array for 18 backscatter channel values
  int16_t waterTemp;
  uint16_t batteryVoltage;
} data; // Updated to include arrays for ambient and backscatter values

//initialization variables
union {
  byte b;
  struct {
    bool sd: 1;
    bool clk: 1;
    bool turb: 1;
    bool pt: 1;
  } module;
} startup;

//time settings
long currentTime = 0;
long delayedStart_seconds = 0;
DateTime nextAlarm;
DS3231 RTC; //create RTC object

//SD vars
#define SPI_SPEED SD_SCK_MHZ(50)
char filename[] = "YYYYMMDD.TXT";
SdFat sd;
SdFile file;
bool fileIsOpen = false;

//Sensor vars
Sensors sensors = Sensors(SENSOR_SETTINGS_ADDR, MS5803_VERSION);
uint8_t measFlags = 0b00001101;

void setup() {
  Serial.begin(250000);
  Serial.setTimeout(50);
  Wire.begin();

  getSerialNumber();
  getDataLoggerSettings();
  checkModuleStartup();
  getSensorSettings();

  if (delayedStart_seconds > 0) {
    sensorSleep(RTC.now().unixtime(), delayedStart_seconds);
  }
  
  updateFilename();
  Serial.print("HEADERS,");
  Serial.println((__FlashStringHelper*)dataColumnLabels);
}


void loop()
{  
  // Put new data into the data struct.
  data.timeSeconds = RTC.now().unixtime();
  data.timeMillis = millis();
  data.batteryVoltage = analogRead(pBatteryDivider);
  sensors.getReadings(
    data.ambientLight, 
    data.backscatterLight, 
    data.absPressure, 
    data.waterTemp);

   writeDataToSerial();
   writeDataToSD();

//  data.toString(messageBuffer);
//  writeToSD(messageBuffer);
//  serialSend(messageBuffer);
//  
//  if (sleepDuration_seconds>0) {
//    sensorSleep(data.timeSeconds, sleepDuration_seconds);
//  }
  
}

void getSerialNumber(){
  EEPROM.get(SN_ADDR, serialNumber);
  //Check if SN has been changed from the default 0xFFFF.
  //If it has not, then loop through asking for a new one.
  while (serialNumber == 0xFFFF || serialNumber == 0){
    Serial.println(F("Missing serial number. Enter a valid SN [1-65534]:"));
    while(Serial.available()==0){}; //wait for input
    uint16_t tmp_SN = Serial.parseInt();
    if (tmp_SN==0 || tmp_SN ==0xFFFF){
      Serial.println(F("Invalid SN"));
    } 
    else {
      EEPROM.put(SN_ADDR,tmp_SN);
      EEPROM.get(SN_ADDR,serialNumber);
      Serial.print(F("SN successfully set to: "));
      Serial.println(serialNumber);
    }
  }
}

void getDataLoggerSettings(){
  /* With power switching between measurements, we need to know what kind of setup() this is.
     First, check if the firmware was updated.
     Next, check if the GUI connection forced a reset.
     If neither, we assume this is a power cycle during deployment and use stored settings.
  */
  
  //if firmware was updated, take those settings and time.
  uint32_t storedTime;
  EEPROM.get(UPLOAD_TIME_ADDR, storedTime);
  if (uploadDT.unixtime() != storedTime) {
    newFirmware = true;
    startup.module.clk = RTC.begin(); //reset the RTC
    RTC.adjust(uploadDT);
    
    EEPROM.put(UPLOAD_TIME_ADDR, uploadDT.unixtime());
    EEPROM.put(SLEEP_ADDR, sleepDuration_seconds);
    Serial.println("Firmware updated");
  }
  //otherwise check if the GUI is connected
  //send a startup message and wait a bit for an echo from the gui
  else if (checkGuiConnection()){
    receiveGuiSettings();
  }
  else {
    //if no contact from GUI, read last stored value
    EEPROM.get(SLEEP_ADDR, sleepDuration_seconds);
    startup.module.clk = true; //assume true if logger woke up.
  }
  if(sleepDuration_seconds < 5){
    sleepDuration_seconds = 0;
  }
}


void checkModuleStartup(){
  //intialize & check all the modules
  startup.module.sd = sd.begin(pChipSelect, SPI_SPEED);
  if (!startup.module.sd) serialSend("SDINIT,0");
  
  //Evaluated in getDataLoggerSettings()
  if (!startup.module.clk) serialSend("CLKINIT,0");

  bool turb_temp, pt_temp;
  sensors.begin(turb_temp, pt_temp);
  startup.module.turb = turb_temp;
  startup.module.pt = pt_temp;
  if (!startup.module.turb) serialSend("TURBINIT,0");
  if (!startup.module.pt) serialSend("PTINIT,0");

  //if we had any errors turn off battery power and stop program.
  //set another alarm to try again- intermittent issues shouldnt end entire deploy.
  //RTC errors likely are fatal though. Will it even wake if RTC fails?
  if (!(startup.b == 0b00001111)) {
    Serial.println(F("$Startup failed*66"));

    if (sleepDuration_seconds>5){
      sensorSleep(RTC.now().unixtime(), sleepDuration_seconds);
    } else {
      while(true); //wait forever.
    }
  }
}


void getSensorSettings(){
  //if we have established a connection to the gui,
  //send a ready message and wait for a settings response.
  if (newFirmware || guiConnected){
    sensors.setMeasurementFlags(measFlags);
    // TODO
//    sensors.setBackscatterCurrent(iredCurrent/10);
  } else {
    sensors.loadSettings();
  }
}
