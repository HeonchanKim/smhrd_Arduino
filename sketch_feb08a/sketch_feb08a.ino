void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * 5.0 / 1024.0;
  float tmpVal = (voltage - 0.5) * 100;

  if (tmpVal >= 23) {
    tone(13, 392, 100);
  }

  Serial.println(tmpVal);
  delay(100);

}
