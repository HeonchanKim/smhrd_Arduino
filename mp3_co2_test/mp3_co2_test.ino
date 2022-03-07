#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <MHZ19.h>
#include <MHZ19PWM.h>

SoftwareSerial co2sensor(17, 25);
MHZ19 mhz(&co2sensor);

void setup() {
  Serial.begin (9600);
  mp3_set_serial (Serial);
  delay(1);
  mp3_set_volume (1);

  co2sensor.begin(9600);
}

void loop() {
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK)
  {
    Serial.print(F("CO2: "));
    Serial.println(mhz.getCO2());
    if (mhz.getCO2() > 900) {
      mp3_play (1);
      delay(5000);
    } else { //그 외엔
      Serial.print(F("Error, code: "));
      Serial.println(response);
    }
  }
    delay(3000);
  }
