void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);

  int changeValue0 = sensorValue0 / 4;
  int changeValue1 = sensorValue1 / 4;
  int changeValue2 = sensorValue2 / 4;

  analogWrite(9, changeValue0);
  analogWrite(10, changeValue1);
  analogWrite(11, changeValue2);
  
//  digitalWrite(9, HIGH); // 빨간색
//  digitalWrite(10, LOW); // 파란색
//  digitalWrite(11, HIGH); // 초록색

}
