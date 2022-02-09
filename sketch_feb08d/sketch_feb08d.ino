int sum = 0;
void setup() {
  Serial.begin(9600);

}

void loop() {

  if (Serial.available()) {
    int num = Serial.parseInt();
    
    if (num != 0) {
      Serial.print(sum);
      Serial.print("+");
      Serial.print(num);
      Serial.print("=");
      sum += num;
      Serial.print(sum);
      Serial.println("");
      
    }
  }
  //c언어에서는 문자열과 숫자형 데이터는 더하기 연산이 불가능하다


  //문자열로 강제 형변환
  //Serial.println((String)num);
  //Serial.println(String(num);
}
