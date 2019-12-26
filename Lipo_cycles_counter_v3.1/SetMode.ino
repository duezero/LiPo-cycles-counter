/*
    BLOCK 1 CELL NUMBER
    BLOCK 2 mAh
    BLOCK 4 MONTH
    BLOCK 5 YEAR
    BLOCK 6 COUNTER
*/

void SetMode(void) {
  if (SModeFlag == 0) {
    CModeFlag = 0;
    RModeFlag = 0;
    SModeFlag = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SetMode");
    lcd.setCursor(0, 1);
    lcd.print("Set cells:  S");
    lcd.setCursor(11, 1);
    lcd.print(cellsNumber);
  }
  while (ModeIndex == 3) {
    /* ---------------- BUTTONS POLLING -----------*/
    if (digitalRead(ExitButton) == 0 && ExitButtonStatus == 0) {
      ExitButtonStatus = 1;
    }
    if (digitalRead(ExitButton) == 1 && ExitButtonStatus == 1) {
      ModeIndex = 2;
      MenuIndex = 1;
      ExitButtonStatus = 0;
      S_ModeButtonStatus = 1;
    }

    if (digitalRead(ModeButton) == 1 && ModeButtonStatus == 1) { // al rilascio dopo essere entrato in SET MODE
      ModeButtonStatus = 0;
      S_ModeButtonStatus = 0;
      MenuIndex = 1;
    }
    if (digitalRead(ModeButton) == 0 && S_ModeButtonStatus == 0) {
      S_ModeButtonStatus = 1;
    }
    if (digitalRead(ModeButton) == 1 && S_ModeButtonStatus == 1) {
      S_ModeButtonStatus = 0;
      if (MenuIndex == 1) {
        MenuIndex = 2;
      }
      else if (MenuIndex == 2) {
        MenuIndex = 3;
      }
      else if (MenuIndex == 3) {
        MenuIndex = 4;
      }
      else if (MenuIndex == 4) {
        MenuIndex = 5;
      }
      else if (MenuIndex == 5) {
        MenuIndex = 6;
      }
      Serial.println(MenuIndex);
    }
    /* ---------------- MENU INDEX -----------*/
    switch (MenuIndex) {
      case (1):
        SetCells();
        break;
      case (2):
        SetmAh();
        break;
      case (3):
        SetMonth();
        break;
      case (4):
        SetYear();
        break;
      case (5):
        SetCounter();
        break;
      case (6):
        WriteTAG();
        break;
    }
  }
}
/* --------------------------------- SET CELLS ---------------------------------*/
void SetCells() {
  if (SCellsFlag == 0) {
    SCellsFlag = 1;
    SmAhFlag = 0;
    SMonthFlag = 0;
    SYearFlag = 0;
    SCounterFlag = 0;
    WTAGFlag = 0;
  }
  /* ---------------- UP DOWN BUTTONS POLLING -----------*/
  if (digitalRead(UPButton) == 0 && UPButtonStatus == 0) {
    UPButtonStatus = 1;
  }
  if (digitalRead(UPButton) == 1 && UPButtonStatus == 1) {
    UPButtonStatus = 0;
    if (cellsNumber < 6) {
      cellsNumber++;
    }
    else cellsNumber = 1;
    lcd.setCursor(11, 1);
    lcd.print(cellsNumber);
  }
  if (digitalRead(DWNButton) == 0 && DWNButtonStatus == 0) {
    DWNButtonStatus = 1;
  }
  if (digitalRead(DWNButton) == 1 && DWNButtonStatus == 1) {
    DWNButtonStatus = 0;
    if (cellsNumber > 1) {
      cellsNumber--;
    }
    else cellsNumber = 6;
    lcd.setCursor(11, 1);
    lcd.print(cellsNumber);
  }
}
/* --------------------------------- SET mAh ---------------------------------*/
void SetmAh() {
  if (SmAhFlag == 0) {
    SCellsFlag = 0;
    SmAhFlag = 1;
    SMonthFlag = 0;
    SYearFlag = 0;
    SCounterFlag = 0;
    WTAGFlag = 0;
    lcd.setCursor(0, 1);
    lcd.print("Set mAh:         ");
    lcd.setCursor(8, 1);
    sprintf(mAhbuf, "%5dmAh", mAh);
    lcd.print(mAhbuf);
  }
  /* ---------------- UP DOWN BUTTONS POLLING -----------*/
  if (digitalRead(UPButton) == 0 && UPButtonStatus == 0) {
    UPButtonStatus = 1;
  }
  if (digitalRead(UPButton) == 1 && UPButtonStatus == 1) {
    UPButtonStatus = 0;
    if (mAh < 10000) {
      mAh = mAh + 50;
    }
    else mAh = 50;
    lcd.setCursor(8, 1);
    sprintf(mAhbuf, "%5dmAh", mAh);
    lcd.print(mAhbuf);
  }
  if (digitalRead(DWNButton) == 0 && DWNButtonStatus == 0) {
    DWNButtonStatus = 1;
  }
  if (digitalRead(DWNButton) == 1 && DWNButtonStatus == 1) {
    DWNButtonStatus = 0;
    if (mAh > 50) {
      mAh = mAh - 50;
    }
    else mAh = 10000;
    lcd.setCursor(8, 1);
    sprintf(mAhbuf, "%5dmAh", mAh);
    lcd.print(mAhbuf);
  }
}
/* --------------------------------- SET MONTH ---------------------------------*/
void SetMonth() {
  if (SMonthFlag == 0) {
    SCellsFlag = 0;
    SmAhFlag = 0;
    SMonthFlag = 1;
    SYearFlag = 0;
    SCounterFlag = 0;
    WTAGFlag = 0;
    lcd.setCursor(0, 1);
    lcd.print("Set month:       ");
    lcd.setCursor(11, 1);
    sprintf(datebuf, "%2d/%2d", month, year);
    lcd.print(datebuf);
  }
  /* ---------------- UP DOWN BUTTONS POLLING -----------*/
  if (digitalRead(UPButton) == 0 && UPButtonStatus == 0) {
    UPButtonStatus = 1;
  }
  if (digitalRead(UPButton) == 1 && UPButtonStatus == 1) {
    UPButtonStatus = 0;
    if (month < 12) {
      month++;
    }
    else month = 1;
    lcd.setCursor(11, 1);
    sprintf(datebuf, "%2d/%2d", month, year);
    lcd.print(datebuf);
  }
  if (digitalRead(DWNButton) == 0 && DWNButtonStatus == 0) {
    DWNButtonStatus = 1;
  }
  if (digitalRead(DWNButton) == 1 && DWNButtonStatus == 1) {
    DWNButtonStatus = 0;
    if (month > 1) {
      month--;
    }
    else month = 12;
    lcd.setCursor(11, 1);
    sprintf(datebuf, "%2d/%2d", month, year);
    lcd.print(datebuf);
  }
}
/* --------------------------------- SET YEAR ---------------------------------*/
void SetYear() {
  if (SYearFlag == 0) {
    SCellsFlag = 0;
    SmAhFlag = 0;
    SMonthFlag = 0;
    SYearFlag = 1;
    SCounterFlag = 0;
    WTAGFlag = 0;
    lcd.setCursor(0, 1);
    lcd.print("Set year:        ");
    lcd.setCursor(11, 1);
    sprintf(datebuf, "%2d/%2d", month, year);
    lcd.print(datebuf);
  }
  /* ---------------- UP DOWN BUTTONS POLLING -----------*/
  if (digitalRead(UPButton) == 0 && UPButtonStatus == 0) {
    UPButtonStatus = 1;
  }
  if (digitalRead(UPButton) == 1 && UPButtonStatus == 1) {
    UPButtonStatus = 0;
    if (year < 99) {
      year++;
    }
    else year = 19;
    lcd.setCursor(11, 1);
    sprintf(datebuf, "%2d/%2d", month, year);
    lcd.print(datebuf);
  }
  if (digitalRead(DWNButton) == 0 && DWNButtonStatus == 0) {
    DWNButtonStatus = 1;
  }
  if (digitalRead(DWNButton) == 1 && DWNButtonStatus == 1) {
    DWNButtonStatus = 0;
    if (year > 19) {
      year--;
    }
    else year = 99;
    lcd.setCursor(11, 1);
    sprintf(datebuf, "%2d/%2d", month, year);
    lcd.print(datebuf);
  }
}
void SetCounter() {
  if (SCounterFlag == 0) {
    SCellsFlag = 0;
    SmAhFlag = 0;
    SMonthFlag = 0;
    SYearFlag = 0;
    SCounterFlag = 1;
    WTAGFlag = 0;
    lcd.setCursor(0, 1);
    lcd.print("Set counter:    ");
    lcd.setCursor(12, 1);
    sprintf(counterbuf, "%4d", counter);
    lcd.print(counterbuf);
  }
  /* ---------------- UP DOWN BUTTONS POLLING -----------*/
  if (digitalRead(UPButton) == 0 && UPButtonStatus == 0) {
    UPButtonStatus = 1;
  }
  if (digitalRead(UPButton) == 1 && UPButtonStatus == 1) {
    UPButtonStatus = 0;
    if (counter < 1000) {
      counter++;
    }
    else counter = 0;
    lcd.setCursor(12, 1);
    sprintf(counterbuf, "%4d", counter);
    lcd.print(counterbuf);
  }
  if (digitalRead(DWNButton) == 0 && DWNButtonStatus == 0) {
    DWNButtonStatus = 1;
  }
  if (digitalRead(DWNButton) == 1 && DWNButtonStatus == 1) {
    DWNButtonStatus = 0;
    if (counter > 0) {
      counter--;
    }
    else counter = 1000;
    lcd.setCursor(12, 1);
    sprintf(counterbuf, "%4d", counter);
    lcd.print(counterbuf);
  }
}

void WriteTAG() {
  if (WTAGFlag == 0) {
    WTAGFlag = 1;
    SCellsFlag = 0;
    SmAhFlag = 0;
    SMonthFlag = 0;
    SYearFlag = 0;
    SCounterFlag = 0;
    lcd.setCursor(0, 1);
    lcd.print("Waiting TAG...   ");
  }
  /* ------- WAIT FOR TAG -------*/
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
  /* ---------------- WRITE CELL ----------------*/
  block = 1;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  // Write block
  myData = cellsNumber;
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
  /* ---------------- WRITE mAh ----------------*/
  block = 2;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  // Write block
  myData = mAh;
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
  /* ---------------- WRITE MONTH ----------------*/
  block = 4;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  // Write block
  myData = month;
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
  /* ---------------- WRITE YEAR ----------------*/
  block = 5;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  // Write block
  myData = year;
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
  /* ---------------- WRITE COUNTER ----------------*/
  block = 6;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  // Write block
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
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  lcd.setCursor(0, 1);
  lcd.print("Done!            ");
  delay(1500);
  ModeIndex = 2; // return to read mode
}
