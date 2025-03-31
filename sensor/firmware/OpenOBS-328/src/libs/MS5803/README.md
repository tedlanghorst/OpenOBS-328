Arduino library for the Measurement Specialties MS5803 pressure sensor modules. This library
only works with the 2, 5, and 14 bar variants and will return incorrect
pressure and temperature values if used with other models. See http://github.com/millerlp for 
libraries to use with the other MS5803 pressure sensor models.

The MS5803 pressure sensor works on voltages around 3 volts. To use it with a 5V Arduino,
you need to supply the sensor power from the Arduino's 3V3 voltage output. Additionally,
you must place 10k ohm resistors between the SDA + SCL I2C communication lines and the 3V3 
voltage supply to keep the data lines from exceeding 3.3V. The manufacturer recommends placing 
a 0.1 microFarad (100 nF) ceramic capacitor between pin 5 (Vdd) and ground. 

PS (pad 6) must be tied to 3.3V supply to invoke I2C Communications mode. 
The SPI protocol is not supported in this library.

 

to use this library. The MS_5803() constructor takes three arguments:
	Version: supported values are 2, 5, and 14. The default is 14.
	I2C address: values are 0x76 and 0x77. The default is 0x67.
	Oversampling range: values are 256, 512, 1024, 2048, and 4096. The default is 512. Larger values include longer delays to allow the sensor to complete a sample. 

In the setup loop, initialize the sensor as follows:
```
	// This must be in the setup loop. arguments: true or false for verbose output
	// Returns a boolean true or false depending on whether the CRC error check
	// succeeds or fails. See the example sketch.
	sensor.initializeMS_5803(true) 
```

Other useful commands:
```

	readSensor() // Get temperature and pressure from sensor

	temperature() // Get temperature in Celsius (returns a float value)
	
	pressure() // Get pressure in mbar (returns a float value)
```

