int ledPin = 9;
int btn = 2;
int cnt = 0; // 버튼 누른 횟수를 저장하는 변수

boolean check = true;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState2 = digitalRead(btn);


  if (buttonState2 == 1) {
    if (check == true) {
      cnt++;
      check = false;
    }
  } else {
    check = true;
  }
  if (cnt % 3 == 0) {
    analogWrite(ledPin, 0);
  } else if (cnt % 3 == 1) {
    analogWrite(ledPin, 127);
  } else if (cnt % 3 == 2) {
    analogWrite(ledPin, 255);
  }

  Serial.println(cnt);
}
