void setup() {
  Serial.begin(9600); // 시리얼 모니터를 사용하겠다
  pinMode(2, INPUT); //2번핀에 Seonsor가 연결됨
  pinMode(13, OUTPUT); //13번핀에 Actuator가 연결됨!!
}

void loop() {
  //  Serial.println("Hello World");
  int sensorValue = digitalRead(2); // 2번핀으로부터 신호를 읽어 온 후

  Serial.println(sensorValue); // 시리얼 모니터에 출력

  // 컨트롤 + T 정렬
  // 컨트롤 + del 한줄 삭제
  //만약, 버튼이 눌러졌다면, LED 불을 켜겠다!!


  if (sensorValue == 1) {
    // 버튼이 눌러진 상태!!
    // 13번에 연결된 LED가 켜짐!!
    digitalWrite(13, 1);
  }
  else {
    // if문의 조건식 ()의 결과가 거짓일 때 실행됨
    // 버튼이 안눌러진 상태!!
    digitalWrite(13, 0);
  }

  // digitalWrite(13, sensorValue); // 버튼을 누르면 13번 LED가 켜진다










}
