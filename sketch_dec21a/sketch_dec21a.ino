// setup은 1번 실행된다(reset버튼을 누르거나 전력이 공급되면)
void setup() {
  // pinMode는 2가지 정보를 담고 있다.
  // (핀 번호, 신호 입출력형태)
  pinMode(10, OUTPUT);
}

// setup이 실행된 이후 다음 실행된다
// 전력이 끊길때까지 계속 반복해서 실행된다.
void loop() {
  digitalWrite(10, HIGH);   // 13번핀에 HIGH(+)신호를 보내라!
  delay(250);              // 코드를 1초 지연시켜라 (1000ms = 1s)         
  digitalWrite(10, LOW);    // 13번핀에 LOW(-)신호를 보내라!
  delay(250);              // 코드를 1초 지연시켜라 (1000ms = 1s)  
}
