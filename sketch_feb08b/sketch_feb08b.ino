void setup() {
  Serial.begin(9600);
  
}

void loop() {
  //읽어올 수 있는 문자 수를 반환 -> int타입 리턴
  //c언어는 0을 제외한 나머지 숫자는 전부 true -> 0은 false
  //전송한 데이터는 버퍼에 저장된다.
  //Serial.available()은 버퍼에 저장된 데이터의 개수를 리턴하는데
  //read를 하는 순간 읽어온 데이터는 버퍼에서 삭제된다.


  if (Serial.available()) {
    char c = Serial.read();
    Serial.println(c);
  }

  
}
