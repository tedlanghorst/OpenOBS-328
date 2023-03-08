/* TODO

*/

#include <Wire.h>     //standard library
#include <SPI.h>      //standard library
#include <EEPROM.h>   //standard library
#include <SdFat.h>    //tested with Version 2.0.7 //uses 908 bytes of memory
#include "src/libs/DS3231/DS3231.h"
#include "src/libs/Adafruit_VCNL4010/Adafruit_VCNL4010.h"
#include "src/libs/MS5803_14/MS5803_14.h" 
#include "src/libs/LowPower/LowPower.h"


//firmware data
const DateTime uploadDT = DateTime((__DATE__), (__TIME__)); //saves compile time into progmem
const char contactInfo[] PROGMEM = "If found, please contact tlang@live.unc.edu";
const char dataColumnLabels[] PROGMEM = "time,ambient_light,backscatter,pressure,water_temp,battery";
uint16_t serialNumber;

//connected pins
#define pChipSelect 10              //chip select pin for SD card

//EEPROM addresses
#define SLEEP_ADDRESS 0
#define SN_ADDRESS 500
#define UPLOAD_TIME_ADDRESS 502

//gui communications vars
bool guiConnected = false;
const uint8_t COMMS_TRY = 3;        //number of attemps for gui connection
const int MAX_CHAR = 60;            //max num character in messages
char messageBuffer[MAX_CHAR];       //buffer for sending and receiving comms

//sensors
Adafruit_VCNL4010 vcnl;
MS_5803 pressure_sensor = MS_5803(0x76, 4096);

//data storage variables
typedef struct single_record_t {
  uint32_t logTime;
  uint32_t abs_P;
  uint16_t tuAmbient;
  uint16_t tuBackscatter;
  int16_t water_temp;
  uint16_t battery;
}; //16 bytes
single_record_t data;

//initialization variable
typedef struct module_t {
  bool sd: 1;
  bool clk: 1;
  bool turb: 1;
  bool pt: 1;
};
typedef union startup_t {
  module_t module;
  byte b;
};
startup_t startup;

//time settings
long currentTime = 0;
long sleepDuration_seconds = 10;
long delayedStart_seconds = 0;
DateTime nextAlarm;
DS3231 RTC; //create RTC object

uint32_t lastRequestTime = 0;

//SD vars
#define SPI_SPEED SD_SCK_MHZ(50)
char filename[] = "YYYYMMDD.TXT";
SdFat sd;
SdFile file;


void setup() {
  Serial.begin(250000);
  Serial.setTimeout(50);
  Wire.begin();
  EEPROM.get(SN_ADDRESS, serialNumber);

  /* With power switching between measurements, we need to know what kind of setup() this is.
      First, check if the firmware was updated.
      Next, check if the GUI connection forced a reset.
      If neither, we assume this is a power cycle during deployment and use stored settings.
  */
  //if firmware was updated, take those settings and time.
  uint32_t storedTime;
  EEPROM.get(UPLOAD_TIME_ADDRESS, storedTime);
  if (uploadDT.unixtime() != storedTime) {
    EEPROM.put(UPLOAD_TIME_ADDRESS, uploadDT.unixtime());
    EEPROM.put(SLEEP_ADDRESS, sleepDuration_seconds);
    Serial.println("Firmware updated");
    startup.module.clk = RTC.begin(); //reset the RTC
    RTC.adjust(uploadDT);
  }
  //otherwise check if the GUI is connected
  //send a startup message and wait a bit for an echo from the gui
  else if (checkGuiConnection());
  else {
    //if no contact from GUI, read last stored value
    EEPROM.get(SLEEP_ADDRESS, sleepDuration_seconds);
    startup.module.clk = true; //assume true if logger woke up.
  }

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
      EEPROM.put(SN_ADDRESS,tmp_SN);
      EEPROM.get(SN_ADDRESS,serialNumber);
      Serial.print(F("SN successfully set to: "));
      Serial.println(serialNumber);
    }
  }

  //intialize & check all the modules
  startup.module.sd = sd.begin(pChipSelect, SPI_SPEED);
  sprintf(messageBuffer,"SDINIT,%u",startup.module.sd);
  serialSend(messageBuffer);

  sprintf(messageBuffer,"CLKINIT,%u",startup.module.clk);
  serialSend(messageBuffer);

  startup.module.turb = vcnl.begin();
  vcnl.setLEDcurrent(5);
  vcnl.setFrequency(VCNL4010_250);
  sprintf(messageBuffer,"TURBINIT,%u",startup.module.turb);
  serialSend(messageBuffer);

  //initialize the pressure sensor
  startup.module.pt = pressure_sensor.initializeMS_5803(false);
  sprintf(messageBuffer,"PTINIT,%u",startup.module.pt);
  serialSend(messageBuffer);


  //if we had any errors turn off battery power and stop program.
  //set another alarm to try again- intermittent issues shouldnt end entire deploy.
  //RTC errors likely are fatal though. Will it even wake if RTC fails?
  if (!(startup.b == 0b00001111)) {
        Serial.println(F("$Startup failed*66"));
        nextAlarm = DateTime(RTC.now().unixtime() + sleepDuration_seconds);
        sensorSleep(nextAlarm);
  }

  //if we have established a connection to the java gui,
  //send a ready message and wait for a settings response.
  //otherwise, use the settings from EEPROM.
  if (guiConnected) {
    receiveGuiSettings();
  }

  if (delayedStart_seconds > 0) {
    nextAlarm = DateTime(currentTime + delayedStart_seconds);
    sensorSleep(nextAlarm);
  }
  
  updateFilename();
  sprintf(messageBuffer, "FILE,OPEN,%s\0", filename);
  serialSend(messageBuffer);
}


void loop()
{ 
  //set the next alarm right away. Check it hasn't passed later.
  nextAlarm = DateTime(RTC.now().unixtime() + sleepDuration_seconds);
  RTC.enableAlarm(nextAlarm);
  setBBSQW(); //enable battery-backed alarm

  //Replace data fields with new sensor data.
  data.logTime = RTC.now().unixtime();
  pressure_sensor.readSensor();
  data.abs_P = pressure_sensor.pressure() * 10; //bar^10-4
  data.water_temp = pressure_sensor.temperature() * 100; //C^10-2
  data.tuAmbient = vcnl.readAmbient();
  data.tuBackscatter = vcnl.readProximity();
  data.battery = analogRead(A2);

  sprintf(messageBuffer, "%lu,%u,%u,%lu,%i,%u", data.logTime, data.tuAmbient, data.tuBackscatter, data.abs_P, data.water_temp, data.battery);

  writeDataToSD();

  serialSend(messageBuffer);

  //ensure a 5 second margin for the next alarm before shutting down.
  if (nextAlarm.unixtime() - RTC.now().unixtime() > 5) {
    sensorSleep(nextAlarm);
  }
  else {
    Serial.flush();
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_ON);
    LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_ON);
  }
}
