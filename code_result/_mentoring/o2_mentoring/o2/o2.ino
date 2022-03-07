#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <Adafruit_MLX90614.h>

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
Adafruit_MLX90614 mlx;
uint32_t tsLastReport = 0;


void setup()
{
  Serial.begin(115200);

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

void loop()
{
  pox.update();

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
    Serial.println("*C");
  }


  delay(100);
}
