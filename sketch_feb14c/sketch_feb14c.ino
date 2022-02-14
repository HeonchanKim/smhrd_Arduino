int cdsPin = 2;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // 단, Wemos board는 12비트 값으로 출력(0 ~ 4095)
  int sensorValue = analogRead(cdsPin);
  Serial.println(sensorValue);
  delay(10);

}
