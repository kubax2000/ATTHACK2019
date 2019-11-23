#include <Wire.h>
#include <FadeLed.h>

//pins for lamp output
const int s = 5; //north
const int j = 6; //south
const int v = 9; //east
const int z = 10; //west
const int k = 11; //crossroad center

//PIR input pins
const int pin_p_s = 2;
const int pin_p_j = 3;
const int pin_p_v = 4;
const int pin_p_z = 7;

//Defining pins for led fading
FadeLed sever(s);
FadeLed jih(j);
FadeLed vychod(v);
FadeLed zapad(z);
FadeLed krizovatka(k);

//PIR on/off
bool p_s;
bool p_j;
bool p_v;
bool p_z;

int ft; //Night sensor reading
bool noc; //Is it night?
bool car; //Is there a car on the crossroad
bool p_car; //Previous state of car
byte I2C_recieve;


void setup() {
    //Slave no.4 ready to recieve
    Wire.begin(0x04);
    Wire.setClock(1000);
    Wire.onReceive(prichoziZnakI2C);
    
    pinMode(s, OUTPUT);
    pinMode(j, OUTPUT);
    pinMode(v, OUTPUT);
    pinMode(z, OUTPUT);
    pinMode(k, OUTPUT);

    pinMode(pin_p_s, INPUT);
    pinMode(pin_p_j, INPUT);
    pinMode(pin_p_v, INPUT);
    pinMode(pin_p_z, INPUT);
    
    //Night sensor
    pinMode(A0, INPUT);

    //Time for the fade effect to take place for each section of LEDs
    sever.setTime(5000, true);
    jih.setTime(5000, true);
    vychod.setTime(5000, true);
    zapad.setTime(5000, true);
    krizovatka.setTime(5000, true);
    
    Serial.begin(9600);
}

//Function for recieving data
void prichoziZnakI2C() {
 I2C_recieve = Wire.read();
}

void loop() {
    FadeLed::update(); //Needed for the fade effect to work properly
    Serial.println(I2C_recieve);
    if(I2C_recieve <= 1) car = I2C_recieve;
    
    p_s = digitalRead(pin_p_s);
    //Serial.println(p_s);
    p_j = digitalRead(pin_p_j);
    p_v = digitalRead(pin_p_v);
    p_z = digitalRead(pin_p_z);
    ft = analogRead(A0);

    if(ft < 800) { //It's night and everything runs
      noc = 1;
    }
    else if(ft >= 800){ //Daytime-turn off all the lights just in case
      noc = 0;
      sever.set(0);
      jih.set(0);
      vychod.set(0);
      zapad.set(0);
      krizovatka.set(0);
    }
    //Serial.println(car);

    
    //Car approaching, turning the center lights on
    if(car == 1 && noc == 1) {
      krizovatka.set(255);
    }
    else if(p_car == 1 && car == 0){
      krizovatka.set(0);
    }
    p_car = car;

    //North and center street light activated
    if(p_s == 1 && noc == 1) {
      sever.set(255);
      krizovatka.set(255);
    }
    else {
      sever.set(0);
    }

    //South and center street light activated
    if(p_j == 1 && noc == 1) {
      jih.set(255);
      krizovatka.set(255);
    }
    else {
      jih.set(0);
    }

    //East and center street light activated
    if(p_v == 1 && noc == 1) {
      vychod.set(255);
      krizovatka.set(255);
    }
    else {
      vychod.set(0);
    }

    //West and center street light activated
    if(p_z == 1 && noc == 1) {
      zapad.set(255);
      krizovatka.set(255);
    }
    else {
      zapad.set(0);
    }

    if(car == 0 && p_s == 0 && p_j == 0 && p_v == 0 && p_z == 0) krizovatka.set(0);
    
}
