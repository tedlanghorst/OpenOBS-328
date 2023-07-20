---
layout: page
title: Build
permalink: /build/
---
## Introduction
{:.no_toc}

**This guide covers the construction of two variants of the OpenOBS:**
* **OpenOBS-328. A self contained turbidity and level sensor & logger.**
* **OpenOBS-Iridium. A bank-installed logger that can transmit data via Iridium satellite connection with a separate sensor deployed in the river.**


## Table of Contents 
{:.no_toc}
* TOC
{:toc}


## Logger Assembly

### OpenOBS-328

The logger PCBs come mostly assembled. There are just 2 parts that need to be soldered to the back side of the board.

1. Solder the QWIIC connector for the sensors. Start by adding a small dab of solder on one of the big corner pads. Let the solder solidify, and use some tweezers to grab the QWIIC connector. Remelt the solder with the iron and slide the connector in place, check that the metal legs on the back line up with the small gold pads. Solder these fine pads on the back, making sure not to short multiple pins together. If they do end up connected, try ‘swiping’ some of the solder away with a clean iron tip. If that isn’t working, then use a solder wick to remove some solder and try again. Solder the other corner pad (these give most of the mechanical strength).

![image](./assets/images/qwiic.png)

2. Insert the battery holder on the back. There are markings on the board and the holder for positive and negative. 

3. Flip the board over, solder the two battery holder legs, and cut off the excess.

4. Clean the residue from the solder flux around all the new joints using >90% isopropyl alcohol.


### OpenOBS-Iridium

The Iridium logger PCBs come mostly assembled. There are just 2 parts that need to be soldered to the board. 

1. Solder the WAGO wire connectors on with the levers facing towards the top of the board. 

    ![](./assets/images/Iridium_connectors.JPG)

1. Next is the variable output buck converter for the 12V battery supply. As indicated on the PCB, we need to set the output to 5V before installing or we will let the smoke out of our electronics when we connect the battery!   
    - connect a 12V power supply or battery to the input of the buck converter using alligator clips. Measure the output with a multimeter and turn the potentiometer screw until it reads 5V +/- 0.05V. You will probably find they are set quite high from the factory and need several counter-clockwise turns before it even starts to decrease from the input voltage. 

      Bad! | Good!
      |:--:|:--:|
      ![image](./assets/images/buck_high.JPG)|![image](./assets/images/buck_set.JPG)

    - Remove the red LED that indicates the power is on. It will only waste power when deployed and is not needed.

    - Orient the input and output of the buck converter on the PCB and solder the four corners. A bit of solid wire or old resistor leg can help transfer the heat and solder between the pads.
    - Put a big glob of hot glue over the potentiometer to keep the screw set at 5V output. 
      ![image](./assets/images/Iridium_glob.JPG)

## Sensor Head
The sensor housing is one of the OpenOBS’s end caps, and holds the proximity sensor and the pressure sensor. The housing has two chambers which are filled with clear epoxy after insertion of the sensors. The epoxy makes the end cap watertight, and also allows light to travel between the proximity sensor chip and the water.

### 3D printing housing

The sensor housing is produced by 3D printing. [**files located here**](https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/3D_print/custom_pcbs).  

Upload the provided .stl file to the 3D printer’s interface and slice the file into machine code that can be printed.  Printing settings will vary depending on your printer and materials. Here are the settings I use with a Prusa MK3S+ printer, the PrusaSlicer, and PETG filament:

* 0.2mm layer height
* 5 perimeters (greatly increases strength)
* External perimeters print first (better dimensional accuracy)
* Supports on the external overhangs only (internal overhangs can be bridged)
* Classic perimeter generator (results in a complete path around the pressure sensor which helps prevent epoxy leaks)

If you have a prusa mk3s+ (or a clone), you can use the presliced gcode included on github which prints 8 heads at once. Do not try to use this gcode if you have another printer.
    ![Alt text](assets/images/8x_3d_print.png)


There is also a cap/filter for the pressure sensor that can be epoxied or glue in place at the very end. These are a quick and simple print, but I also recommend 0.2mm layers and several perimeters so that they are solid.




### Wiring
#### Pressure sensor

