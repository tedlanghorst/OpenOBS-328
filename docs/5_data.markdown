---
layout: page
title: Data
permalink: /data/
---

# Data format
Data is saved on the micro SD card as a .TXT file. A new file is created every day at midnight with the format YYYYMMDD. The data files should look something like this: 
~~~
If found, please contact tlang@live.unc.edu
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
* pressure (bar * $10^{-5}$)
* battery (multiply by $\frac{3.3}{2^{9}}$ to get Volts)

*There is an intermittent bug in the firmware that occasionally omits the header. If this happens, don't worry. The data rows are unaffected and you can copy a header over from another day (make sure you keep the serial number the same).*

# Processing scripts
Some basic processing scripts for Matlab and Python are found [here](../scripts/). I try to keep these updated but variations in sensor versions and development can make it messy. Check over the data headers and conversions if you use them.