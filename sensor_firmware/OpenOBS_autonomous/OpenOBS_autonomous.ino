/* TODO

*/

#include <Wire.h>               //standard library
#include <SPI.h>                //standard library
#include <EEPROM.h>             //standard library
#include <SdFat.h>              //Version 2.0.7 https://github.com/greiman/SdFat //uses 908 bytes of memory
#include <DS3231.h>             //Updated Jan 2, 2017 https://github.com/kinasmith/DS3231
#include "Adafruit_VCNL4010.h"
#include <MS5803_14.h>          // https://github.com/millerlp/MS5803_14
#include <LowPower.h>


//firmware data
const DateTime uploadDT = DateTime((__DATE__), (__TIME__)); //saves compile time into progmem
const char contactInfo[] PROGMEM = "If found, please contact tlang@live.unc.edu";
const char dataColumnLabels[] PROGMEM = "time,pressure,ambient_light,backscatter,water_temp,battery";
uint16_t serialNumber;

//connected pins
#define pChipSelect 10              //chip select pin for SD card

//EEPROM addresses
#define SLEEP_ADDRESS 0
#define SN_ADDRESS 500
#define UPLOAD_TIME_ADDRESS 502

//gui communications vars
bool guiConnected = false;
const uint16_t COMMS_WAIT = 300;    //ms delay to try gui connection
const int MAX_CHAR = 60;            //max num character in messages
char messageBuffer[MAX_CHAR];       //buffer for sending and receiving comms

//sensors
Adafruit_VCNL4010 vcnl;
MS_5803 pressure_sensor = MS_5803(4096);

//data storage variables
typedef struct single_record_t {
  uint32_t logTime;
  uint32_t hydro_p;
  uint16_t tuBackground;
  uint16_t tuReading;
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
long sleepDuration_seconds = 0;
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
  Serial.begin(38400);
  Serial.setTimeout(50);
  Wire.begin();
  EEPROM.get(SN_ADDRESS, serialNumber);

  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);

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

  //intialize & check all the modules
  startup.module.sd = sd.begin(pChipSelect, SPI_SPEED);
  if (!startup.module.sd) serialSend("SDINIT,0");

  if (!startup.module.clk) serialSend("CLKINIT,0");

  startup.module.turb = vcnl.begin();
  vcnl.setLEDcurrent(5);
  vcnl.setFrequency(VCNL4010_250);
  if (!startup.module.turb) serialSend("TURBINIT,0");

  //initialize the pressure sensor
  startup.module.pt = pressure_sensor.initializeMS_5803(false);
  if (!startup.module.pt) serialSend("PTINIT,0");


  //if we had any errors turn off battery power and stop program.
  //set another alarm to try again- intermittent issues shouldnt end entire deploy.
  //RTC errors likely are fatal though. Will it even wake if RTC fails?
  if (!(startup.b && 0xFF)) {
    //    nextAlarm = DateTime(RTC.now().unixtime() + sleepDuration_seconds);
    //    sensorSleep(nextAlarm);
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
  data.hydro_p = pressure_sensor.pressure()*10; //bar^10-4
  data.water_temp = pressure_sensor.temperature()*100; //C^10-2
  data.tuBackground = vcnl.readAmbient();
  data.tuReading = vcnl.readProximity();
  data.battery = analogRead(A2);

  sprintf(messageBuffer, "%u,%u,%u,%u,%i,%u", data.logTime, data.tuBackground, data.tuReading, data.hydro_p, data.water_temp, data.battery);
    
  writeDataToSD();

  Serial.println(messageBuffer);

  //ensure a 5 second margin for the next alarm before shutting down.
  if (sleepDuration_seconds > 5) {
    sensorSleep(nextAlarm);
  }
  else {
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_ON);
  }
}
