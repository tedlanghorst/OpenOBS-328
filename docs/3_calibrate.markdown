---
layout: page
title: Calibrate
permalink: /calibrate/
---

## Turbidity calibration
We do a 5 point calibration with tap water for 0 NTUs and Formazin dilutions at 100, 250, 500, and 1000 NTUs. Set the logger to run in [continuous mode](./4_deploy.markdown#deploying) (~1.1 Hz sampling) and hold it in a beaker of each NTU standard for ~30 seconds. If you're comfortable with Matlab and have a license, try the [auto-calibration script](https://github.com/tedlanghorst/OpenOBS-328/blob/main/scripts/calibrateOOBS.m) to process the data. 

## Sediment calibration

### In the field
While the logger is installed on site, visit it regularly and collect measurements of total suspended solids or suspended sediment concentration. Ideally your measurements will cover nearly the full range of values you expect to observe with the sensor. sample the sensor data when the in-situ measurements were made to calibrate the sensor response.

### In the lab
This is a hybrid of the last two options. Collect some sediment from your field site (either fines from the banks or distilled from the river). Put a large pitcher of clear water on a stir plate and add sediment in steps up to your maximum concentration. Dunk the sensor in the pitcher for ~30 seconds at each step. Subsample the pitcher at each step to measure the actual concentration.