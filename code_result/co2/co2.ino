#include <SoftwareSerial.h>       //'SoftwareSerial.h' 포함
#include <MHZ19.h>           //MHZ19B-master.zip 파일 추가 후 -> 라이브러리 추가
#include <MHZ19PWM.h>

SoftwareSerial co2sensor(17, 25);          //SoftwareSerial ss핀을 2번 3번으로 지정

MHZ19 mhz(&co2sensor);

void setup()
{
  Serial.begin(115200);         //115200 시리얼 통신 시작
  Serial.println(F("Starting..."));         //시리얼 모니터에 "Starting..." 표시

  co2sensor.begin(9600);
}

void loop()
{
  MHZ19_RESULT response = mhz.retrieveData();

  if (response == MHZ19_RESULT_OK)
  {
    Serial.print(F("CO2: "));
    Serial.println(mhz.getCO2());        //시리얼 모니터에 Co2값 표시
  }else{ //그 외엔
    Serial.print(F("Error, code: "));        //시리얼 모니터에 에러코드 표시
    Serial.println(response);
  }
  delay(3000);         //15초 대기
} 
