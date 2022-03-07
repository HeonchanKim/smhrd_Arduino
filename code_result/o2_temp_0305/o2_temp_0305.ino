#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
#include <SoftwareSerial.h>       //'SoftwareSerial.h' 포함
#include <MHZ19.h>           //MHZ19B-master.zip 파일 추가 후 -> 라이브러리 추가
#include <MHZ19PWM.h>

PulseOximeter pox;
uint32_t tsLastReport = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SoftwareSerial co2sensor(17, 5);          //SoftwareSerial ss핀을 2번 3번으로 지정
MHZ19 mhz(&co2sensor);


void setup() {
  Serial.begin(115200);

  co2sensor.begin(9600);

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  if (!Wire1.setPins(26, 27)) {
    Serial.println("Set i2c failed");
  }

  if (!mlx.begin(MLX90614_I2CADDR, &Wire1))
  {
    Serial.println("MLX FAILED");
    while (1)
    {
    }
  };

}

void loop() {
  MHZ19_RESULT response = mhz.retrieveData();
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("심박수:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / 산소포화도:");
    Serial.print(pox.getSpO2());
    Serial.print("% ");

    Serial.print("체온 = ");
    Serial.print(mlx.readObjectTempC());
    Serial.print("*C ");

    tsLastReport = millis();

    //심박수가 0이 아닐 때 이산화탄소 출력
    if (pox.getHeartRate() != 0) {
      if (response == MHZ19_RESULT_OK)
      {
        Serial.print(F("이산화탄소: "));
        Serial.println(mhz.getCO2());        //시리얼 모니터에 Co2값 표시
      } else { //그 외엔
        Serial.print(F("Error, code: "));        //시리얼 모니터에 에러코드 표시
        Serial.println(response);
      }
    }
  }


  delay(10);
}// end of loop
