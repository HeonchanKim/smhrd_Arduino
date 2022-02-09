void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  int led_time = 25;
  
  digitalWrite(2, HIGH);   
  delay(led_time);
  digitalWrite(2, LOW);   
  delay(led_time);
  digitalWrite(7, HIGH);   
  delay(led_time);
  digitalWrite(7, LOW);   
  delay(led_time);
  digitalWrite(9, HIGH);   
  delay(led_time);
  digitalWrite(9, LOW);   
  delay(led_time);
  digitalWrite(3, HIGH);   
  delay(led_time);
  digitalWrite(3, LOW);   
  delay(led_time);
  digitalWrite(8, HIGH);   
  delay(led_time);
  digitalWrite(8, LOW);   
  delay(led_time);
  digitalWrite(13, HIGH);   
  delay(led_time);
  digitalWrite(13, LOW);   
  delay(led_time);
  
}
