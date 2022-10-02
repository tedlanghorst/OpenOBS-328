#include <Wire.h>               //standard library
#include "SerialTransfer.h"
#include "Adafruit_VCNL4010.h"
#include <MS5803_14.h>          // https://github.com/millerlp/MS5803_14

SerialTransfer myTransfer;

//sensors
Adafruit_VCNL4010 vcnl;
MS_5803 pressure_sensor = MS_5803(4096);

//data storage
typedef struct single_record_t {
  uint32_t logTime = 0;
  uint32_t hydro_p;
  uint16_t tuBackground;
  uint16_t tuReading; 
  int16_t water_temp;
};
single_record_t data;

uint16_t sendSize;
byte request;

bool turb_init;
bool pressure_init;
byte sensor_init;


void setup()
{
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  Serial.begin(115200);
  myTransfer.begin(Serial);

  //initialize the light sensor
  turb_init = vcnl.begin();
  vcnl.setLEDcurrent(5);
  vcnl.setFrequency(VCNL4010_250);
  //initialize the pressure sensor
  pressure_init = pressure_sensor.initializeMS_5803(false);

  turb_init = true;
  pressure_init = true;
}


void loop()
{
  //Wait for a data request.
  if(myTransfer.available()){
    myTransfer.rxObj(request);
  }

  if(request == 1){
    sensor_init = (turb_init << 1) + pressure_init;
    //Fill buffer with initializations and then send it
    sendSize = myTransfer.txObj(sensor_init, 0);
    myTransfer.sendData(sendSize);
    request = 0;
    
  }
  else if(request == 2){
    //Replace our data fields with new sensor data.
    pressure_sensor.readSensor();
    data.hydro_p = pressure_sensor.pressure()*10; //bar^10-4
    data.water_temp = pressure_sensor.temperature()*100; //C^10-2
    data.tuBackground = vcnl.readAmbient();
    data.tuReading = vcnl.readProximity();
    
    //Fill buffer with a data struct and then send it.
    sendSize = myTransfer.txObj(data, 0);
    myTransfer.sendData(sendSize);
    request = 0;
  }
}
