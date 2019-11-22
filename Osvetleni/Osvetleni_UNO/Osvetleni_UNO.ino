const int s = 5;
const int j = 6;
const int v = 9;
const int z = 10;
const int k = 11;

const int pin_p_s = 2;
const int pin_p_j = 3;
const int pin_p_v = 4;
const int pin_p_z = 7;

int s_jas;
int j_jas;
int v_jas;
int z_jas;
int k_jas;

long t;

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
/*    s_jas += 10;
    j_jas += 10;
    v_jas += 10;
    z_jas += 10;
    k_jas += 10;
    
    if(s_jas >= 240) s_jas = 0;
    if(j_jas >= 240) j_jas = 0;
    if(v_jas >= 240) v_jas = 0;
    if(z_jas >= 240) z_jas = 0;
    if(k_jas >= 240) k_jas = 0;
*/  
    digitalRead(pin_p_s);
    digitalRead(pin_p_j);
    digitalRead(pin_p_v);
    digitalRead(pin_p_z);
    
    if((pin_p_s == 1)&&(s_jas = 0)){
          
    }
    
    analogWrite(s, s_jas);
    analogWrite(j, j_jas);
    analogWrite(v, v_jas);
    analogWrite(z, z_jas);
    analogWrite(k, k_jas);

    Serial.println(s_jas);
    delay(100);
}
