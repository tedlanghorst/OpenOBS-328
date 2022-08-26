#include <Wire.h>               //standard library
#include <SoftwareSerial.h>
#include "SerialTransfer.h"
#include <MS5803_14.h>          // https://github.com/millerlp/MS5803_14

SoftwareSerial ArduinoMaster(3,4);
SerialTransfer myTransfer;

//pressure sensor
MS_5803 pressure_sensor = MS_5803(4096);

//data storage
typedef struct single_record_t {
  uint32_t logTime = 0;
  uint16_t tuBackground;
  uint16_t tuReading; 
  uint32_t p;
  int16_t temp;
};
single_record_t data;

byte request = 0;
uint16_t sendSize;

void setup()
{
  Serial.begin(115200);
  ArduinoMaster.begin(38400);
  myTransfer.begin(ArduinoMaster);

  //initialize the pressure sensor
  bool pressure_init = pressure_sensor.initializeMS_5803();
  if(!pressure_init){
    /*
    send an error back to the logger.
    */
  }
}


void loop()
{
  //Wait for a data request.
  if(myTransfer.available()){
    Serial.println("received");
    myTransfer.rxObj(request);
  }

  if(request == 1){
    //Replace our data fields with new sensor data.
    data.tuBackground = 127;
    data.tuReading = 32768;
    
    pressure_sensor.readSensor();
    data.p = pressure_sensor.pressure();
    data.temp = pressure_sensor.temperature();
    
    //Stuff buffer with struct.
    sendSize = myTransfer.txObj(data, 0);
  
    //Send buffer to the logger.
    myTransfer.sendData(sendSize);
    request = 0;
  }
}
