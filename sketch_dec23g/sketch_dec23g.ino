#include <Servo.h>
Servo myservo;

void setup() {
  myservo.attach(8);
  Serial.begin(9600);
}
void loop() {
  
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  int changeValue = map(sensorValue, 0, 1023, 0, 179);

  myservo.write(changeValue);
}
