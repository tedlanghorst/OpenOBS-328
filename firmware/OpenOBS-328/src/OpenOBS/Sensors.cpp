#include "sensors.h"

// Sensors class constructor
Sensors::Sensors(uint16_t eepromAddr, uint8_t ms5803_version) {
    eepromAddress = eepromAddr;

    if (ms5803_version > 0) {
        ms5803 = MS_5803(ms5803_version, 0x76, 4096);
    } else {
        // ms5803 = nullptr;
    }
    
}

void Sensors::setBackscatterRate(vcnl4010_freq rate) {
    settings.backscatterRate = rate;
    if (vcnl4010.begin()) {
        vcnl4010.setFrequency(rate);
    }
}

void Sensors::setBackscatterCurrent(uint8_t current) {
    settings.backscatterCurrent = current;
    if (vcnl4010.begin()) {
        vcnl4010.setLEDcurrent(current);
    }
}

void Sensors::setAmbientAveraging(uint8_t averaging) {
    settings.ambientAveraging = averaging;
    if (vcnl4010.begin()) {
        vcnl4010.setAmbientAveraging(averaging);
    }
}

void Sensors::setAmbientContinuous(bool continuous) {
    settings.ambientContinuous = continuous;
    if (vcnl4010.begin()) {
        vcnl4010.setAmbientContinuous(continuous);
    }
}

void Sensors::setUsePressureSensor(bool use) {
    settings.usePressureSensor = use;
}

void Sensors::newSettings(vcnl4010_freq bs_rate, uint8_t bs_current, uint8_t amb_averaging, bool amb_continuous, bool use_P) {
        setBackscatterRate(bs_rate);
        setBackscatterCurrent(bs_current);
        setAmbientAveraging(amb_averaging);
        setAmbientContinuous(amb_continuous);
        setUsePressureSensor(use_P);

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

    if (settings.usePressureSensor) { 
        
        ms5803_init = ms5803.initializeMS_5803();
    } else {
        // Just set true if we are not using it.
        ms5803_init = true;
    }
}


void Sensors::getReadings(uint16_t &tuAmbient, uint16_t &tuBackscatter, uint32_t &abs_P, int16_t &water_temp) {
    tuBackscatter = vcnl4010.readProximity();
    tuAmbient = vcnl4010.readAmbient();
    
    if (settings.usePressureSensor) {
        ms5803.readSensor();
        abs_P = ms5803.getPressure();           //bar*10^-5
        water_temp = ms5803.getTemperature();   //C*10^-2
    } else {
        abs_P = 0;
        water_temp = -32768; // Invalid temperature marker
    }
}



