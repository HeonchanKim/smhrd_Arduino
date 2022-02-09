void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  int sensorValue0 = analogRead(A0);
  int changeValue0 = map(sensorValue0, 0, 1023, 0, 255);
  int sensorValue1 = analogRead(A1);
  int changeValue1 = map(sensorValue1, 0, 1023, 0, 255);
  int sensorValue2 = analogRead(A2);
  int changeValue2 = map(sensorValue2, 0, 1023, 0, 255);

  analogWrite(9, changeValue0);
  analogWrite(10, changeValue1);
  analogWrite(11, changeValue2);

  //  digitalWrite(9, HIGH); // 빨간색
  //  digitalWrite(10, LOW); // 파란색
  //  digitalWrite(11, HIGH); // 초록색





}
