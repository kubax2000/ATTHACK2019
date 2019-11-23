
#include <Wire.h>

bool x = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(0, OUTPUT);
  pinMode(A0, INPUT);
  Wire.begin(0x01); //+ kazda jina adresa!
  Wire.setClock(1000);  //+
}

void loop() 
{
  Serial.println(x);
  x = digitalRead(A0);
  digitalWrite(0, x);
  Wire.beginTransmission(0x04); //+ pripoji se k jinemu chipu na adrese 0x04 pro posilani dat
  Wire.write(x);  //posle promennou x
  Wire.endTransmission(); //ukonceni spojeni, nutne!
  delay(50);
}
