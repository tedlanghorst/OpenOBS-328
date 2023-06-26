#include <Wire.h>     //standard library
#include <SPI.h>      //standard library
#include <EEPROM.h>   //standard library
#include <SdFat.h>    //tested with Version 2.0.7 //uses 908 bytes of memory
#include "src/libs/DS3231/DS3231.h"
#include "src/libs/Adafruit_VCNL4010/Adafruit_VCNL4010.h"
#include "src/libs/LowPower/LowPower.h"
#include "src/libs/MS5803/MS5803.h" 

// Likely variables to change
#define MS5803_VERSION 5 //comment or remove if you aren't using the pressure sensor
long sleepDuration_seconds = 0; 
const char contactInfo[] PROGMEM = "If found, please contact tlang@live.unc.edu";
//

//firmware data
const DateTime uploadDT = DateTime((__DATE__), (__TIME__)); //saves compile time into progmem
const char dataColumnLabels[] PROGMEM = "time,ambient_light,backscatter,pressure,water_temp,battery";
uint16_t serialNumber;

//connected pins
#define pChipSelect 10              //chip select pin for SD card
#define pBatteryDivider A2

//EEPROM addresses
#define SLEEP_ADDRESS 0
#define SN_ADDRESS 500
#define UPLOAD_TIME_ADDRESS 502

//gui communications vars
#define COMMS_TRY 3        //number of attemps for gui connection
#define MAX_CHAR 60            //max num character in messages
char messageBuffer[MAX_CHAR];       //buffer for sending and receiving comms
bool guiConnected = false;

//sensors
Adafruit_VCNL4010 vcnl;
#ifdef MS5803_VERSION
  MS_5803 pressure_sensor = MS_5803(MS5803_VERSION, 0x76, 4096);
#endif

//data storage variables
struct {
  uint32_t logTime;
  uint32_t abs_P;
  uint16_t tuAmbient;
  uint16_t tuBackscatter;
  int16_t water_temp;
  uint16_t battery;
} data; //16 bytes

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
  if(sleepDuration_seconds < 5){
    sleepDuration_seconds = 0;
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
  if (!startup.module.sd) serialSend("SDINIT,0");

  if (!startup.module.clk) serialSend("CLKINIT,0");

  startup.module.turb = vcnl.begin();
  vcnl.setLEDcurrent(5);
  if (!startup.module.turb) serialSend("TURBINIT,0");

  //initialize the pressure sensor
  #ifdef MS5803_VERSION
    startup.module.pt = pressure_sensor.initializeMS_5803();
    if (!startup.module.pt) serialSend("PTINIT,0");
  #else
    startup.module.pt = true;
  #endif

  //if we had any errors turn off battery power and stop program.
  //set another alarm to try again- intermittent issues shouldnt end entire deploy.
  //RTC errors likely are fatal though. Will it even wake if RTC fails?
  if (!(startup.b == 0b00001111)) {
    Serial.println(F("$Startup failed*66"));
    nextAlarm = DateTime(RTC.now().unixtime() + sleepDuration_seconds);
    sensorSleep(nextAlarm);
  }

  //if we have established a connection to the gui,
  //send a ready message and wait for a settings response.
  //otherwise, use the settings from EEPROM.
  if (guiConnected) {
    receiveGuiSettings();
  }

  if (delayedStart_seconds > 0) {
    nextAlarm = DateTime(currentTime + delayedStart_seconds);
    RTC.enableAlarm(nextAlarm);
    setBBSQW(); //enable battery-backed alarm
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
  data.tuAmbient = vcnl.readAmbient();
  data.tuBackscatter = vcnl.readProximity();
  data.battery = analogRead(pBatteryDivider);
  #ifdef MS5803_VERSION
    pressure_sensor.readSensor();
    data.abs_P = pressure_sensor.getPressure(); //bar*10^-5
    data.water_temp = pressure_sensor.getTemperature(); //C*10^-2
  #endif

  sprintf(messageBuffer, "%lu,%u,%u,%lu,%i,%u", data.logTime, data.tuAmbient, data.tuBackscatter, data.abs_P, data.water_temp, data.battery);
  writeDataToSD();

  serialSend(messageBuffer);

  //ensure a margin for the next alarm before shutting down.
  if ((long(nextAlarm.unixtime() - RTC.now().unixtime())) > 3) {
    sensorSleep(nextAlarm);
  }
  else {
    Serial.flush();
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_ON);
    LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_ON);
  }
}
