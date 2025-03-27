void sensorSleep(long last_wake_time, long sleep_seconds) {
  // Ensure a margin for the next alarm before shutting down.
  if ((last_wake_time+sleep_seconds) < (RTC.now().unixtime()+3)){
    return;
  }
  
  // Set the next alarm right away. Check it hasn't passed later.
  nextAlarm = DateTime(last_wake_time + sleep_seconds);
  RTC.enableAlarm(nextAlarm);
  setBBSQW(); //enable battery-backed alarm
  
  LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_ON); //ensure the alarm is set and SD card done reshuffling.
  serialSend("POWEROFF,1");
  Serial.flush();
  
  RTC.clearAlarm(); // Turn off alarm, cutting off battery supply.
  delay(sleep_seconds * 1000); // Just wait if we have USB power (mimics shutdown).
}


void writeToSD(char dataStr[]) {
  file.open(filename, O_WRITE | O_APPEND);
  file.println(dataStr);
  file.close();
}


//Check if the daily file exists already. If not, create one and write headers.
void updateFilename() {
  DateTime now = RTC.now();
  snprintf(filename, 13, "%04u%02u%02u.TXT", now.year(), now.month(), now.date());

  SdFile::dateTimeCallback(dateTime_callback);
  //if we create a new file with this name, set header
  if (file.open(filename, O_CREAT | O_EXCL | O_WRITE)) {
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
