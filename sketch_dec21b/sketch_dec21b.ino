void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  int led_time = 1000;
  
  digitalWrite(7, HIGH);   
  delay(led_time);
  digitalWrite(7, LOW);   
  delay(led_time);
  digitalWrite(8, HIGH);   
  delay(led_time);
  digitalWrite(8, LOW);   
  delay(led_time);
  digitalWrite(9, HIGH);   
  delay(led_time);
  digitalWrite(9, LOW);   
  delay(led_time);
  
}
