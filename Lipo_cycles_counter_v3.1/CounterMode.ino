/*
    BLOCK 1 CELL NUMBER
    BLOCK 2 mAh
    BLOCK 4 MONTH
    BLOCK 5 YEAR
    BLOCK 6 COUNTER
*/

void CounterMode(void) {
  if (CModeFlag == 0) {
    CModeFlag = 1;
    RModeFlag = 0;
    SModeFlag = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CM Cycles:       ");
    lcd.setCursor(0, 1);
    lcd.print("                 ");
  }
  /* ---------------- WAIT FOR TAG ------------*/
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  /*------------------  READ CELL ------------------*/
  block = 1;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_GetValue(block, myDataRead);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAG ERROR");
    lcd.setCursor(0, 1);
    lcd.print("please reset");
    while (1); // infinite loop to force reset
    return;
  }
  cellsNumber = *myDataRead;
  /*------------------  READ mAh ------------------*/
  block = 2;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_GetValue(block, myDataRead);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAG ERROR");
    lcd.setCursor(0, 1);
    lcd.print("please reset");
    while (1); // infinite loop to force reset
    return;
  }
  mAh = *myDataRead;

  /*------------------  READ MONTH ------------------*/
  block = 4;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_GetValue(block, myDataRead);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAG ERROR");
    lcd.setCursor(0, 1);
    lcd.print("please reset");
    while (1); // infinite loop to force reset
    return;
  }
  month = *myDataRead;

  /*------------------  READ YEAR ------------------*/
  block = 5;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_GetValue(block, myDataRead);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAG ERROR");
    lcd.setCursor(0, 1);
    lcd.print("please reset");
    while (1); // infinite loop to force reset
    return;
  }
  year = *myDataRead;

  /*------------------  READ COUNTER ------------------*/
  block = 6;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_GetValue(block, myDataRead);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAG ERROR");
    lcd.setCursor(0, 1);
    lcd.print("please reset");
    while (1); // infinite loop to force reset
    return;
  }
  oldcounter = *myDataRead;
  /* ---------------- WRITE COUNTER ----------------*/
  block = 6;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  // Write block
  counter = oldcounter + 1; // add 1 to counter
  myData = counter;
  status = mfrc522.MIFARE_SetValue(block, myData);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAG ERROR");
    lcd.setCursor(0, 1);
    lcd.print("please reset");
    while (1); // infinite loop to force reset
    return;
  }
  else Serial.println(F("MIFARE_Write() success "));

  /*------------------  READ COUNTER ------------------*/
  block = 6;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  status = mfrc522.MIFARE_GetValue(block, myDataRead);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAG ERROR");
    lcd.setCursor(0, 1);
    lcd.print("please reset");
    while (1); // infinite loop to force reset
    return;
  }
  counter = *myDataRead;

  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  lcd.setCursor(11, 0);
  sprintf(RModebuf, "%-d        ", oldcounter);
  lcd.print(RModebuf);
  lcd.setCursor(0, 1);
  sprintf(RModebuf, "%dS %4dmAh %02d/%d", cellsNumber, mAh, month, year);
  lcd.print(RModebuf);
  delay(750);
  lcd.setCursor(11, 0);
  sprintf(RModebuf, "%-d        ", counter);
  lcd.print(RModebuf);
  oldcounter = counter;
}
