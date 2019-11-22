const int sever = 3;
const int jih = 5;
const int vychod = 6;
const int zapad = 9;
const int krizovatka = 10;
int jas;


void setup() {    
    pinMode(sever, OUTPUT);
    pinMode(jih, OUTPUT);
    pinMode(vychod, OUTPUT);
    pinMode(zapad, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    jas += 10;
    if(jas >= 240) jas = 0;
    analogWrite(sever, jas);
    analogWrite(jih, jas);
    analogWrite(vychod, jas);
    analogWrite(zapad, jas);
    analogWrite(krizovatka, jas);
    delay(100);
    Serial.println(jas);
}
