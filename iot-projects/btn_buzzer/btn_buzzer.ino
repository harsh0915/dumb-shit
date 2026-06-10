void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D8, INPUT);
}

void loop() {
  int state = digitalRead(D8);
  if(state == HIGH)
    tone(D1,400); 
  else
   noTone(D1);
}