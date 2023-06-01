---
layout: page
title: Data
permalink: /data/
---

## Data format
Data is saved on the micro SD card as a .TXT file. A new file is created every day at midnight with the format YYYYMMDD. The data files should look something like this: 
~~~
If found, please contact XXXXX
Firmware updated: 2023/02/27
OpenOBS SN:000

time,ambient_light,backscatter,pressure,water_temp,battery
1677518326,1307,11354,9823,2145,649
1677518327,1300,11360,9826,2145,641
1677518328,2402,11296,9824,2145,639
1677518329,3068,11273,9824,2145,639
1677518330,2218,11287,9823,2146,639
~~~

After the data header, we have columns of data that represent
* time (Posix/Unix time. seconds since Jan 1, 1970)
* ambient light (light from 400-700 nm. Appx. equal to 1-2 Lux per unit)
* backscatter (uncalibrated backscatter intensity. Linear w.r.t. turbidity)
* pressure (bar * 10<sup>-5</sup>)
* water temperature (C * 10<sup>-1</sup>)
* battery level (multiply by 3.3*2<sup>-9</sup> to get Volts)

*There is an intermittent bug in the firmware that occasionally omits the header. If this happens, don't worry. The data rows are unaffected and you can copy a header over from another day (make sure you keep the serial number the same).*

## Iridium logger data
The Iridium data logger uses the same sensor head as the 328 version, but with an additional air pressure and temperature sensor for water level correction. As such, the data files on the micro-SD card look very similar to the 328 data. 
The data transmitted from the Iridium loggers is the same as stored on the micro-SD card, but has to be unpacked after transmitting. Rockblock charges about $0.12 per 50 bytes of data transmitted, so we use bit field structures to pack the data down to the smallest possible size without losing information. Each data record is packed into 16 bytes as follows: 

![image](./assets/images/IridiumBitField.png)

The Iridium loggers batch these data and transmits 3 sets of 16 bytes (48 bytes) at once, to fit nicely in the 50 byte Iridium package. When you receive the data, it will have some header info and then a string of characters representing the bytes in hexadecimal. You will need to process the data according to the image above before using it.

Below is an example script in python that parses the data using the ctypes package and carefully recreating our data structure and union with a byte array. This mimicks what happens when we package the data before transmitting, except instead of putting measurements into the records in our transmission packet, we put the data string into the packet. Then, we can access the measurements records through the packet union object.

~~~python
import ctypes as ct

#example data
dataString = "320254641900E72A8884811B2FFF36883E0254641900F52A8784811B36FF3685480254641A00F82A8A84811B34BF3685"
dataBytes = bytes.fromhex(dataString)
nBytes = len(dataBytes)

#recreate the data structure from the Arduino data logger
class single_record(ct.LittleEndianStructure):
    _fields_ = [("logtime", ct.c_uint32, 32),
                ("tuBackground", ct.c_uint32, 16),
                ("tuBackscatter", ct.c_uint32, 16),
                ("waterPressure", ct.c_uint32, 21),
                ("waterTemp",ct.c_int32, 11),
                ("baroAnomaly",ct.c_int32,14),
                ("airTemp",ct.c_int32,10),
                ("batteryVoltage",ct.c_uint32,8)]  
    
class transmission_packet(ct.Union):
    _fields_ = [("record", single_record*(nBytes//ct.sizeof(single_record))),
                ("data", ct.c_ubyte*nBytes)]
    

#Create a packet object and put our data in as a byte array.
packet = transmission_packet()
packet.data = (ct.c_ubyte * nBytes)(*dataBytes)

#example data access
print(packet.record[0].logtime)

#show all the data
for r in packet.record:
    for f in r._fields_:
        print('{:<20s}{:d}'.format(f[0], getattr(r, f[0])))~~~

## Processing scripts
Some basic processing scripts for Matlab and Python are found [here](https://github.com/tedlanghorst/OpenOBS-328/tree/main/scripts). I try to keep these updated but variations in sensor versions and development can make it messy. Check over the data headers and conversions if you use them.