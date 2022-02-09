void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  
  
  if (Serial.available()) {
    char c = Serial.read();
    Serial.println(c);

    if (c == '1') {
      digitalWrite(5, HIGH);
      Serial.println("1 HIGH");
    } else if (c == '2') {
      digitalWrite(4, HIGH);
      Serial.println("2 HIGH");
    } else if (c == '3') {
      digitalWrite(3, HIGH);
      Serial.println("3 HIGH");
    } else if (c == '4') {
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
      Serial.println("1,2,3 LOW");
    }
  }


  
} //end of loop
