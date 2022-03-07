//공용 라이브러리
#include <SoftwareSerial.h>       

// 산소포화도 라이브러리
#include <Wire.h>
#include <MAX30100_PulseOximeter.h>

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;

// 이산화탄소 라이브러리
#include <MHZ19.h>          
#include <MHZ19PWM.h>
SoftwareSerial co2Serial(17, 25);          
MHZ19 mhz(&co2Serial);

// 체온 라이브러리
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx;

// GPS 라이브러리
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial gpsSerial(18, 19); 

// MP3Player 라이브러리
#include <DFRobotDFPlayerMini.h>


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

//  gpsSerial.begin(9600);
  co2Serial.begin(9600);
}

void loop()
{
  pox.update();
  MHZ19_RESULT response = mhz.retrieveData();

  //gps
//  boolean newData = false;
//  unsigned long chars;
//  unsigned short sentences, failed;

  if (millis() - tsLastReport > REPORTING_PERIOD_MS){
    Serial.print("심박수:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / 산소포화도:");
    Serial.print(pox.getSpO2());

    tsLastReport = millis();
    Serial.print("% / 체온 = ");
    Serial.print(mlx.readObjectTempC());
    Serial.print("*C");

    if (response == MHZ19_RESULT_OK){
      Serial.print(F(" / CO2: "));
      Serial.println(mhz.getCO2());        //시리얼 모니터에 Co2값 표시
    } else { //그 외엔
      Serial.print(F("Error, code: "));        //시리얼 모니터에 에러코드 표시
      Serial.println(response);
    }


    //gps
//    for (unsigned long start = millis(); millis() - start < 1000;)
//    {
//      while (gpsSerial.available()){
//        char c = gpsSerial.read();
//        // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
//        if (gps.encode(c)) // Did a new valid sentence come in?
//          newData = true;
//      }
//    }
//
//    if (newData){
//      float flat, flon;
//      unsigned long age;
//      gps.f_get_position(&flat, &flon, &age);
//      Serial.print("LAT=");
//      Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//      Serial.print("LON=");
//      Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//    }

  }
  delay(100);
}
