#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#define ROWS 4
#define COLS 4

#define SDA_PIN 9
#define RST_PIN 8

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte colPins[COLS] = {5,4,3,2};
byte rowPins[ROWS] = {9,8,7,6};
bool login = false; 
MFRC522 rfid(SDA_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);
Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

void def(){
  char Str1[]= "Welcome Indetify"; 
  char Str2[]= "yourself with ID";
   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(Str1);
    lcd.setCursor(0,1);
    lcd.print(Str2);
    delay(150);
}

   
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  
  Serial.println("Power ON");
  lcd.begin(16,2);
}


void loop()
  {
 
  if(!login){

    def();
    Serial.println("Login start");
    if ( ! rfid.PICC_IsNewCardPresent()) {
      return;
    }
    
    if ( ! rfid.PICC_ReadCardSerial()) {
      return;
    }
    String id= "";
    Serial.print("Card: "); 
    for( byte i = 0; i < rfid.uid.size; i++){
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    id.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : " "));
    id.concat(String(rfid.uid.uidByte[i], HEX));
  } 
  
    Serial.println();
    Serial.print("Info: ");
    id.toUpperCase();
    if (id.substring(1) == "59 5D 94 A2")
    {
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Authorizet access");
      Serial.println("Authorized access");
      Serial.println();
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      login = true;
    }
   
    else   {
      Serial.println("Access denied");
      delay(3000);
    }
  }
 
 
  delay(150);
} 



  
 
