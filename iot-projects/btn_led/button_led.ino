void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D8, INPUT);
}

void loop() {
  int state = digitalRead(D8);
  digitalWrite(D1, state);
}
