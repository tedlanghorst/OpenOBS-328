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

void Sensors::setBackscatterRate(vcnl4010_freq rate) {
    settings.backscatterRate = rate;
    vcnl4010.setFrequency(rate);
    saveSettings();
}

void Sensors::setBackscatterCurrent(uint8_t current) {
    settings.backscatterCurrent = current;
    vcnl4010.setLEDcurrent(current);
    saveSettings();
}

void Sensors::setAmbientAveraging(uint8_t averaging) {
    settings.ambientAveraging = averaging;
    vcnl4010.setAmbientAveraging(averaging);
    saveSettings();
}

void Sensors::setAmbientContinuous(bool continuous) {
    settings.ambientContinuous = continuous;
    vcnl4010.setAmbientContinuous(continuous);
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
void Sensors::begin(bool &vcnl_init, bool &ms5803_init) {
    vcnl_init = vcnl4010.begin();
    if (vcnl_init) {
        vcnl4010.setFrequency(settings.backscatterRate);
        vcnl4010.setLEDcurrent(settings.backscatterCurrent);
        vcnl4010.setAmbientAveraging(settings.ambientAveraging);
        vcnl4010.setAmbientContinuous(settings.ambientContinuous);
    } 

    if (hasPressureSensor) { 
        ms5803_init = ms5803.initializeMS_5803();
    } else {
        // Just set true if we are not using it.
        ms5803_init = true;
    }
}


void Sensors::getReadings(uint16_t &tuAmbient, uint16_t &tuBackscatter, uint32_t &abs_P, int16_t &water_temp) {
    if (settings.measFlags & 0b00000001) { // Check bit 0 (readAmbient)
        tuAmbient = vcnl4010.readAmbient();
    } else {
        tuAmbient = 0;
    }

    if (settings.measFlags & 0b00000010) { // Check bit 1 (readBackscatter)
        tuBackscatter = vcnl4010.readProximity();
    } else {
        tuBackscatter = 0;
    }
    
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



