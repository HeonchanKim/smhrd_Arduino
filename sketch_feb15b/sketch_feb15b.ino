#include <ArduinoJson.h>

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "heon";
const char* password =  "12345678";

String result = "";


void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}

void loop() {

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;

//    http.begin("http://192.168.137.1:8081/IoT/Exam01");
    http.begin("https://api.openweathermap.org/data/2.5/weather?q=Gwangju,kr&appid=a6c9e75f6bc317c439692bd0d4f6365e"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request

    if (httpCode > 0) { //Check for the returning code

      Serial.println(httpCode);
      result = http.getString();
      // Serial.println(result);
      
      
      // C++에서는 json data를 담을 공간이 필요(메모리)
      
      DynamicJsonBuffer jsonBuffer;

      // result를 jsonObject로 변환
      JsonObject& root = jsonBuffer.parseObject(result);
      JsonObject& root_main = root["main"];
      JsonObject& root_wind = root["wind"];
      
      double temp = root_main["temp"];
      temp = temp - 273;
      Serial.print("현재 광주 기온은 : ");
      Serial.print(temp);
      Serial.println("도 입니다.");

      int humidity = root_main["humidity"];
      Serial.print("현재 광주 습도는 : ");
      Serial.print(humidity);
      Serial.println("% 입니다.");

      double wind_speed = root_wind["speed"];
      Serial.print("현재 광주 스피드는 : ");
      Serial.print(wind_speed);
      Serial.println("m/s 입니다.");

      
      
    }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
  delay(1000);
}
