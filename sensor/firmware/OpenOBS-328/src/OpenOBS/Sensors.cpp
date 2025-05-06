#include "sensors.h"

// Sensors class constructor
Sensors::Sensors(uint16_t eepromAddr, uint8_t ms5803_version) {
    eepromAddress = eepromAddr;

    if (ms5803_version > 0) {
        ms5803 = MS_5803(ms5803_version, 0x76, 4096);
        hasPressureSensor = true;
    } else {
        hasPressureSensor = false;
    }
    
}

void Sensors::setBackscatterCurrent(as7265x_led_current current) {
    settings.backscatterCurrent = current;
    as7265x.setBulbCurrent(current, AS7265x_LED_WHITE);
    as7265x.setBulbCurrent(current, AS7265x_LED_IR);
    as7265x.setBulbCurrent(current, AS7265x_LED_UV);
    saveSettings();
}

void Sensors::setIndicatorCurrent(as7265x_indicator_current current){
    settings.indicatorCurrent = current;
    as7265x.setIndicatorCurrent(current);
    saveSettings();
}

void Sensors::setBackscatterGain(as7265x_gain gain){
    settings.gain = gain;
    as7265x.setGain(gain);
    saveSettings();
}

void Sensors::setMeasurementFlags(uint8_t flags) {
    settings.measFlags = flags;
    saveSettings();
}

// Load settings from EEPROM
void Sensors::loadSettings() {
    EEPROM.get(eepromAddress, settings);
}

// Save settings to EEPROM
void Sensors::saveSettings() {
    EEPROM.put(eepromAddress, settings);
}


// Initialize sensors
void Sensors::begin(bool &as7265x_init, bool &ms5803_init) {
    as7265x_init = as7265x.begin();
    // if (as7265x_init) {
        // as7265x.disableIndicator();
        // setBackscatterCurrent(settings.backscatterCurrent);
        // as7265x.setIndicatorCurrent(settings.indicatorCurrent);
        // as7265x.setGain(settings.gain);
    // } 

    if (hasPressureSensor) { 
        ms5803_init = ms5803.initializeMS_5803();
    } else {
        // Just set true if we are not using it.
        ms5803_init = true;
    }
}


void Sensors::getReadings(uint16_t &tuAmbient, uint16_t &tuBackscatter, uint32_t &abs_P, int16_t &water_temp) {
    // if (settings.measFlags & 0b00000001) { // Check bit 0 (readAmbient)
    //     as7265x.takeMeasurements();
    //     tuAmbient = as7265x.getCalibratedW();
    // } else {
    //     tuAmbient = 0;
    // }
    as7265x.takeMeasurements();
    tuAmbient = as7265x.getCalibratedW();

    // if (settings.measFlags & 0b00000010) { // Check bit 1 (readBackscatter)
    //     as7265x.takeMeasurementsWithBulb();
    //     tuBackscatter = as7265x.getCalibratedW();
    // } else {
    //     tuBackscatter = 0;
    // }
    as7265x.takeMeasurementsWithBulb();
    tuBackscatter = as7265x.getCalibratedW();
    
    if (hasPressureSensor && ((settings.measFlags & 0b00001100) != 0)) {
        ms5803.readSensor();
        if (settings.measFlags & 0b00000100) { // Check bit 2 (readPressure)
            abs_P = ms5803.getPressure();
        } else {
            abs_P = 0;
        }

        if (settings.measFlags & 0b00001000) { // Check bit 3 (readWaterTemp)
            water_temp = ms5803.getTemperature();
        } else {
            water_temp = -32768;
        }
    } else {
        abs_P = 0;
        water_temp = -32768;
    }
}



