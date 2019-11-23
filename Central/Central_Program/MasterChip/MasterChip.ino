
bool setup1[2][5] = {{1, 0, 0, 1, 0}, {0, 1, 0, 1, 0}}; //definition of steps for switching ways
bool setup2[2][5] = {{1, 0, 0, 1, 0}, {1, 0, 0, 1, 0}};
bool setup3[2][5] = {{1, 1, 0, 1, 0}, {1, 0, 0, 1, 0}};
bool setup4[2][5] = {{0, 0, 1, 1, 0}, {1, 0, 0, 0, 1}};


void setup()
{

  Serial.begin(9600);
  pinMode (2, INPUT);   //sensor 1 (sv) pin 0
  pinMode (3, INPUT);   //sensor 1 (jv) pin 1
  pinMode (4, INPUT);   //sensor 1 (jz) pin 2
  pinMode (5, INPUT);   //sensor 1 (sz) pin 3
  pinMode (6, INPUT);   //sensor 2 (sv) pin 4
  pinMode (7, INPUT);   //sensor 2 (jv) pin 5
  pinMode (8, INPUT);   //sensor 2 (jz) pin 6
  pinMode (9, INPUT);   //sensor 2 (sz) pin 7
  pinMode (10, OUTPUT);  //traffic light red (ns)
  pinMode (11, OUTPUT);  //traffic light yellow (ns)
  pinMode (12, OUTPUT);  //traffic light green (ns)
  pinMode (13, OUTPUT);   //traffic light goer red (ns)
  pinMode (A0, OUTPUT);   //traffic light goer green (ns)
  pinMode (A1, OUTPUT);  //traffic light red (ew)
  pinMode (A2, OUTPUT);  //traffic light yellow (ew)
  pinMode (A3, OUTPUT);  //traffic light green (ew)
  pinMode (0, OUTPUT);  //traffic light goer red (ew)
  pinMode (1, OUTPUT);  //traffic light goer green (ew)

}


byte pin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
float rychlost[4] = {0, 0, 0, 0}; //the speed of car/s from one side
int aut[4] = {0, 0, 0, 0};  //the number of cars coming from one side of the road
byte cnt = 0;

bool stav[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool zmena(int pinnum)
{
  bool x = digitalRead(pin[pinnum]);
  bool y = stav[pinnum];
  stav[pinnum] = x;
  if (y != x) return 1;
  return 0;
}


int delta = 0;  //auxiliary variable
bool sempin[2][5] = {{10, 11, 12, 13, A0}, {A1, A2, A3, 0, 1}}; //traffic lights pins
bool svetla[2][5];  //values of traffic lights
bool aktual;  //actual open direction

void crossSet(bool smer)  //sets the open direction of the crossroad
{
  if (aktual == smer) return;
  switch (cnt)
  {
    case 0: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup1[i][f]; delta = millis(); cnt -= 10; break; //sets step 1
    case 1: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup2[i][f]; delta = millis(); cnt -= 10; break; //sets step 2
    case 2: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup3[i][f]; delta = millis(); cnt -= 10; break; //sets step 3
    case 3: for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) svetla[i ^ smer][f] = setup4[i][f]; delta = millis(); cnt -= 10; cnt = 0; aktual = smer; break; //sets step 4
  }
  if (millis() > delta + 2000) cnt += 11; //waiting for 2 seconds each step
  for (int i = 0; i < 2; i++) for (int f = 0; f < 5; f++) digitalWrite(sempin[i][f], svetla[i][f]); //sets the digital ouputs by the "svetla" field

}


byte body_sj = 0;
byte body_zv = 0;

void loop()
{
  
  long t[4];  //auxiliary variable for measuring time from one button to the second one

  for (int i = 0; i < 4; i++) if (zmena(i) && stav[i]) //condition for counting cars and setting the time start
    {
      t[i] = millis();
      aut[i]++;
    }
  for (int i = 0; i < 4; i++) //condition that stops the time count and then calculating the speed of a car
  {
    if (zmena(i + 4) && stav[i + 4])
    {
      rychlost[i] = 2 / (float)(millis() - t[i]) * 1000;  //calculation of the speed (in m/s, the distance between the two buttons is 2 m
    }
  }
 












  delay(10);
}
