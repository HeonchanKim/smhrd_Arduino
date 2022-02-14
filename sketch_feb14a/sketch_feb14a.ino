int ledPin = 18;

void setup() {
  pinMode(ledPin,OUTPUT);
}

void loop() {
  digitalWrite(ledPin,1);
  delay(1000);
  digitalWrite(ledPin,0);
  delay(1000);
}
