#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

PulseOximeter pox;

uint32_t tsLastReport = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");

  if (!Wire1.setPins(26, 27)) {
    Serial.println("Set i2c failed");
  }

  if (!pox.begin(&Wire1)) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
}

void loop()
{
  pox.update();

  // For both, a value of 0 means "invalid"
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("심박수:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / 산소포화도:");
    Serial.print(pox.getSpO2());
    Serial.println("%");

    tsLastReport = millis();
  }
}
