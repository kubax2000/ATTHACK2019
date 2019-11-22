void setup() {
    byte led_sever = 3;
    pinMode(3, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW); 
    delay(1000);  
}
