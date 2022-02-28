#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(18, OUTPUT);
}

int num = 0;

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());

  }
  if (SerialBT.available()) {
    //    Serial.write(SerialBT.read());

    char c = SerialBT.read();

    if (c == '1') {
      digitalWrite(18, 1);
    } else {
      digitalWrite(18, 0);
    }


  }
  delay(20);
}
