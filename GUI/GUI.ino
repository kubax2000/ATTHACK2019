#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#define ROWS 4
#define COLS 4

#define SDA_PIN 36
#define RST_PIN 28

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte colPins[COLS] = {5,4,3,2};
byte rowPins[ROWS] = {9,8,7,6};
 
MFRC522 rfid(SDA_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);
Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);



 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  
  Serial.println("Power ON");
  lcd.begin(16,2);

  
}

 
void Pressed () {
  
  }

void loop()
{
/*
 lcd.clear();
 lcd.setCursor(0,0); 
 char Str[] = {"Welcome, indetify yourself with ID"};

 lcd.print(Str);
 int size = sizeof(Str);
 for(int i = 0;i < size ;i++){
   delay(500);
   lcd.scrollDisplayLeft();
 }*/
  

   if ( ! rfid.PICC_IsNewCardPresent()) {
   return;
  }

  if ( ! rfid.PICC_ReadCardSerial()) {
   return;
  }
 MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 
 Serial.print("Card: ");
 Serial.println(rfid.PICC_GetTypeName(piccType));

  if(piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
  piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
  piccType != MFRC522::PICC_TYPE_MIFARE_4K){
    Serial.println("Máte špatná čip (Neni podporován"); 
    return;
  }
 
 for( byte i = 0; i < rfid.uid.size; i++){
  Serial.print(rfid.uid.uidByte[i] < 0x10 ? "" : "0");
  Serial.print(rfid.uid.uidByte[i], HEX);

 }
 

 /* rfid.PICC_HaltA();
  return 1;
  */

  
 delay(1000);
}
