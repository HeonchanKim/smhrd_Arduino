#include <ArduinoJson.h>

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "heon";
const char* password =  "12345678";

String result = "";

int ledPin = 18;

void setup() {
  pinMode(ledPin,OUTPUT);
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

    //http.begin("http://121.147.52.204:8081/IoT/Exam01");
    http.begin("http://project-student.ddns.net/nayeho/Exam01"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request

    if (httpCode > 0) { //Check for the returning code

      Serial.println(httpCode);
      result = http.getString();
      Serial.println(result);

      DynamicJsonBuffer jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(result);
      String led = root["led"];

      if(led == "1"){
         Serial.println("LED의 상태는 1입니다");
         digitalWrite(ledPin,1);
        }else{
          Serial.println("LED의 상태는 0입니다");
          digitalWrite(ledPin,0);
          }
    }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
  delay(1000);
}
