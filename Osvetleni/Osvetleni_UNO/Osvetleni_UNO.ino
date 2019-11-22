#include <FadeLed.h>

const int s = 5;
const int j = 6;
const int v = 9;
const int z = 10;
const int k = 11;

const int pin_p_s = 2;
const int pin_p_j = 3;
const int pin_p_v = 4;
const int pin_p_z = 7;

FadeLed sever(s);
FadeLed jih(j);
FadeLed vychod(v);
FadeLed zapad(z);
FadeLed krizovatka(k);

bool p_s;
bool p_j;
bool p_v;
bool p_z;

bool noc;
int ft;
bool car;
bool p_car;

void setup() {
    pinMode(s, OUTPUT);
    pinMode(j, OUTPUT);
    pinMode(v, OUTPUT);
    pinMode(z, OUTPUT);
    pinMode(k, OUTPUT);

    pinMode(pin_p_s, INPUT);
    pinMode(pin_p_j, INPUT);
    pinMode(pin_p_v, INPUT);
    pinMode(pin_p_z, INPUT);

    pinMode(A1, INPUT);

    pinMode(A0, INPUT);

    sever.setTime(5000, true);
    jih.setTime(5000, true);
    vychod.setTime(5000, true);
    zapad.setTime(5000, true);
    krizovatka.setTime(5000, true);
    
    Serial.begin(9600);
}

void loop() {
    FadeLed::update();

    p_s = digitalRead(pin_p_s);
    //Serial.println(p_s);
    p_j = digitalRead(pin_p_j);
    p_v = digitalRead(pin_p_v);
    p_z = digitalRead(pin_p_z);
    ft = analogRead(A0);

    if(analogRead(A1) > 10) car = 1;
    else car = 0;
    Serial.println(car);

    if(ft < 800) {
      noc = 1;
    }
    else if(ft >= 800){
      noc = 0;
      sever.set(0);
      jih.set(0);
      vychod.set(0);
      zapad.set(0);
      krizovatka.set(0);
    }
    //Serial.println(noc);

    
    
    if(car == 1 && noc == 1) {
      krizovatka.set(255);
    }
    else if(p_car == 1 && car == 0){
      krizovatka.set(0);
    }

    p_car = car;

    if(p_s == 1 && noc == 1) {
      sever.set(255);
      krizovatka.set(255);
    }
    else {
      sever.set(0);
    }

    if(p_j == 1 && noc == 1) {
      jih.set(255);
      krizovatka.set(255);
    }
    else {
      jih.set(0);
    }

    if(p_v == 1 && noc == 1) {
      vychod.set(255);
      krizovatka.set(255);
    }
    else {
      vychod.set(0);
    }

    if(p_z == 1 && noc == 1) {
      zapad.set(255);
      krizovatka.set(255);
    }
    else {
      zapad.set(0);
    }
    
    if(car == 0 && p_s == 0 && p_j == 0 && p_v == 0 && p_z == 0) krizovatka.set(0);
    
}
