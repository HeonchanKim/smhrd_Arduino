#include <Servo.h>
Servo myservo;

void setup() {
  myservo.attach(8);
}
void loop() {
  //  myservo.write(0); // 0 ~ 179
  //  delay(1000);
  //  myservo.write(90);
  //  delay(1000);
  //  myservo.write(179);
  //  delay(1000);

  int max = 179;

  for (int i = 0; i <= max; i++) {
    myservo.write(i);
    delay(100);
  }
}
