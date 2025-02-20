/**************************************************************************/
/*!
  @file     Adafruit_VCNL4010.cpp

  @mainpage Adafruit VCNL4010 Ambient Light/Proximity Sensor

  @section intro Introduction

  This is a library for the Aadafruit VCNL4010 proximity sensor breakout board
  ----> http://www.adafruit.com/products/466

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  @section author Author

  K. Townsend (Adafruit Industries)

  @section license License

  BSD (see license.txt)
*/
/**************************************************************************/

#include "Adafruit_VCNL4010.h"

/**************************************************************************/
/*!
    @brief  Instantiates a new VCNL4010 class
*/
/**************************************************************************/
Adafruit_VCNL4010::Adafruit_VCNL4010() {}

/**************************************************************************/
/*!
    @brief  Setups the I2C connection and tests that the sensor was found. If
   so, configures for 200mA IR current and 390.625 KHz.
    @param addr Optional I2C address (however, all chips have the same address!)
    @param theWire Optional Wire object if your board has more than one I2C
   interface
    @return true if sensor was found, false if not
*/
/**************************************************************************/
boolean Adafruit_VCNL4010::begin(uint8_t addr, TwoWire *theWire) {
  if (i2c_dev)
    delete i2c_dev;
  i2c_dev = new Adafruit_I2CDevice(addr, theWire);
  if (!i2c_dev->begin())
    return false;

  uint8_t rev = read8(VCNL4010_PRODUCTID);
  // Serial.println(rev, HEX);
  if ((rev & 0xF0) != 0x20) {
    return false;
  }
  
  return true;
}

/**************************************************************************/
/*!
    @brief  Set the LED current.
    @param  current_10mA  Can be any value from 0 to 20, each number represents
   10 mA, so if you set it to 5, its 50mA. Minimum is 0 (0 mA, off), max is 20
   (200mA)
*/
/**************************************************************************/

void Adafruit_VCNL4010::setLEDcurrent(uint8_t current_10mA) {
  if (current_10mA > 20)
    current_10mA = 20;
  write8(VCNL4010_IRLED, current_10mA);
}

/**************************************************************************/
/*!
    @brief  Get the LED current
    @return  The value directly from the register. Each bit represents 10mA so 5
   == 50mA
*/
/**************************************************************************/

uint8_t Adafruit_VCNL4010::getLEDcurrent(void) { return read8(VCNL4010_IRLED); }

/**************************************************************************/
/*!
    @brief  Set the measurement signal frequency
    @param  freq Sets the measurement rate for proximity. Can be VCNL4010_1_95
   (1.95 measurements/s), VCNL4010_3_90625 (3.9062 meas/s), VCNL4010_7_8125
   (7.8125 meas/s), VCNL4010_16_625 (16.625 meas/s), VCNL4010_31_25 (31.25
   meas/s), VCNL4010_62_5 (62.5 meas/s), VCNL4010_125 (125 meas/s) or
   VCNL4010_250 (250 measurements/s)
*/
/**************************************************************************/

void Adafruit_VCNL4010::setFrequency(vcnl4010_freq freq) {
  write8(VCNL4010_PROXRATE, freq);
}

/**************************************************************************/
/*!
    @brief  Set the number of measurements to average for an ambient reading
    @param  avg Sets the number of measurements (2^log2_avg)
*/
/**************************************************************************/

void Adafruit_VCNL4010::setAmbientAveraging(uint8_t log2_avg) {
  // Ensure the value does not exceed the maximum (128 conversions)
  if (log2_avg > 7) {
    log2_avg = 7; 
  }

  // Read the current register value
  uint8_t reg = read8(VCNL4010_AMBIENTPARAMETER);

  // Mask out the old averaging bits (Bit 2 to Bit 0) and set the new ones
  reg &= 0b11111000; 
  reg |= (log2_avg & 0b00000111); 

  // Write back to the register
  write8(VCNL4010_AMBIENTPARAMETER, reg);
}

void Adafruit_VCNL4010::setAmbientContinuous(bool enable){
  // Read the current register value
  uint8_t reg = read8(VCNL4010_AMBIENTPARAMETER);

  // Clear bit 7, then set it based on `enable`
  reg = (reg & 0b01111111) | (enable << 7); 

  // Write back the modified register value
  write8(VCNL4010_AMBIENTPARAMETER, reg);
}

/**************************************************************************/
/*!
    @brief  Get proximity measurement
    @return Raw 16-bit reading value, will vary with LED current, unit-less!
*/
/**************************************************************************/

uint16_t Adafruit_VCNL4010::readProximity(void) {
  uint8_t i = read8(VCNL4010_INTSTAT);
  i &= ~0x80;
  write8(VCNL4010_INTSTAT, i);

  write8(VCNL4010_COMMAND, VCNL4010_MEASUREPROXIMITY);
  while (1) {
    // Serial.println(read8(VCNL4010_INTSTAT), HEX);
    uint8_t result = read8(VCNL4010_COMMAND);
    // Serial.print("Ready = 0x"); Serial.println(result, HEX);
    if (result & VCNL4010_PROXIMITYREADY) {
      return read16(VCNL4010_PROXIMITYDATA);
    }
    delay(1);
  }
}

/**************************************************************************/
/*!
    @brief  Get ambient light measurement
    @return Raw 16-bit reading value, unit-less!
*/
/**************************************************************************/

uint16_t Adafruit_VCNL4010::readAmbient(void) {
  uint8_t i = read8(VCNL4010_INTSTAT);
  i &= ~0x40;
  write8(VCNL4010_INTSTAT, i);

  write8(VCNL4010_COMMAND, VCNL4010_MEASUREAMBIENT);
  while (1) {
    // Serial.println(read8(VCNL4010_INTSTAT), HEX);
    uint8_t result = read8(VCNL4010_COMMAND);
    // Serial.print("Ready = 0x"); Serial.println(result, HEX);
    if (result & VCNL4010_AMBIENTREADY) {
      return read16(VCNL4010_AMBIENTDATA);
    }
    delay(1);
  }
}

/**************************************************************************/
/*!
    @brief  I2C low level interfacing
*/
/**************************************************************************/

// Read 1 byte from the VCNL4000 at 'address'
uint8_t Adafruit_VCNL4010::read8(uint8_t address) {
  uint8_t buffer[1] = {address};
  i2c_dev->write_then_read(buffer, 1, buffer, 1);
  return buffer[0];
}

// Read 2 byte from the VCNL4000 at 'address'
uint16_t Adafruit_VCNL4010::read16(uint8_t address) {
  uint8_t buffer[2] = {address, 0};
  i2c_dev->write_then_read(buffer, 1, buffer, 2);
  return (uint16_t(buffer[0]) << 8) | uint16_t(buffer[1]);
}

// write 1 byte
void Adafruit_VCNL4010::write8(uint8_t address, uint8_t data) {
  uint8_t buffer[2] = {address, data};
  i2c_dev->write(buffer, 2);
}
