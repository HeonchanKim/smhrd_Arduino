#include <SoftwareSerial.h>       //'SoftwareSerial.h' 포함
#include <MHZ19.h>           //MHZ19B-master.zip 파일 추가 후 -> 라이브러리 추가
#include <MHZ19PWM.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;

SoftwareSerial co2sensor(26, 25);          //SoftwareSerial ss핀을 2번 3번으로 지정
MHZ19 mhz(&co2sensor);

uint32_t tsLastReport = 0;

void onBeatDetected()
{
  Serial.println("Beat!");
}






void setup()
{
  Serial.begin(115200);

  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);

  //co2
  Serial.println(F("Starting..."));         //시리얼 모니터에 "Starting..." 표시
  co2sensor.begin(9600);
}


void loop()
{
  MHZ19_RESULT response = mhz.retrieveData();

  if (response == MHZ19_RESULT_OK)
  {
    Serial.print(F("이산화탄소: "));
    Serial.println(mhz.getCO2());        //시리얼 모니터에 Co2값 표시
  } else { //그 외엔
    Serial.print(F("Error, code: "));        //시리얼 모니터에 에러코드 표시
    Serial.println(response);
  }
  
  //산소포화도
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("심박수:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / 산소포화도:");
    Serial.print(pox.getSpO2());
    Serial.print("%  /  ");

    tsLastReport = millis();
  }
  //--------------------------------------------------------
  //밑에는 co2
  
  delay(1000);


}
