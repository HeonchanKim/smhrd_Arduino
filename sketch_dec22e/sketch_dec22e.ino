void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(10, OUTPUT);

  // pinMode INPUT값은 생략가능, OUTPUT은 생략불가능
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  if (sensorValue < 700) {
    digitalWrite(10, HIGH);
  }
  else {
    digitalWrite(10, LOW);
  }
}
