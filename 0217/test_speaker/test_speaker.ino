#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;


int beepPin = 19;

note_t melody_note[] = { // 곰세마리 음계
  NOTE_C, NOTE_C, NOTE_C, NOTE_C, NOTE_C
};


uint8_t octave_m[] = { // 멜로디 옥타브
  4, 4, 4, 4, 4
};

uint8_t noteDurations[] = { // 음의 길이 설정
  2000, 4, 8, 8, 4
};

uint8_t melody_num = 0;
unsigned long int beepTime = 0;



void setup() {
  Serial.begin(115200);
  SerialBT.begin("test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  //pinMode(18, OUTPUT);


  ledcSetup(0, 1E5, 12); // ESP32 톤전용 ledcSetup: ledcSetup(channel,1E5,12);
  ledcAttachPin(beepPin, 0); // ledcAttachPin(uint8_t pin, uint8_t channel);

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
      //digitalWrite(18, 1);
      
      if (millis() - beepTime >= 2000 / noteDurations[melody_num]) {
        beepTime = millis();
        ledcWrite(0, 0);
        ledcWriteNote(0, melody_note[melody_num], octave_m[melody_num]);

        melody_num++;
        if (melody_num == 50) { // 초기화
          ledcWrite(0, 0); // noTone() - ledcWrite(uint8_t channel, uint32_t duty);
          melody_num = 0; 
          beepTime = 0;
        }
      }


    } else {
      //digitalWrite(18, 0);
      melody_num = 0; 
      beepTime = 0;
    }


  }
  delay(20);
}
