void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  int sensorValue1 = digitalRead(3);

  if (sensorValue1 == 1) {
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(11, HIGH);
    delay(5000);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
  }
}
