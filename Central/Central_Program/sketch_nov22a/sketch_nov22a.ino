
TaskHandle_t Task1;
TaskHandle_t Task2;

void setup()
{

Serial.begin(115200);
pinMode (2, OUTPUT);
pinMode (4, OUTPUT);



xTaskCreatePinnedToCore
  (
  Task1code, "Task1", 10000, NULL, 1, &Task1, 0
  );

}

void Task1code( void * pvParameters )
  {
    digitalWrite(2, HIGH);
  }


  
void loop() 
{
digitalWrite(4, HIGH);


 
}
