#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#define ROWS 4
#define COLS 4




LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte colPins[COLS] = {5,4,3,2};
byte rowPins[ROWS] = {9,8,7,6};

Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

 
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);

  Serial.println("Power ON");
  lcd.begin(16,2);
}
 
 
void loop()
{

 lcd.clear();
 lcd.setCursor(0,0); 
 char Str[] = {"Welcome, indetify yourself with ID"};

 lcd.print(Str);
 int size = sizeof(Str);
 for(int i = 0;i < size ;i++){
   delay(500);
   lcd.scrollDisplayLeft();
   
  
 }

  
 
 char pressed = keypad.getKey();
 lcd.setCursor(0,1);
 lcd.leftToRight();
 Serial.println(pressed);
 lcd.print(pressed);
 delay(1000);
}