1. Squeeze some solder paste on the pads of the SMD adapter board. The right amount of paste is more important than keeping the paste separate on each pad. The surface tension of the melted solder should ‘snap’ the puddles of solder onto the pads.
1. Place the pressure sensor on the adapter board. Make sure the orientation is correct- there is a dot in one corner of both the adapter and the sensor that indicates orientation.
1. Use a hot air gun at 250°C to heat both sides of the sensor and completely melt the solder. The paste is a mixture of solder and flux. You’ll see the flux melt first but keep heating to melt the solder. Aim at one side and periodically rotate the board to avoid blowing hot air directly at the white gel cap. Sometimes the hot air pushes the sensor around; check that it is still in position before removing the heat.
1. Flip the pressure sensor over to add a 100 nF capacitor and select the I2C address 0x76. 

    ![image](assets/images/pressure_back.png)

1. Solder the 4 pin flat flex cable in from the back of the PCB.

    ![image](assets/images/flat_flex.png)


#### Turbidity sensor

1. These steps are the same for both the OpenOBS-328 and the OpenOBS-Iridium except for this first step.
    - **OpenOBS-328:** cut one of the 50 cm QWIIC cables in half (or use the other half from last time).
    - **OpenOBS-Iridium:** cut another set of 6 cm long, 30 AWG wires in red, black, blue, and yellow.
