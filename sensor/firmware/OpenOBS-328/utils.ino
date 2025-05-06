void sensorSleep(long last_wake_time, long sleep_seconds) {
  // Ensure a margin for the next alarm before shutting down.
  if ((last_wake_time+sleep_seconds) < (RTC.now().unixtime()+3)){
    return;
  }
  
  // Set the next alarm right away. Check it hasn't passed later.
  nextAlarm = DateTime(last_wake_time + sleep_seconds);
  RTC.enableAlarm(nextAlarm);
  setBBSQW(); //enable battery-backed alarm
  fileIsOpen = !file.close();
  
  
  LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_ON); //ensure the alarm is set and SD card done reshuffling.
  serialSend("POWEROFF,1");
  
  RTC.clearAlarm(); // Turn off alarm, cutting off battery supply.
  delay(sleep_seconds * 1000); // Just wait if we have USB power (mimics shutdown).
}


void writeToSD(char dataStr[]) {
  if (~fileIsOpen){
    fileIsOpen = file.open(filename, O_WRITE | O_APPEND);
  }
  file.println(dataStr);
  file.sync();
}

void writeDataToSerial() {
  // Ensure Serial communication has been initialized in your setup() function, e.g., Serial.begin(9600);

  // Write timestamp and pressure
  Serial.print(data.timeSeconds);
  Serial.print(',');
  Serial.print(data.timeMillis);
  Serial.print(',');
  Serial.print(data.absPressure);
  Serial.print(',');

  // Write ambient light values with 2 decimal places
  for (int i = 0; i < 18; i++) {
    Serial.print(data.ambientLight[i], 2);
    Serial.print(',');
  }

  // Write backscatter light values with 2 decimal places
  for (int i = 0; i < 18; i++) {
    Serial.print(data.backscatterLight[i], 2);
    Serial.print(',');
  }

  // Write temp and battery voltage
  Serial.print(data.waterTemp);
  Serial.print(',');
  Serial.println(data.batteryVoltage); // Newline at end of row

  // Serial.flush(); // Optional: waits for the transmission of outgoing serial data to complete.
                  // Similar in concept to file.sync() for ensuring data is sent.
                  // Often not strictly necessary for Serial.print unless precise timing
                  // or confirmation of transmission is critical before proceeding.
}

void writeDataToSD() {
  if (!fileIsOpen) {
    fileIsOpen = file.open(filename, O_WRITE | O_APPEND);
  }

  // Write timestamp and pressure
  file.print(data.timeSeconds); 
  file.print(',');
  file.print(data.timeMillis);  
  file.print(',');
  file.print(data.absPressure); 
  file.print(',');

  // Write ambient light values with 2 decimal places
  for (int i = 0; i < 18; i++) {
    file.print(data.ambientLight[i], 2); 
    file.print(',');
  }

  // Write backscatter light values with 2 decimal places
  for (int i = 0; i < 18; i++) {
    file.print(data.backscatterLight[i], 2); 
    file.print(',');
  }

  // Write temp and battery voltage
  file.print(data.waterTemp); 
  file.print(',');
  file.println(data.batteryVoltage); // Newline at end of row

  file.sync();  // Ensure data is written to SD
}


//Check if the daily file exists already. If not, create one and write headers.
void updateFilename() {
  DateTime now = RTC.now();
  snprintf(filename, 13, "%04u%02u%02u.TXT", now.year(), now.month(), now.date());

  SdFile::dateTimeCallback(dateTime_callback);
  //if we create a new file with this name, set header
  fileIsOpen = file.open(filename, O_CREAT | O_EXCL | O_WRITE);
  if (fileIsOpen) {
    snprintf(messageBuffer, 11, "%04u/%02u/%02u", uploadDT.year(), uploadDT.month(), uploadDT.date());
    file.print(F("Firmware updated: "));
    file.println(messageBuffer);
    file.print("OpenOBS SN:");
    file.println(serialNumber);
    file.println();
    file.println((__FlashStringHelper*)dataColumnLabels);
  } 
  sprintf(messageBuffer, "FILE,OPEN,%s\0", filename);
  serialSend(messageBuffer);
}


//callback for SD file creation date.
void dateTime_callback(uint16_t* date, uint16_t* time) {
  DateTime now = RTC.now();
  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(now.year(), now.month(), now.date());
  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}

//enable alarm on battery power. Normally disabled
void setBBSQW() {
  uint8_t ctReg = RTC.readRegister(DS3231_CONTROL_REG);
  ctReg |= 0b01000000;
  RTC.writeRegister(DS3231_CONTROL_REG, ctReg);
}
