int sensor;                               // sensor의 값이 0~1023 사이에서 나옵니다.

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  sensor = analogRead(3);
  // 센서가 움직이지 않을때는 센서 값이 1023입니다.
                    // 주파수 500Hz로 설정해줍니다. 부저는 주파수에 따라 음이 달라집니다.
    Serial.print("Sensor Value: ");        // 시리얼 모니터에 값을 보여줍니다.
    Serial.println(sensor);
    delay(1000);
  }
