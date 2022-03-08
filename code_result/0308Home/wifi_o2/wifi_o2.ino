#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>

//산소포화도
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;


//학원
//ssid KT_GiGA_8403
//password 6az42bd158
const char* ssid = "heon";
const char* password = "rlagjscks1234";

const char* serverName = "http://192.168.0.10:8081/27.8Hz/getValuesTest.jsp";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
long prev_time;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

}

void loop() {
  pox.update();
  Serial.print("심박수:");
  Serial.print(pox.getHeartRate());
  Serial.print("bpm / 산소포화도:");
  Serial.print(pox.getSpO2());
  Serial.println("%");
  delay(100);


  //Send an HTTP POST request every 10 minutes
  String httpRequestData = "";
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST


      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------


      httpRequestData = "HR=" + (String)pox.getHeartRate() + "&O2=" + (String)pox.getSpO2();
      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------
      //---------------------------------------------------------------------------


      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      if (millis() - prev_time > 500) {
        pox = PulseOximeter();
        pox.begin();
      }
      prev_time = millis();

      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }



}
