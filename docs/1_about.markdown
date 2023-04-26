---
layout: page
title: About
permalink: /about/
---

#

OpenOBS is an academic research project to develop an open source, affordable, and accurate turbidity and water level sensor using common electronics components. The combination of turbidity (which can be calibrated to the concentration of suspended particulate matter) and water level are key components of monitoring a river system. Increased flow in the river raises the water level, and at the same time, washes sediment and other matter downstream. OpenOBS-328 allows us to cheaply and effectively monitor both of these effects. While comparable commercial sensors cost upwards of $2000, OpenOBS can be built for about $50 and a couple hours of work. 


&nbsp;

# History 
The project began at the University of North Carolina at Chapel Hill (UNC) under the direction of Dr. Evan Goldstein and Dr. Emily Eidam in 2019. After a long period of design and testing, we started producing dozens of sensors and published [the first OpenOBS manuscript](https://aslopubs.onlinelibrary.wiley.com/doi/abs/10.1002/lom3.10469) in Limnology and Oceanography Methods. By 2022, we had built almost 90 sensors and deployed them many times in North Carolina and Alaska, USA. Constructing each sensor was labor intensive and often required troubleshooting problems after assembly. Further, readings were highly sensitive to ambient light and affected by changes in temperature. 

![image](./images/OBS1.png)

*The Original OpenOBS sensor ([GitHub repo](https://github.com/tedlanghorst/OpenOBS)).*

&nbsp;

Development of the OpenOBS-328 began in Fall 2022 when Dr. Emily Eidam was awarded an NSF grant which provided funding to continue developement of the OpenOBS sensor. This included the addition of the pressure sensor and a variant that transmits data in real time. At this point, we decided to move on from many of the old design decisions and approach the problem again with our new knowledge. We changed from a discrete implementation of a photodiode and signal amplifier to an integrated solution (the VCNL4010), which uses the same measurement principles and handles all the analog sensing. We also transitioned from hand-soldering modules to a printed circuit board (PCB), to an entirely assembled PCB that integrated the same functions in a smaller package.

&nbsp;

![image](./images/OpenOBS-328-front.png)

*The new OpenOBS-328 sensor.*








