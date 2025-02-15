int buz = 10;
int led = 13;
int but = 8;
float c = 527.47;
float d = 469.92;
float g = 352.04;
float gb = 372.98;
float tempo = 76.9230769;

void setup() {
  pinMode(led,OUTPUT);
  pinMode(but,INPUT);
  pinMode(buz,OUTPUT);
}

void loop() {
  int buttonstate = digitalRead(but);
  if(buttonstate == HIGH) {
    digitalWrite(led, HIGH);
    delay(tempo*2);
    tone(buz,c,tempo);
    delay(tempo*5);
    tone(buz,gb,tempo);
    delay(tempo*2);
    tone(buz,c,tempo);
    delay(tempo*2);
    tone(buz,d,tempo);
    delay(tempo*2);
    tone(buz,d,tempo);
    delay(tempo*2);
    tone(buz,c,tempo);
    delay(tempo);
    tone(buz,g,tempo);
    delay(tempo*3);

    
   //primeiro verso 
 
  }
}

// MEMBROS: João Moniz nº 20220550, Tiago Estrela nº20220534, Tomás Salgueiro nº20220589
