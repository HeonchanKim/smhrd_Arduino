void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(12, OUTPUT);
  pinMode(6, INPUT);
  pinMode(13, OUTPUT);
  pinMode(5, INPUT);
  pinMode(11, OUTPUT);
}
void loop() {
  int sensorValue1 = digitalRead(7);
  int sensorValue2 = digitalRead(6);
  int sensorValue3 = digitalRead(5);

  Serial.println(sensorValue1);
  Serial.println(sensorValue2);
  Serial.println(sensorValue3);

  if (sensorValue1 == 1) {
    digitalWrite(12, HIGH);
  }
  else {
    digitalWrite(12, LOW);
  }
  if (sensorValue2 == 1) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  if (sensorValue3 == 1) {
    digitalWrite(11, HIGH);
  }
  else {
    digitalWrite(11, LOW);
  }
}
