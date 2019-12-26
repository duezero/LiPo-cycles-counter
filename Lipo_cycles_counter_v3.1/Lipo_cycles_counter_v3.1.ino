/*
   LIPO CYCLES COUNTER v3.1
*/

/*
   --------------------------------------
               MFRC522      Arduino
               Reader/PCD   Uno/101
   Signal      Pin          Pin
   --------------------------------------
   RST/Reset   RST          9
   SPI SS      SDA(SS)      10
   SPI MOSI    MOSI         11 / ICSP-4
   SPI MISO    MISO         12 / ICSP-1
   SPI SCK     SCK          13 / ICSP-3
*/

/*
    BLOCK 1 CELLS NUMBER
    BLOCK 2 mAh
    BLOCK 4 MONTH
    BLOCK 5 YEAR
    BLOCK 6 COUNTER
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 4, en = 3, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

uint32_t myData; // data to write into nfc tag
uint32_t myDataRead[1]; // data read from nfc tag
byte block = 1; // nfc tag block
byte ModeButton = 5;
byte UPButton = 6;
byte DWNButton = 7;
byte ExitButton = 8;
byte ModeIndex = 1; // 1 counter mode, 2 read mode, 3 set mode
byte MenuIndex = 1; // 1 set cell, 2 set mAh, 3 set month, 4 set year, 5 set counter, 6 wite tag
bool ModeButtonStatus = 0;
bool S_ModeButtonStatus = 1; //utilized in SetMode
bool ExitButtonStatus = 0;
bool UPButtonStatus = 0;
bool DWNButtonStatus = 0;
bool CModeFlag = 0;
bool RModeFlag = 0;
bool SModeFlag = 0;
bool SCellsFlag = 0;
bool SmAhFlag = 0;
bool SMonthFlag = 0;
bool SYearFlag = 0;
bool SCounterFlag = 0;
bool WTAGFlag = 0;
byte cellsNumber = 1; // number of lipo cells
int mAh = 1300; // lipo capacity
char mAhbuf[9];
byte month = 1;
byte year = 19;
char datebuf[6];
int counter = 0; // number of cycles
int oldcounter = 0;
char counterbuf[5];
char RModebuf[17];

uint32_t previousMillis = 0;

MFRC522::StatusCode status;

void setup() {
  pinMode(ModeButton, INPUT_PULLUP); // hardware debounce on push buttons !! 220R 100nF
  pinMode(UPButton, INPUT_PULLUP);
  pinMode(DWNButton, INPUT_PULLUP);
  pinMode(ExitButton, INPUT_PULLUP);
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  lcd.begin(16, 2);
  Serial.begin(9600);        // Initialize serial communications with the PC
  /* splash screen*/
  lcd.setCursor(0, 0);
  lcd.print("LiPo Cycles");
  lcd.setCursor(0, 1);
  lcd.print("Counter v3.1");
  //Serial.println(F("Write one block on a MIFARE PICC "));
  delay(2000);
  lcd.clear();
}

void loop() {

  /* ---------------- BUTTONS POLLING -----------*/
  if (digitalRead(ModeButton) == 0 && ModeButtonStatus == 0) { //short press modebutton to change from readmode to countermode
    previousMillis = millis();
    while (digitalRead(ModeButton) == 0 &&  ModeIndex != 3) {
      if ((millis() - previousMillis) > 2000) { // press modebutton for more than 2 seconds to enter SetMode
        ModeIndex = 3;
      }
    }
    ModeButtonStatus = 1;
  }
  if (digitalRead(ModeButton) == 1 && ModeButtonStatus == 1) {
    ModeButtonStatus = 0;
    if (ModeIndex == 2) {
      ModeIndex = 1;
    }
    else if (ModeIndex == 1) {
      ModeIndex = 2;
    }
  }


  /*----------------- MODE SELECTION ---------------*/
  switch (ModeIndex) {
    case (1):
      CounterMode();
      break;
    case (2):
      ReadMode();
      break;
    case (3):
      SetMode();
      break;
  }
}
