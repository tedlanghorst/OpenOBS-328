---
layout: page
title: Materials
permalink: /materials/
---
## Introduction
{:no_toc}
The parts cost of an OpenOBS-328 is approximately $50 USD. This can be slightly reduced in larger quantities ($40 at 100 qty). You will also need tools and equipment to build your sensors, which we have tried to reduce to the essentials here. These costs are substantial, especially if you are trying to build just a few sensors. If you don't have a lot of this equipment and aren't looking to invest in these tools, look into community resources. For example, the Univeristy of North Caorlina at Chapel Hill has a 'makerspace' with most of these tool available. Similar spaces and tool sharing communities exist outside of univiersities. 

## Table of Contents 
{:.no_toc}
* TOC
{:toc}


## Tools & Materials
* Soldering iron
* Solder
* Hot air gun/station for electronics. (sometimes called rework station)
* No clean solder paste
* Vacuum pump
* Vacuum chamber
* Hot glue gun
* 3D printer
* PVC pipe cutter
* Electronics tweezers
* Fine flush cutters
* Wire strippers (22-30 AWG)
* 30 AWG wire (red, black, blue, yellow)
* micro USB cable
* [ISP programmer](#isp-programmer)

## Parts

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-wp8o{border-color:#000000; text-align:center;vertical-align:top}
.tg .tg-73oq{border-color:#000000;text-align:left;vertical-align:top}
.tg .tg-jdb5{border-color:#000000;font-weight:bold;text-align:center;vertical-align:bottom; border-width: 0px 0px 5px 0px}
.tg .tg-1tol{border-color:#000000;font-weight:bold;text-align:left;vertical-align:middle}
.tg .tg-4e6d{border-color:#000000;color:#00E;text-align:left;text-decoration:underline;vertical-align:top}
.tg .tg-noSides{border-left:0px; border-right:0px}
.tg .tg-topLeft{border-width:0px}
</style>
<table class="tg">
<colgroup>
<col style="width: 15%">
<col style="width: 20%">
<col style="width: 10%">
<col style="width: 10%">
<col style="width: 20%">
</colgroup>
<thead>
  <tr>
    <th class="tg-topLeft"></th>
    <th class="tg-jdb5">Item</th>
    <th class="tg-jdb5">Appx. Cost</th>
    <th class="tg-jdb5">Links</th>
    <th class="tg-jdb5">Notes</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-1tol" rowspan="9">Sensor head</td>
    <td class="tg-73oq">3D printed head</td>
    <td class="tg-wp8o">0.50</td>
    <td class="tg-73oq"><a href="https://github.com/tedlanghorst/OpenOBS-328/blob/main/hardware/3D_print/sensor_head_single.stl" target="_blank" rel="noopener noreferrer">.STL file</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">Light sensor</td>
    <td class="tg-wp8o">2.5</td>
    <td class="tg-73oq"><a href="https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/turbidity" target="_blank" rel="noopener noreferrer">Gerber files</a></td>
    <td class="tg-73oq">JLCPCB ordering instruction</td>
  </tr>
  <tr>
    <td class="tg-73oq">pressure PCB</td>
    <td class="tg-wp8o">0.4</td>
    <td class="tg-73oq"><a href="https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/pressure" target="_blank" rel="noopener noreferrer">Gerber files</a></td>
    <td class="tg-73oq">JLCPCB ordering instruction</td>
  </tr>
  <tr>
    <td class="tg-73oq">pressure sensor</td>
    <td class="tg-wp8o">21</td>
    <td class="tg-73oq"><a href="https://octopart.com/ms580314ba01-00-te+connectivity-59208930?r=sp" target="_blank" rel="noopener noreferrer">14 bar</a><br><a href="https://octopart.com/ms580305ba01-00-te+connectivity-59208929?r=sp" target="_blank" rel="noopener noreferrer">5 bar</a></td>
    <td class="tg-73oq">5 bar max sensor has better resolution</td>
  </tr>
  <tr>
    <td class="tg-73oq">flat flex cable</td>
    <td class="tg-wp8o">0.61</td>
    <td class="tg-73oq"><a href="https://octopart.com/search?q=5-1474644-0&currency=USD&specs=0" target="_blank" rel="noopener noreferrer">octopart</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">0603 0.1uF</td>
    <td class="tg-wp8o">0.01</td>
    <td class="tg-73oq"><a href="https://octopart.com/cl10b104kb8nnwc-samsung-23795471?r=sp" target="_blank" rel="noopener noreferrer">octopart</a></td>
    <td class="tg-73oq">Very generic part. Any 0603 0.1uF will do.</td>
  </tr>
  <tr>
    <td class="tg-73oq">epoxy</td>
    <td class="tg-wp8o">0.5</td>
    <td class="tg-73oq"><a href="https://www.amazon.com/VViViD-Optically-Clear-2-Part-Coating/dp/B0797KW5JD/ref=sr_1_2?crid=3DGB62750R6T6&keywords=VViViD+Optically+Clear+2-Part+Epoxy+Hard+Gloss+Coating+Resin&qid=1683411866&sprefix=vvivid+optically+clear+2-part+epoxy+hard+gloss+coating+resin+750g+small+pack+%2Caps%2C99&sr=8-2" target="_blank" rel="noopener noreferrer">750g</a><br><a href="https://www.amazon.com/VViViD-Optically-Clear-2-Part-Coating/dp/B07RM5Z991/ref=sr_1_5?crid=3DGB62750R6T6&keywords=VViViD+Optically+Clear+2-Part+Epoxy+Hard+Gloss+Coating+Resin&qid=1683411946&sprefix=vvivid+optically+clear+2-part+epoxy+hard+gloss+coating+resin+750g+small+pack+%2Caps%2C99&sr=8-5" target="_blank" rel="noopener noreferrer">1500g</a></td>
    <td class="tg-73oq">20g per sensor</td>
  </tr>
  <tr>
    <td class="tg-73oq">1" PVC</td>
    <td class="tg-wp8o">0.4</td>
    <td class="tg-73oq"><a href="https://www.lowes.com/pd/Charlotte-Pipe-1-in-dia-x-10-ft-L-200-PSI-SDR-21-PVC-Pipe/1000080801" target="_blank" rel="noopener noreferrer">Lowe's</a></td>
    <td class="tg-73oq">6" per sensor</td>
  </tr>
  <tr>
    <td class="tg-73oq">pvc cement</td>
    <td class="tg-wp8o">0.2</td>
    <td class="tg-73oq"><a href="https://www.lowes.com/pd/Oatey-8-fl-oz-PVC-Cement/4750803" target="_blank" rel="noopener noreferrer">Lowe's</a></td>
    <td class="tg-73oq">cost based on 50 sensors</td>
  </tr>
  <tr>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
  </tr>
  <tr>
    <td class="tg-1tol" rowspan="5">OpenOBS-328</td>
    <td class="tg-73oq">assembled PCB</td>
    <td class="tg-wp8o">12</td>
    <td class="tg-73oq"><a href="https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/logger" target="_blank" rel="noopener noreferrer">Gerber files</a></td>
    <td class="tg-73oq">JLCPCB ordering instruction</td>
  </tr>
  <tr>
    <td class="tg-73oq">Battery holder</td>
    <td class="tg-wp8o">1.1</td>
    <td class="tg-73oq"><a href="https://octopart.com/2460-keystone-17876?r=sp" target="_blank" rel="noopener noreferrer">Octopart</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">qwiic connector</td>
    <td class="tg-wp8o">0.5</td>
    <td class="tg-73oq"><a href="https://octopart.com/sm04b-srss-tb%28lf%29%28sn%29-jst-289307?r=sp" target="_blank" rel="noopener noreferrer">Octopart</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">qwiic cable</td>
    <td class="tg-wp8o">1</td>
    <td class="tg-73oq"><a href="https://octopart.com/prt-17257-sparkfun-115856491?r=sp" target="_blank" rel="noopener noreferrer">Octopart</a><br><a href="https://www.sparkfun.com/products/14429" target="_blank" rel="noopener noreferrer">Sparkfun</a></td>
    <td class="tg-73oq">Cut in half, 1 part supplies 2 sensors.</td>
  </tr>
  <tr>
    <td class="tg-73oq">end plug</td>
    <td class="tg-wp8o">3.5</td>
    <td class="tg-73oq"><a href="https://www.amazon.com/Dsnaduo-Automotive-Neoprene-Expansion-28mm/dp/B09P12JQRD/ref=pd_bxgy_vft_none_sccl_2/145-3546519-1924258?pd_rd_w=71jGh&content-id=amzn1.sym.7f0cf323-50c6-49e3-b3f9-63546bb79c92&pf_rd_p=7f0cf323-50c6-49e3-b3f9-63546bb79c92&pf_rd_r=3X7QQF87M0K1WG5FSKEE&pd_rd_wg=kG2Ph&pd_rd_r=2b97f4d7-f0c1-4cfa-ab36-4c1da310bbc5&pd_rd_i=B09P12JQRD&psc=1" target="_blank" rel="noopener noreferrer">Amazon</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
    <td class="tg-noSides"></td>
  </tr>
  <tr>
    <td class="tg-1tol" rowspan="7">Iridium</td>
    <td class="tg-73oq">iridium module</td>
    <td class="tg-wp8o">267.5</td>
    <td class="tg-73oq"><a href="https://www.sparkfun.com/products/14498" target="_blank" rel="noopener noreferrer">Sparkfun</a></td>
    <td class="tg-73oq">+ $15/month and $0.12/transmission</td>
  </tr>
  <tr>
    <td class="tg-73oq">pressure sensor (baro)</td>
    <td class="tg-wp8o">22</td>
    <td class="tg-73oq"><a href="https://octopart.com/ms580302ba01-00-te+connectivity-59208928?r=sp" target="_blank" rel="noopener noreferrer">Octopart</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">qwiic cable</td>
    <td class="tg-wp8o">1</td>
    <td class="tg-4e6d"><a href="https://octopart.com/prt-17257-sparkfun-115856491?r=sp" target="_blank" rel="noopener noreferrer">Octopart</a><br><a href="https://www.sparkfun.com/products/14429" target="_blank" rel="noopener noreferrer">Sparkfun</a></td>
    <td class="tg-73oq">Cut in half, 1 part supplies 2 sensors.</td>
  </tr>
  <tr>
    <td class="tg-73oq">100' cable</td>
    <td class="tg-wp8o">35</td>
    <td class="tg-4e6d"><a href="https://www.amazon.com/Monoprice-Access-Gauge-Conductor-Speaker/dp/B003KPYRJM/ref=d_pd_di_sccai_cn_sccl_2_2/147-5558742-6438149?pd_rd_w=XtCA6&content-id=amzn1.sym.e13de93e-5518-4644-8e6b-4ee5f2e0b062&pf_rd_p=e13de93e-5518-4644-8e6b-4ee5f2e0b062&pf_rd_r=2148BS7ECTT29JE6CXV4&pd_rd_wg=w4b3d&pd_rd_r=52dbf083-5f28-4a72-8769-5486458894c5&pd_rd_i=B003KPYRJM&psc=1" target="_blank" rel="noopener noreferrer">Amazon</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">case</td>
    <td class="tg-wp8o">30</td>
    <td class="tg-4e6d"><a href="https://www.amazon.com/Olympia-Waterproof-Customizable-Equiment-Camera/dp/B08CXZNSK2/ref=sr_1_15?crid=JHF3WLPXNAAT&keywords=waterproof%2Bcase&qid=1683414354&sprefix=waterproof%2Bcase%2Caps%2C98&sr=8-15&th=1" target="_blank" rel="noopener noreferrer">Amazon</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">solar panel</td>
    <td class="tg-wp8o">38</td>
    <td class="tg-4e6d"><a href="https://www.amazon.com/SOLPERK-Maintainer-Waterproof-Controller-Adjustable/dp/B091KGZGM3/ref=sr_1_3?crid=2H0AH8F0C328Y&keywords=12v%2Bsolar%2Bpanel&qid=1683414390&sprefix=12v%2Bsolar%2Bpanel%2Caps%2C103&sr=8-3&th=1" target="_blank" rel="noopener noreferrer">Amazon</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">12V SLA battery</td>
    <td class="tg-wp8o">50</td>
    <td class="tg-4e6d"></td>
    <td class="tg-73oq"></td>
  </tr>
</tbody>
</table>

## ISP programmer
You can buy specialized devices that act as an ISP, but it is easy enough to just use another Arduino that already has a bootloader installed to burn a new device. Here is an easy to make ISP device using an Arduino Nano clone. Besides the 6 pogo connectors, you will need to attach a wire from pin D10 to the RST pin and then cut the RST trace on the PCB. The capacitor between ground and reset can help with stability, but not always necessary. 

D10 wire | D10 to RST | RST trace cut
|:------:|:----------:|:-----------:|
![](./assets/images/ISP_1.JPG)|![](./assets/images/ISP_2.JPG)|![](./assets/images/ISP_3.JPG)