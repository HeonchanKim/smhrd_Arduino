#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);

void setup() {
  lcd.begin(16,2); //column, row (16열 2행)
}

void loop() {
  int sensorValue = analogRead(A0);
  lcd.clear(); // lcd를 한 번 비워주자!!
  lcd.setCursor(0,0);
  lcd.print("Hello World");
  lcd.setCursor(0,1);
  lcd.print("bright : ");
  lcd.print(sensorValue);
  delay(100);
}
