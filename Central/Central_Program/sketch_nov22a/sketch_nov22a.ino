
TaskHandle_t Task1;
TaskHandle_t Task2;

void setup()
{

Serial.begin(115200);
pinMode (32, INPUT);   //sensor 1 (sv) pin 1
pinMode (33, INPUT);   //sensor 1 (jv) pin 2
pinMode (34, INPUT);   //sensor 1 (jz) pin 3
pinMode (35, INPUT);   //sensor 1 (sz) pin 4
pinMode (12, INPUT);   //sensor 2 (sv) pin 5
pinMode (13, INPUT);   //sensor 2 (jv) pin 6
pinMode (14, INPUT);   //sensor 2 (jz) pin 7
pinMode (15, INPUT);   //sensor 2 (sz) pin 8



xTaskCreatePinnedToCore
  (
  Task1code, "Task1", 10000, NULL, 1, &Task1, 0
  );

}

byte pin[8] = {32, 33, 34, 35, 12, 13, 14, 15};
float rychlost[4];



bool stav[8];
bool zmena(int pinnum)
  {
    bool x = digitalRead(pin[pinnum]);
    bool y = stav[pinnum];
    stav[pinnum] = x;
    if(y != x) return 1;
    return 0;
  }




void Task1code( void * pvParameters )
{
  long t[4];  //pamet casu

  
    while(true)
     {
      for(int i = 0; i < 4; i++) if(zmena(pin[i])) t[i] = millis();
      for(int i = 0; i < 4; i++) if(zmena(pin[i + 4])) rychlost[i] = 2 / (millis() - t[i]) * 1000; //vzdalennost senzoru = 2 m







      
     }
}

  
void loop() 
{
digitalWrite(4, HIGH);


 
}
