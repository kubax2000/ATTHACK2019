
TaskHandle_t Task1;


void setup()
{
Serial.begin(9600);  
pinMode (32, INPUT);   //sensor 1 (sv) pin 0
pinMode (33, INPUT);   //sensor 1 (jv) pin 1
pinMode (34, INPUT);   //sensor 1 (jz) pin 2
pinMode (35, INPUT);   //sensor 1 (sz) pin 3
pinMode (12, INPUT);   //sensor 2 (sv) pin 4
pinMode (13, INPUT);   //sensor 2 (jv) pin 5
pinMode (14, INPUT);   //sensor 2 (jz) pin 6
pinMode (15, INPUT);   //sensor 2 (sz) pin 7
pinMode (27, OUTPUT);  //semafor cervena
pinMode (26, OUTPUT);  //semafor zluta
pinMode (25, OUTPUT);  //semafor zelena
pinMode (2, OUTPUT);   //semafor chodci cervena
pinMode (4, OUTPUT);   //semafor chodci zelena



xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
}

byte pin[8] = {32, 33, 34, 35, 12, 13, 14, 15};
float rychlost[4] = {0, 0, 0, 0};
int aut[4] = {0, 0, 0, 0};


bool stav[8] = {0, 0, 0, 0, 0, 0, 0, 0};
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
      for(int i = 0; i < 4; i++) if(zmena(i) && stav[i])
      {

      t[i] = millis();
      aut[i]++;
      
      }
      for(int i = 0; i < 4; i++) 
      {
        if(zmena(i + 4) && stav[i + 4])
        {
        rychlost[i] = 2 / (float)(millis() - t[i]) * 1000;  //vzdalennost senzoru = 2 m
        }
      }
      delay(50);
     }
}

byte body_sj = 0;
byte body_zv = 0;
  
void loop() 
{

  delay(50);
}
