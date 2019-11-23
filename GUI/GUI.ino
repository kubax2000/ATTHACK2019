#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define ROWS 4 //rows of Keypad
#define COLS 4 //cols of Keypad

#define SDA_PIN 9 // SDA pin RFID
#define RST_PIN 8 // RST pin RFID

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};  //all keys

int lcd_col = 16; //lcd col
int lcd_row = 2;  //lcd row


byte colPins[COLS] = {30,28,26,24}; //set pins of keypads col
byte rowPins[ROWS] = {38,36,34,32}; //set pins of keypads row
bool login = false;                 //RFID check 
              
MFRC522 rfid(SDA_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);
Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

String menu_opt[]= {"------MENU------", "NORMAL", "OFF", "KEEP LIGHTS ON"};   //Options in menu
byte data[] = {01 /*Normal*/,00 /*OFF*/,02 /*KEEP LIGHTS ON*/};     //Data of menu

void def_Text(){            //function for default text, that displays on LCD              
  char Str1[]= "Welcome Indetify"; 
  char Str2[]= "yourself with ID";
   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(Str1);
    lcd.setCursor(0,1);
    lcd.print(Str2);
    delay(150);
}
/* //Text Center (Margin)
void centerText(){
   int size = sizeof(menu_opt[0]) % lcd_col; 
  }*/

int opt = 1;  //variable of options + options which are send 
void menu(char pressed){      //Menu options choose
  
  
  switch (pressed){     
    case 'A': 
    //Go up in menu
          opt--;
          if(opt<=0){
            opt=3;
          }
          else if(opt>=4)opt = 1;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(menu_opt[0]);
          lcd.setCursor(0,1);
          lcd.print(menu_opt[opt]); //changemenu option
          Serial.print("actual opt: ");
          Serial.println(opt);
          Serial.println("UP");
          Serial.print("after up: ");
          Serial.println(opt);
          break;
          
    case 'B':         //Go down in menu
          opt++;
          if(opt>=4){
            opt = 1;
          }
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(menu_opt[0]);
          lcd.setCursor(0,1);
          lcd.print(menu_opt[opt]); //changemenu option
          Serial.println("Down");
          Serial.print("actual opt: ");
          Serial.println(opt);
          
          Serial.print("after down: ");
          Serial.println(opt);
          
          
          break;
          
      
    case '#': 
          Transmission(opt);
          Serial.print("Sending: ");
          Serial.println(data[opt]);
    default:
      break;
  }
  
}


void Transmit(int o){
  Wire.beginTransmission();
  Wire.write(data[o]);
  Wire.endTransmission();  
}
void menu_def(){        //Default menu, that shows after you logged in
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menu_opt[0]);
  lcd.setCursor(0,1);
  lcd.print(menu_opt[1]);
}
void setup()
{
  Wire.begin(0x02);       // join i2c bus with address #0x02
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);   // start serial for output
  SPI.begin();
  rfid.PCD_Init();
  
  Serial.println("Power ON"); 
  lcd.begin(16,2);
}

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
void loop()
  {
 
  if(!login){       //checks if user is logged in already

    def_Text();      //prints default text 
    if ( ! rfid.PICC_IsNewCardPresent()) {    // Look for new cards
      return;
    }    
    if ( ! rfid.PICC_ReadCardSerial()) {    // Select one of the cards
      return;
    }
    
    String id= "";    
    Serial.print("Card: "); 
    for( byte i = 0; i < rfid.uid.size; i++){         //Transfering tag to hex format
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    id.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : " "));
    id.concat(String(rfid.uid.uidByte[i], HEX));
    } 
  
    Serial.println();
    Serial.print("Info: ");
    
    id.toUpperCase();
    if (id.substring(1) == "59 5D 94 A2")   //Checking TAG if its autorized user
    {
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Verified");
      Serial.println("Authorizet access");
      rfid.PICC_HaltA();                //Ending and securing 
      rfid.PCD_StopCrypto1();
      login = true;               // variable is changet to true => user is logged. It wont detect Tag again.
      delay(1000);
      menu_def();                 //displaying default menu
    }
   
    else   {                   //secont part of Checking TAG if its autorized user 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Access denied");
      lcd.setCursor(0,1);
      Serial.println("Access denied");
      delay(3000);
    }
  }

  char key = keypad.getKey();    //pressing key on keypad
  if(key != NO_KEY){      //if chracter was pressed
      menu(key);          //choosing options in menu
  }

  
 
  delay(150);
} 



  
 
