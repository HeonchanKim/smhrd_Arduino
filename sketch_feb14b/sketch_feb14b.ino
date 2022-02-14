int ch = 0;
int freq = 5000;
int resolution = 8;
//해상도 8비트, 16비트까지 설정 가능

int ledPin1 = 18; 
int ledPin2 = 19;

void setup() {
  ledcSetup(ch, freq, resolution); //PWM 채널에 진동수, 해상도를 결정

  ledcAttachPin(ledPin1, ch);
  ledcAttachPin(ledPin2, ch);
}

void loop() {
  ledcWrite(ch, 0);
  delay(1000);
  ledcWrite(ch, 127);
  delay(1000);
  ledcWrite(ch, 255);
  delay(1000);
}
