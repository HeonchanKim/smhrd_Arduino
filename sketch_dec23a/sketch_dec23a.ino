void setup() {
  pinMode(A0, INPUT); // INPUT은 기본값이므로 생략 가능
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  //  int changeValue = sensorValue / 4;
  Serial.println(sensorValue);

  
  //  int changeValue = map(변환값, 변환전 최소범위, 변환 전 최대범위, 변환 후 최소, 변환 후 최대)
  int changeValue = map(sensorValue, 0, 1023, 0, 255);
  
  analogWrite(9, changeValue);
  



}
