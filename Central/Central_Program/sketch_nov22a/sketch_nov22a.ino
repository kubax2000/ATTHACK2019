
TaskHandle_t Task1;

bool setup1[2][5] = {{1, 0, 0, 1, 0},{0, 1, 0, 1, 0}};
bool setup2[2][5] = {{1, 0, 0, 1, 0},{1, 0, 0, 1, 0}};
bool setup3[2][5] = {{1, 1, 0, 1, 0},{1, 0, 0, 1, 0}};
bool setup4[2][5] = {{0, 0, 1, 1, 0},{1, 0, 0, 0, 1}};




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
pinMode (27, OUTPUT);  //semafor cervena (sj)
pinMode (26, OUTPUT);  //semafor zluta (sj)
pinMode (25, OUTPUT);  //semafor zelena (sj)
pinMode (2, OUTPUT);   //semafor chodci cervena (sj)
pinMode (4, OUTPUT);   //semafor chodci zelena (sj)
pinMode (18, OUTPUT);  //semafor cervena (vz)
pinMode (19, OUTPUT);  //semafor zluta (vz)
pinMode (21, OUTPUT);  //semafor zelena (vz)
pinMode (22, OUTPUT);  //semafor chodci cervena (vz)
pinMode (23, OUTPUT);  //semafor chodci zelena (vz)



xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0);
}

int delta = 0;
bool sempin[2][5] = {{27, 26, 25, 2, 4},{18, 19, 21, 22, 23}};
byte pin[8] = {32, 33, 34, 35, 12, 13, 14, 15};
float rychlost[4] = {0, 0, 0, 0};
int aut[4] = {0, 0, 0, 0};
byte cnt = 0;

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

bool svetla[2][5];
bool aktual;
  void crossSet(bool smer)
  {
  if(aktual == smer) return;
  switch(cnt)
  {
   case 0: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup1[i][f]; delta = millis(); cnt -= 10; break;
   case 1: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup2[i][f]; delta = millis(); cnt -= 10; break;
   case 2: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup3[i][f]; delta = millis(); cnt -= 10; break;
   case 3: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup4[i][f]; delta = millis(); cnt -= 10; cnt = 0; aktual = smer; break;
   }
  if(millis() > delta + 2000) cnt += 11;
  for(int i = 0; i < 2; i++) for(int f = 0; f < 5; f++) digitalWrite(sempin[i][f], svetla[i][f]);
    
  }
  


  
void loop() 
{



  delay(50);
}
