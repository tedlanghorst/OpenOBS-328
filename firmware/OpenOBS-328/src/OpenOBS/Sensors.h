#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "../libs/Adafruit_VCNL4010/Adafruit_VCNL4010.h"
#include "../libs/MS5803/MS5803.h" 

// Sensor settings structure
struct SensorSettings {
    vcnl4010_freq backscatterRate = VCNL4010_250;
    uint8_t backscatterCurrent = 5;
    uint8_t ambientAveraging = 1;
    bool ambientContinuous = true;
    bool usePressureSensor = true;
};


// Sensors class
class Sensors {
public:
    Sensors(uint16_t eepromAddr, uint8_t ms5803_version); 
    
    uint16_t eepromAddress;  // Store the address passed in constructor
    SensorSettings settings;    // Settings struct
    Adafruit_VCNL4010 vcnl4010; // Proximity sensor
    MS_5803 ms5803;             // Pressure sensor (optional)

    void saveSettings();
    void loadSettings(); 
    void setBackscatterRate(vcnl4010_freq rate);
    void setBackscatterCurrent(uint8_t current);
    void setAmbientAveraging(uint8_t averaging);
    void setAmbientContinuous(bool continuous);
    void setUsePressureSensor(bool use);
    void newSettings(vcnl4010_freq bs_rate, uint8_t bs_current, uint8_t amb_averaging, bool amb_continuous, bool use_P);
    void begin(bool &vcnl_init, bool &ms5803_init); 
    void getReadings(uint16_t &tuAmbient, uint16_t &tuBackscatter, uint32_t &abs_P, int16_t &water_temp);
};
    
#endif // SENSORS_H