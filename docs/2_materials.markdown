---
layout: page
title: Materials
permalink: /materials/
---
## Introduction
{:.no_toc}
The parts cost of an OpenOBS-328 is approximately $50 USD. This can be slightly reduced in larger quantities ($40 at 50 qty). You will also need tools and equipment to build your sensors, which we have tried to reduce to the essentials here. These costs are substantial, especially if you are trying to build just a few sensors. If you don't have a lot of this equipment and aren't looking to invest in these tools, look into community resources. For example, the Univeristy of North Caorlina at Chapel Hill has a 'makerspace' with most of these tool available. Similar spaces and tool sharing communities exist outside of univiersities. 

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
* disposable pipettes (3 mL size works well)
* Hot glue gun
* 3D printer
* PVC pipe cutter (can use a saw)
* PVC cement/solvent
* Electronics tweezers
* Fine flush cutters
* Wire strippers (22-30 AWG)
* Electrical tape
* micro USB cable
* Arduino Nano (or clone; [for ISP programmer](./3_build.markdown#isp-programmer))
* Pogo pins (6 individual or 2x3 grid)

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
    <th class="tg-jdb5"></th>
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
    <td class="tg-73oq"><a href="https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/3D_print/custom_pcbs" target="_blank" rel="noopener noreferrer">files</a></td>
    <td class="tg-73oq"></td>
  </tr>
  <tr>
    <td class="tg-73oq">Light sensor</td>
    <td class="tg-wp8o">2.5</td>
    <td class="tg-73oq"><a href="https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/turbidity" target="_blank" rel="noopener noreferrer">Gerber files</a></td>
    <td class="tg-73oq">ordering instructions below</td>
  </tr>
  <tr>
    <td class="tg-73oq">pressure PCB</td>
    <td class="tg-wp8o">0.4</td>
    <td class="tg-73oq"><a href="https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/pressure" target="_blank" rel="noopener noreferrer">Gerber files</a></td>
    <td class="tg-73oq">ordering instructions below</td>
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
    <td class="tg-73oq"><a href="https://www.amazon.com/dp/B07RM5Z991" target="_blank" rel="noopener noreferrer">750g</a><br><a href="https://www.amazon.com/dp/B079Y9QFQS/" target="_blank" rel="noopener noreferrer">1500g</a></td>
    <td class="tg-73oq">~20g per sensor</td>
  </tr>
  <tr>
    <td class="tg-73oq">1" PVC</td>
    <td class="tg-wp8o">0.4</td>
    <td class="tg-73oq"><a href="https://www.lowes.com/pd/1-in-dia-x-10-ft-L-450-PSI-PVC-Pipe/3133091" target="_blank" rel="noopener noreferrer">Lowe's</a></td>
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
    <td class="tg-73oq">ordering instructions below</td>
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
    <td class="tg-73oq">qwiic cable (JST SH connector 4 pin 20cm length)</td>
    <td class="tg-wp8o">1</td>
    <td class="tg-73oq"><a href="https://octopart.com/prt-17257-sparkfun-115856491?r=sp" target="_blank" rel="noopener noreferrer">Octopart</a><br>
    <a href="https://www.sparkfun.com/products/14429" target="_blank" rel="noopener noreferrer">Sparkfun</a><br>
    <a href="https://www.aliexpress.us/item/3256803220110303.html" target="_blank" rel="noopener noreferrer">AliExpress</a>
    </td>
    <td class="tg-73oq">Can cut in half, need ~20 cm length. Double check options if using AliExpress. </td>
  </tr>
  <tr>
    <td class="tg-73oq">end plug</td>
    <td class="tg-wp8o">3.5</td>
    <td class="tg-73oq"><a href="https://www.amazon.com/dp/B09P12JQRD" target="_blank" rel="noopener noreferrer">Amazon</a></td>
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

## Ordering PCBs from JLCPCB
1. Download the manufacturing files for the [data logger](https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/logger), [turbidity sensor](https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/turbidity), and [pressure sensor](https://github.com/tedlanghorst/OpenOBS-328/tree/main/hardware/PCBA/pressure) from the project Github repo. The data logger and turbidity sensors can be ordered assembled, and as such will have 3 files each. The pressure sensor directory only has 1 file because you have to assemble it separately.

1. Go to JLCPCB and click “Instant Quote”.

1. Upload one of gerber files at the top of the page (.zip extension). You will need to change the following settings:
    - **PCB Qty:** This is the number of **panels** you are ordering, and the actual number of finished boards will be greater. See next 2 steps. Multiply the rows and columns of Panel Format to get number of boards per panel.
    - **Delivery format:** Panel by Customer
    - **Panel Format:** This is different for each board:
        |        PCB       | Columns | Rows |
        |------------------|---------|------|
        | data logger      | 1       | 5    |
        | turbidity sensor | 5       | 4    |
        | pressure board   | 9       | 10   |
        
    - **Remove order number:** Specify a location
    > If you are ordering the pressure board, click **add to cart** and skip past the remainder of this section. If you are ordering the data logger or turbidity sensor, enable the option for **PCB Assembly** towards the bottom and continue. 
    - **PCBA type:** Standard
    - **Assembly side:** Top (Optionally both sides for the data logger)
    - **Edge Rails/Fiducials:** Added by Customer
    - Click **Confirm**. 
    - Click **Next**
    - This should take you to a page to upload upload the BOM and CPL files. They are both .csv files, named “BOM_\*.csv” and “PickAndPlace_\*.csv.” respectively. 
    - On the same page, select **File provided as** "Single Piece, pls help … "
    - Click **Process BOM & CPL**. You may get a warning that some components were not included in the BOM. This is fine, click **Continue**.
    - Now a table of the parts will be shown. Make sure they’re all selected and there are no warnings about inventory shortage etc. Send me an email if any parts are out of stock and I can check if there are any compatable replacements. 
    - Click **Next**. Now a rendering of the populated board should appear, but it will only include the first PCB on the panel. 
    - Click **Next** again and then **Save to Cart**.
1. Repeat the last section with any other PCBs you are ordering.
1. Go through checkout.
