  int buz = 8;
  int but = 10;
  int led = 13;
  

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(but, INPUT);
 

}

void loop() {

  int buttonState = digitalRead(but);

  if(buttonState == HIGH) {
    tone(buz, 1000, 500);
    delay(499);
    tone(buz, 0, 1);
    delay(500);
 
  }else{
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }

}
