int LED = 10;
int buzzer= 13;
int button= 7;
int b2= 2;
int rev;
int tom;
int tg= 1;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
}


void loop() {
  
  tom = 2 * rev;
  rev = analogRead(0);
  if (digitalRead(button)== HIGH){
    tone(buzzer,tom);
  }
  if(tom>1500){
    digitalWrite(LED, HIGH);
    
  }else {
    digitalWrite(LED, LOW);
  }
  if (digitalRead(b2)== HIGH){
    tg * -1;
  }
  if (tg = -1){
  tone(buzzer,tom,1000);
    delay(2000);}
    else {tone(buzzer,0,0);
  }
   
}
