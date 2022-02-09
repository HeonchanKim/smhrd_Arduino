int trig = 2;
int echo = 3;
void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(trig, HIGH); // trig쪽에서 초음파를 쏜다
  delay(10);
  digitalWrite(trig, LOW);  // 초음파를 그만 쏜다.

  // Echo쪽에서 초음파가 오는 걸 측정!
  // echo핀이 LOW -> HIGH되는 시간을 측정
  int duration = pulseIn(echo, HIGH);
  int distance = (duration / 2) / 29.1;

  // 거리가 5cm이상, 300cm이하 출력
  if (distance >= 5 && distance <= 300) {
    Serial.print("distance : ");
    Serial.print(distance);
    Serial.println("cm");

    if (distance <= 15) {
      tone(8, 330, 100);
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13,LOW);
      delay(100);
    }

  }
  delay(300);






}
