int cdsPin = A0;
int ledPin = 9;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(cdsPin);
  Serial.println(sensorValue);

  //가로등 만들기
  //주변의 밝기가 어두워지면 9번 핀과 연결된 LED가 켜짐
  //주변이 밝아지면 LED가 켜짐

  digitalWrite(ledPin, sensorValue <= 800);

//  if (sensorValue < 800) {
//    digitalWrite(ledPin, 1);
//  } else {
//    digitalWrite(ledPin, 0);
//  } 

}
