#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(18, 19); // 18tx 19rx
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
PulseOximeter pox;

uint32_t tsLastReport = 0;
int sensor;
long prev_time;


void setup()
{
  Serial.begin(115200);

  //산소포화도
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  //체온
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

  //gps
  ss.begin(9600);

}

void loop()
{
  sensor = analogRead(2);
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    Serial.print("심박수:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / 산소포화도:");
    Serial.print(pox.getSpO2());
    Serial.print("% ");

    tsLastReport = millis();

    Serial.print("체온 = ");
    Serial.print(mlx.readObjectTempC());
    Serial.print("*C ");

    //충격감지센서
    Serial.print("충격 감지: ");
    Serial.println(sensor);

  }
  delay(50);

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  if (millis() - prev_time > 100000) {


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
      Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
      Serial.print(" LON=");
      Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    }
    pox = PulseOximeter();
    pox.begin();
    prev_time = millis();
  }

}// end of loop
