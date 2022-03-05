#include <Wire.h>

#include <MAX30100_PulseOximeter.h>

#include <Adafruit_MLX90614.h>
#define REPORTING_PERIOD_MS 1000

#include <SoftwareSerial.h>       

#include <MHZ19.h>          
#include <MHZ19PWM.h>

PulseOximeter pox;
Adafruit_MLX90614 mlx;
uint32_t tsLastReport = 0;

SoftwareSerial co2sensor(17, 25);          
MHZ19 mhz(&co2sensor);

//SoftwareSerial ss(18, 19); 

void setup() {
  Serial.begin(115200);


  Serial.print("Initializing pulse oximeter..");
  
  if (!pox.begin())
  {
    Serial.println("FAILED");
    for (;;);
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

  //ss.begin(9600);
  co2sensor.begin(115200);
}

void loop() {
  //co2sensor.listen();
  //ss.listen();
  
  pox.update();
  MHZ19_RESULT response = mhz.retrieveData();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  {
    Serial.print("심박수:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / 산소포화도:");
    Serial.print(pox.getSpO2());

    tsLastReport = millis();
    Serial.print("%/ 체온 = ");
    Serial.print(mlx.readObjectTempC());
    Serial.print("*C");

    if (response == MHZ19_RESULT_OK)
    {
      Serial.print(F("/ CO2: "));
      Serial.println(mhz.getCO2());        //시리얼 모니터에 Co2값 표시
    } else { //그 외엔
      Serial.print(F("Error, code: "));        //시리얼 모니터에 에러코드 표시
      Serial.println(response);
    }
  }
  delay(100);
}
