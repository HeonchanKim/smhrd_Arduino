void setup() {

}

void loop() {
  int sensorValue1 = digitalRead(3);
  int sensorValue2 = digitalRead(4);
  int sensorValue3 = digitalRead(5);
  int sensorValue4 = digitalRead(6);
  int sensorValue5 = digitalRead(7);

  
  if (sensorValue1 == 1) {
    tone(8, 262, 100);
  }
  if (sensorValue2 == 1) {
    tone(8, 294, 100);
  }
  if (sensorValue3 == 1) {
    tone(8, 330, 100);
  }
  if (sensorValue4 == 1) {
    tone(8, 349, 100);
  }
  if (sensorValue5 == 1) {
    tone(8, 392, 100);
  }



}
