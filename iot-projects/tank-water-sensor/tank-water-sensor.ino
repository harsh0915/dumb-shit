#include "EspMQTTClient.h"

int trig_pin = 13;       
int echo_pin = 5;
int duration;
float distance;
int total_distance = 11;
float water_level_percentage;

EspMQTTClient client(
  "Harsh",
  "Test123!",
  "harsh-raspberry-pi-0wh.local",  // broker
  "WaterSensor",     // unique client name 
  1883              // mqtt port, default to 1883
);

void setup() {
  Serial.begin(9600);
  client.enableDebuggingMessages(); 
  //Define inputs and outputs
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void onConnectionEstablished()
{
  Serial.println("Connection established!");
  // Publish a message to "mytopic/test"
  client.publish("sensors/water-sensor", "55"); // You can activate the retain flag by setting the third parameter to true
}
 
void loop() {
  // the sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH,26000); // read in times pulse
  distance= duration/58;//convert to cm
  Serial.print(distance);
  Serial.println(" cm");
  // Wait 50ms before next ranging
  delay(50);

  water_level_percentage=((float) (total_distance-distance)/(float)total_distance)*100;
  Serial.println(distance);
  String message = String(distance)+" cm";

  client.publish("sensors/water-sensor", message);

  client.loop();
}