
int led = 8;
int buzzer = 13;

void setup()
{
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop()
{

  int sensorValue = analogRead(A0);

    if(sensorValue < 300){
      tone(buzzer, 0, 100);
      digitalWrite(led, HIGH);
      
    }else if(sensorValue >= 600){
      tone(buzzer, 0, 100);
      digitalWrite(led, HIGH);  
      delay(300);                      
      digitalWrite(led, LOW);
      delay(300);
    
    }else{
       tone(buzzer, sensorValue);
       digitalWrite(led, LOW);
       
    }
    
}
