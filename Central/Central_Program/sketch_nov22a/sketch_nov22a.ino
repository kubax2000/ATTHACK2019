
TaskHandle_t Task1;
TaskHandle_t Task2;

void setup()
{

Serial.begin(115200);
pinMode (32, INPUT);   //sensor(sv)
pinMode (33, INPUT);   //sensor(jv)
pinMode (34, INPUT);   //sensor(jz)
pinMode (35, INPUT);   //sensor(sz)






xTaskCreatePinnedToCore
  (
  Task1code, "Task1", 10000, NULL, 1, &Task1, 0
  );

}

bool stav[4];
bool zmena(int pin)
  {
    bool x = digitalRead(pin);
    bool y = stav[pin];
    stav[pin] = x;
    if(y != x) return 1;
    return 0;
  }




void Task1code( void * pvParameters )
{
  long t[4];  //pamet casu

  
    while(true)
     {
      for(i = 0; i < 4; i++) if(zmena(i + 32)) t[i] = millis();
     // for(i = 0; i < 4; i++) if() t[i] = millis();
      
     }
}

  
void loop() 
{
digitalWrite(4, HIGH);


 
}