1. Separate the four strands and strip their ends. Strip the ends of the pressure sensor wires now too.
1. Put the pressure sensor assembly in the 3d printed sensor head 
1. Twist the matching colors together from one end of each new wire and the free end of the pressure sensor wires. Solder them in place on the proximity sensor. Bring the wires in from the back. I found it easiest to twist one pair, solder it, and then repeat with the next pair. Match the wire colors to the right solder point on the proximity sensor using the Qwiic standard:

    >If you are using the [Adafruit VCNL4010 module](https://www.adafruit.com/product/466), connect the red wire to **Vin**, NOT **3vo**! They made a weird choice with their schematic here.

    <table>
    <thead>
      <tr>
        <td rowspan="4"><img src="https://tedlanghorst.github.io/OpenOBS-328/assets/images/QwiicPinoutGraphic.jpg" height="200"> </td>
        <td><b><font color="yellow">SCL</font></b></td>
        <td>yellow</td>
      </tr>
      <tr>
        <td><b><font color="blue">SDA</font></b></td>
        <td>blue</td>
      </tr>
      <tr>
        <td><b><font color="red">3V3 </font></b></td>
        <td>red</td>
      </tr>
      <tr>
        <td><b><font color="black">GND</font></b></td>
        <td>black</td>
      </tr>
    </thead>
    </table>

    *Image from [Sparkfun](https://www.sparkfun.com/qwiic)*
    

1. Slide the proximity sensor into the head by pushing on the end of the PCB with a skinny tool. A scrap of protoboard works really well. It might take some force to get it all the way down, and if the tool slips off the PCB, it’s very possible to break the wires you just soldered on.
1. Finally, test the connections. If you are building an OpenOBS-328, you can simply plug the connector into one of the logger PCBs. If you have built the sensor with short bare wires for the OpenOBS-Iridium you can use alligator clips to connect to a test board. This is your last chance to fix anything before potting it in epoxy! 
    >If you don’t know how to check that the sensor is working, go to the [programming section](#usb) that covers uploading code to the logger and opening the serial monitor to read its output. Once you have a working logger you can just plug in each new sensor. If the logger starts up correctly and does not write out “PTINIT,0”, or “TURBINIT,0” or similar- you are good! 

### Epoxy potting
#### Turbidity sensor
1. The sensor head needs to be situated upside down in order to pour the epoxy. Place a silicon pad (shiny side toward the sensor) between the sensor head and a flat surface (a granite countertop sample works well). The epoxy will not stick to the silicone pad and leaves a smooth surface. Clamp or tape the sensor head securely to the slab.
1. Prepare the epoxy by weighing out two parts Vivid Scientific Epoxy 128 (red label) and one part Epoxy 762 (green label) in an aluminum weighing dish. One turbidity sensor requires about 4 g Epoxy 128 and 2 g Epoxy 762. Thoroughly mix the two parts to ensure it cures fully.
1. At this stage, the epoxy will contain bubbles, which will interfere with the optical path of the proximity sensor. Remove the bubbles by alternating between these two methods 2-3x until the epoxy is clear:
    - **Vacuum chamber** expands bubbles and brings them to the surface. 

    - **Heat gun** reduces the viscosity of the epoxy, allowing bubbles to rise to the surface and burst. Note: Although the heat setting for soldering purposes is 250 ℃, the heat gun should be set to ~120 ℃ when working with the epoxy. Too much heat will make the epoxy set rapidly.

    ![image](./assets/images/epoxy_bubbles.png)
    *Epoxy just after mixing (left) and after the vacuum/heat process (right)*

1. Once the epoxy is bubble free, slowly pour it into the proximity sensor slot. The level of the epoxy should go above the proximity sensor window but below the opening for the pressure sensor- we don't want epoxy dripping down on to the proximity sensor in this orientation. Allow the epoxy to cure for 12-24 hours before unclamping/removing tape.

#### Pressure sensor
1. Use hot glue to seal the hole at the base of the pressure sensor slot. This will keep the epoxy from leaking down.
1. Set the sensor head upright so that the pressure sensor is facing up.
1. Prepare epoxy as in the previous section. Again, one sensor requires about 4g Epoxy 128 and 2g Epoxy 762.
1. Once the epoxy is bubble free, use a disposable pipette to fill the pressure sensor opening **to a level that covers the electronics but without getting epoxy on the white gel membrane of the pressure sensor**. Allow the epoxy to cure for 12-24 hours again.

    ![Alt text](assets/images/pipette_epoxy.png)

## Final Assembly
1. Cut a 6" length of 1” diameter PVC. Wash it now if necessary.
1. In a well ventilated space (e.g. fume hood, fan in a window, outdoors), attach the completed sensor head to the PVC using PVC cement. Apply the cement all around the small diameter of the sensor head and then insert. Twist to spread the cement.
1. Allow the cement to dry for about 30 mins (or according to the instructions on the can). 
1. Flip the sensor housing so the open end is up and pour about 10g of mixed epoxy inside the housing, down on the inside of the sensor head. This will prevent leaks at the junction of the sensor head with the PVC better than the PVC cement alone.

## Programming 
These two sections provide background information for programming OpenOBS devices. In the logger assembly sections later on we will assume you understand these concepts and have set up your computer to be able to program the new device.

### ISP & Bootloading

#### *Introduction*
When we order new PCBs with microcontrollers on them, they are a blank slate with default configurations and no code running. The bootloader is firmware that we ‘burn’ on the microcontroller that defines some settings and subsequently allows us to upload Arduino code via the USB connection. You can think of this kind of like the BIOS of a regular computer; it doesn’t do much on its own, but it lets us install an operating system and then run programs etc. Because this step sets up the protocol for uploading from USB, we have to send this firmware to the microcontroller through the In System Programming (ISP) connections.

You can find additional background info [here](https://linuxhint.com/bootloader-arduino/) if you want to read more!

#### *Connections*
Read through [this tutorial](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP) for how ISP uploading works and how to use an Arduino as the programmer. Don’t worry about all the examples they give on how to use different “programmers” and “hosts”, just understand the basic idea. We will follow the 8-step guide section at the end of the tutorial. At step 5, it says: 

  > Select the item in the Tools > Board menu that corresponds to the board on which you want to burn the bootloader (not the board that you're using as the programmer). See the board descriptions on the environment page for details.

We have a custom circuit and the standard Arduino board options will not work for us. The next section covers how to add new, custom options. 

#### *Board options* 
We will use the [MiniCore](https://github.com/MCUdude/MiniCore) and [MegaCore](https://github.com/MCUdude/MegaCore) set of boards for our custom circuit. See the instructions for both under “Board Manager Installation” for how to make these options available in the Arduino IDE ([minicore install link](https://github.com/MCUdude/MiniCore#how-to-install); [megacore install link](https://github.com/MCUdude/MegaCore#how-to-install))

Once you have installed the new boards options, you can click on Tools -> Boards -> MiniCore -> ATmega328 (for OpenOBS-328 and the OpenOBS-Iridium sensor) or Tools -> Boards -> MegaCore -> ATmega2560 (for the OpenOBS-Iridium logger) from the top menu. Now, under tools -> boards there will be many new options for our microcontroller. Use the following settings whenever uploading any code:

**Table 1: Board settings for uploading to OpenOBS devices.**

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-c3ow{border-color:inherit;text-align:center;vertical-align:top}
.tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
.tg .tg-fymr{border-color:inherit;font-weight:bold;text-align:left;vertical-align:top}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-0pky"><span style="font-weight:700;font-style:normal;text-decoration:none;color:#000;background-color:transparent"></span></th>
    <th class="tg-c3ow"><span style="font-weight:700;font-style:normal;text-decoration:none;color:#000;background-color:transparent">OpenOBS-328</span></th>
    <th class="tg-c3ow"><span style="font-weight:700;font-style:normal;text-decoration:none;color:#000;background-color:transparent">OpenOBS-Iridium Sensor</span></th>
    <th class="tg-c3ow"><span style="font-weight:700;font-style:normal;text-decoration:none;color:#000;background-color:transparent">OpenOBS-Iridium Logger</span></th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">Board</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">MiniCore -&gt; ATmega328</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">MiniCore -&gt; ATmega328</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">MegaCore -&gt; ATmega2560</span></td>
  </tr>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">Clock</span></td>
    <td class="tg-c3ow" colspan="3"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">External 8MHz</span></td>
  </tr>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">BOD</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">2.7V</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">2.7V</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">4.3V</span></td>
  </tr>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">EEPROM</span></td>
    <td class="tg-c3ow" colspan="3"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">EEPROM retained</span></td>
  </tr>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">Compiler LTO</span></td>
    <td class="tg-c3ow" colspan="3"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">LTO enabled</span></td>
  </tr>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">Variant</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">328P/328PA</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">328P/328PA</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">N/A</span></td>
  </tr>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">Pinout</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">N/A</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">N/A</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">Arduino MEGA pinout</span></td>
  </tr>
  <tr>
    <td class="tg-fymr"><span style="font-style:normal;text-decoration:none;color:#000;background-color:transparent">Bootloader</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">Yes (UART0)</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">No bootloader</span></td>
    <td class="tg-c3ow"><span style="font-weight:400;font-style:normal;text-decoration:none;color:#000;background-color:transparent">Yes (UART0)</span></td>
  </tr>
</tbody>
</table>


**Bootloading** 


**Programming with ISP**
We can also send our Arduino program to the microcontroller directly through the ISP, rather than installing a bootloader and then programming through USB. The advantage to this method is that we do not need the hardware for a USB connection. We will only use ISP programming for the sensor end of the OpenOBS-Iridium variant, because once we verify the sensor is working, we will encase it in epoxy.


### USB

After installing the Arduino bootloader via the ISP programming, we can now upload code via the micro-USB connection. 

1. Setup

	1.1 If you already have the [Arduino IDE](https://www.arduino.cc/en/software) and know how to connect and upload code, skip ahead to the next step. Otherwise, download and install the free Arduino IDE and follow [this guide](https://learn.adafruit.com/ladyadas-learn-arduino-lesson-number-1/upload-your-first-sketch) to get familiar with the IDE and learn how to upload code. 

	1.2 Review the section “Setting board options” earlier in this section and use Table 1 to pick the correct board in the Arduino IDE.
	
	1.3 Download and unzip the entire github repo for the sensor you are working with to get the latest code and documentation.

	1.4 Libraries are chunks of code that we can import into our script and use to simplify the interactions with hardware. The Arduino IDE comes with many libraries, and we have packaged several others with the OBS code, but one library needs to be installed separately using the Arduino Library Manager. Search for “SdFat” (by Bill Greiman) and click install. 

2. Firmware

	2.1 Open the correct sensor firmware in the Arduino IDE and upload it to the OpenOBS. Watch the IDE status bar for the code to be compiled and uploaded.

	2.2 Open the Serial Monitor (Tools -> Serial Monitor) and verify that the OpenOBS is starting up and communicating. Change the baud rate to 250000 in the bottom right corner of the Serial Monitor if it is not already set.

	2.3 If the serial number has not been set, the serial monitor will prompt you to set it now by typing it at the top of the window. If you need to change it in the future, use the .ino script titled “set_serial_number.ino”, follow the prompts in the serial monitor, and then reupload the regular sensor firmware.
