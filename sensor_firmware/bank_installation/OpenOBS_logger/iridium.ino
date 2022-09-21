bool startIridium() {
  modem.setPowerProfile(IridiumSBD::USB_POWER_PROFILE); //for testing
  //Start the serial port connected to the satellite modem
  Serial3.begin(19200);
  Serial.println(F("Starting modem..."));
  modemErr = modem.begin();
  if (modemErr != ISBD_SUCCESS) {
    Serial.print(F("Begin failed: error "));
    Serial.println(modemErr);
    if (modemErr == ISBD_NO_MODEM_DETECTED) {
      Serial.println(F("No modem detected: check wiring."));
    }
    return false;
  }
  return true;
}

int getIridiumSignalQuality() {
  int quality;
  modemErr = modem.getSignalQuality(quality);
  if (modemErr != ISBD_SUCCESS) {
    Serial.print(F("SignalQuality failed: error "));
    Serial.println(modemErr);
    return -1;
  } 
  Serial.print(F("On a scale of 0 to 5, signal quality is currently "));
  Serial.print(quality);
  Serial.println(F("."));
  return quality;
}
