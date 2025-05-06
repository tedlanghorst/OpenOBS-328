#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <EEPROM.h>
#include "../libs/SparkFun_AS7265x/SparkFun_AS7265X.h"
#include "../libs/MS5803/MS5803.h" 

// Sensor settings structure
struct SensorSettings {
    as7265x_led_current backscatterCurrent = LED_12_5MA; // 12.5, 25, 50, 100 mA
    as7265x_indicator_current indicatorCurrent = INDICATOR_2MA; // 1, 2, 4, 8 mA
    as7265x_gain gain = GAIN_1X; // 1x, 37x, 16x, 64x
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
    void setBackscatterCurrent(as7265x_led_current current);
    void setIndicatorCurrent(as7265x_indicator_current current);
    void setBackscatterGain(as7265x_gain gain);
    void setMeasurementFlags(uint8_t flags);
    void newSettings();
    void begin(bool &vcnl_init, bool &ms5803_init); 
    void getReadings(uint16_t &tuAmbient, uint16_t &tuBackscatter, uint32_t &abs_P, int16_t &water_temp);
};
    
#endif // SENSORS_H