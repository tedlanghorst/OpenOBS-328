#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "../libs/SparkFun_AS7265x/SparkFun_AS7265X.h"
#include "../libs/MS5803/MS5803.h" 

// Sensor settings structure
struct SensorSettings {
    uint8_t backscatterCurrent = AS7265X_LED_CURRENT_LIMIT_12_5MA; // 12.5, 25, 50, 100 mA
    uint8_t indicatorCurrent = AS7265X_INDICATOR_CURRENT_LIMIT_1MA; // 1, 2, 4, 8 mA
    uint8_t gain = AS7265X_GAIN_64X; // 1x, 37x, 16x, 64x
    uint8_t integrationCycles = 64; //1-255
    uint8_t measFlags = 0b00001111;
};


// Sensors class
class Sensors {
public:
    Sensors(uint16_t eepromAddr, uint8_t ms5803_version); 
    
    uint16_t eepromAddress;     // Store the address passed in constructor
    bool hasPressureSensor;
    SensorSettings settings;    // Settings struct
    AS7265X as7265x;            // Proximity sensor
    MS_5803 ms5803;             // Pressure sensor

    void saveSettings();
    void loadSettings(); 
    void setBackscatterCurrent(uint8_t current);
    void setIndicatorCurrent(uint8_t current);
    void setBackscatterGain(uint8_t gain);
    void setMeasurementFlags(uint8_t flags);
    void newSettings();
    void begin(bool &vcnl_init, bool &ms5803_init); 
    void readChannels(float values[18], bool withBulb);
    void getReadings(float ambient[18], float backscatter[18], uint32_t &abs_P, int16_t &water_temp);
};
    
#endif // SENSORS_H