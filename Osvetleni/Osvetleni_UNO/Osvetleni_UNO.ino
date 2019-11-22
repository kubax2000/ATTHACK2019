const int s = 5;
const int j = 6;
const int v = 9;
const int z = 10;
const int k = 11;

const int pin_p_s = 2;
const int pin_p_j = 3;
const int pin_p_v = 4;
const int pin_p_z = 7;

bool p_s;
bool p_j;
bool p_v;
bool p_z;

bool z_p_s;
bool z_p_j;
bool z_p_v;
bool z_p_z;

int s_jas;
int j_jas;
int v_jas;
int z_jas;
int k_jas;

bool s_sviti;
bool j_sviti;
bool v_sviti;
bool z_sviti;

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
    
    Serial.begin(9600);
}

void loop() {
    p_s = digitalRead(pin_p_s);
    Serial.println(p_s);
    p_j = digitalRead(pin_p_j);
    p_v = digitalRead(pin_p_v);
    p_z = digitalRead(pin_p_z);

/*
    if(p_s == 0 && s_sviti == 1){
      s_jas--;
      //Serial.println(s_jas);     
    }
    if(s_jas = 0) s_sviti = 0;
*/    

    if(p_s == 1 && s_sviti == 0){
      s_jas++;
      //Serial.println(s_jas);     
    }
    if(s_jas >= 180) {
      s_sviti = 1;
      s_jas = 255;
    }

    if(p_j == 1 && j_sviti == 0){
      j_jas++;
      //Serial.println(j_jas);     
    }
    if(j_jas >= 180) {
      j_sviti = 1;
      j_jas = 255;
    }

    if(p_v == 1 && v_sviti == 0){
      v_jas++;
      //Serial.println(v_jas);     
    }
    if(v_jas >= 180) {
      v_sviti = 1;
      v_jas = 255;
    }

    if(p_z == 1 && z_sviti == 0){
      z_jas++;
      //Serial.println(z_jas);     
    }
    if(z_jas >= 180) {
      z_sviti = 1;
      z_jas = 255;
    }
    
    analogWrite(s, s_jas);
    analogWrite(j, j_jas);
    analogWrite(v, v_jas);
    analogWrite(z, z_jas);
    analogWrite(k, k_jas);

    //Serial.println(s_jas);
    delay(10);
}
