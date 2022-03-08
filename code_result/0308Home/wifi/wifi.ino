#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>


//학원
//ssid KT_GiGA_8403
//password 6az42bd158
const char* ssid = "iptime";
const char* password = "rlagjscks1234";

const char* serverName = "http://192.168.0.8:8081/27.8Hz/getValuesTest.jsp";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

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


}

void loop() {
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


      
      httpRequestData = "LAT=" + (String)x + "&LON=" + (String)y;


      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
