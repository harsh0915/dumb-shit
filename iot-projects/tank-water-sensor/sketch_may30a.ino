int trigPin = 13;
int echoPin = 5;
int duration;
int currentDistance;
int totalDistance = 200;
float waterLevelPercentage;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  currentDistance = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343 for values in cm
  waterLevelPercentage = (currentDistance/(float)totalDistance) * 100;

  Serial.print("Percentage filled : ");
  Serial.print(waterLevelPercentage);
  Serial.println();
}
