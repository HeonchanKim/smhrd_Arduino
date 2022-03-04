#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <Adafruit_MLX90614.h>
#include <Wire.h>
#define REPORTING_PERIOD_MS 1000
#include <SoftwareSerial.h>       //'SoftwareSerial.h' 포함
#include <MHZ19.h>           //MHZ19B-master.zip 파일 추가 후 -> 라이브러리 추가
#include <MHZ19PWM.h>
#include <TinyGPS.h>

PulseOximeter pox;
Adafruit_MLX90614 mlx;
uint32_t tsLastReport = 0;

//이산화탄소 핀번호 설정
SoftwareSerial co2sensor(17, 25);          //SoftwareSerial ss핀을 2번 3번으로 지정
MHZ19 mhz(&co2sensor);

TinyGPS gps;
SoftwareSerial ss(18, 19); // 18tx 19rx

void setup()
{
  Serial.begin(9600);

  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin())
  {
    Serial.println("FAILED");
    for (;;)
      ;
  }
  else
  {
    Serial.println("SUCCESS");
  }

  //체온센서핀번호 설정
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

  ss.begin(9600);
  co2sensor.begin(9600);
}

void loop()
{
  pox.update();
  MHZ19_RESULT response = mhz.retrieveData();

  //gps
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  {
    Serial.print("심박수:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / 산소포화도:");
    Serial.print(pox.getSpO2());
    Serial.print("% /");

    tsLastReport = millis();
    Serial.print("체온 = ");
    Serial.print(mlx.readObjectTempC());
    Serial.print("*C / ");

    if (response == MHZ19_RESULT_OK)
    {
      Serial.print(F("CO2: "));
      Serial.println(mhz.getCO2());        //시리얼 모니터에 Co2값 표시
    } else { //그 외엔
      Serial.print(F("Error, code: "));        //시리얼 모니터에 에러코드 표시
      Serial.println(response);
    }


    //gps
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
      while (ss.available())
      {
        char c = ss.read();
        // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
        if (gps.encode(c)) // Did a new valid sentence come in?
          newData = true;
      }
    }

    if (newData)
    {
      float flat, flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      Serial.print("LAT=");
      Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
      Serial.print("LON=");
      Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    }

  }




  delay(100);
}
