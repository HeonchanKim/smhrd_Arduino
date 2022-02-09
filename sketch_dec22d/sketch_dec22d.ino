void setup() {
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

void loop() {
  int buttonState1 = digitalRead(2);
  int buttonState2 = digitalRead(3);
  int buttonState3 = digitalRead(4);

  if (buttonState1 == 1) {
    analogWrite(10, 0);
  }
  if (buttonState2 == 1) {
    analogWrite(10, 127);
  }
  if (buttonState3 == 1) {
    analogWrite(10, 255);
  }

}
