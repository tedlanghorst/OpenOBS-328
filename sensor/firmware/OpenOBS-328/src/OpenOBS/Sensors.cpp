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

void Sensors::setBackscatterCurrent(uint8_t current) {
    settings.backscatterCurrent = current;
    as7265x.setBulbCurrent(current, AS7265x_LED_WHITE);
    as7265x.setBulbCurrent(current, AS7265x_LED_IR);
    as7265x.setBulbCurrent(current, AS7265x_LED_UV);
    saveSettings();
}

void Sensors::setIndicatorCurrent(uint8_t current){
    settings.indicatorCurrent = current;
    as7265x.setIndicatorCurrent(current);
    saveSettings();
}

void Sensors::setBackscatterGain(uint8_t gain){
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

void Sensors::readChannels(float values[18], bool withBulb) {
    if (withBulb) {
        as7265x.takeMeasurementsWithBulb();
    } else {
        as7265x.takeMeasurements();
    }

    values[0] = as7265x.getCalibratedA();
    values[1] = as7265x.getCalibratedB();
    values[2] = as7265x.getCalibratedC();
    values[3] = as7265x.getCalibratedD();
    values[4] = as7265x.getCalibratedE();
    values[5] = as7265x.getCalibratedF();
    values[6] = as7265x.getCalibratedG();
    values[7] = as7265x.getCalibratedH();
    values[8] = as7265x.getCalibratedR();
    values[9] = as7265x.getCalibratedI();
    values[10] = as7265x.getCalibratedS();
    values[11] = as7265x.getCalibratedJ();
    values[12] = as7265x.getCalibratedT();
    values[13] = as7265x.getCalibratedU();
    values[14] = as7265x.getCalibratedV();
    values[15] = as7265x.getCalibratedW();
    values[16] = as7265x.getCalibratedK();
    values[17] = as7265x.getCalibratedL();
}

void Sensors::getReadings(float ambient[18], float backscatter[18], uint32_t &abs_P, int16_t &water_temp) {
    
    if (settings.measFlags & 0b00000001) { // Check bit 0 (readAmbient)
        readChannels(ambient, false);
    } 

    if (settings.measFlags & 0b00000010) { // Check bit 1 (readBackscatter)
        readChannels(backscatter, true);
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





