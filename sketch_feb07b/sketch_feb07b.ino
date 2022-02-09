void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(2);
  Serial.println(buttonState);

  //버튼을 눌렀을 때 : 1
  //버튼을 누르지 않았을 때 : 0

  //버튼을 눌렀을 때, 13번핀에 연결된 LED가 켜지게 해주세요
  //버튼에서 손을 떼면, LED가 꺼지게 해주세요


  //
  digitalWrite(10,buttonState);

//  if (buttonState == 1) {
//    digitalWrite(10, HIGH);
//  } else {
//    digitalWrite(10, LOW);
//  }
}
