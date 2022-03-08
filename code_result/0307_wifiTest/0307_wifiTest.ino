#include <WiFi.h>
#include <HTTPClient.h>

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

//KT_GiGA_8403
//6az42bd158
const char* ssid = "KT_GiGA_8403";
const char* password = "6az42bd158";

const char* serverName = "http://59.0.236.34:8081/27.8Hz/getValuesTest.jsp";

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

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");


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

      
      //---------------------------------------------------------------------------------------------------
      //---------------------------------------------------------------------------------------------------
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

      float flat, flon;
      unsigned long age;
      double x, y;
      int result_lat, result_lon;

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
          //float flat, flon;
          //unsigned long age;
          gps.f_get_position(&flat, &flon, &age);
          Serial.print("LAT=");
          Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
          x = (flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat);
          result_lat = x * 1000000;
          Serial.print(" ");
          Serial.print("LON=");
          Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
          y = (flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon);
          result_lon = y * 1000000;

        }
        pox = PulseOximeter();
        pox.begin();
        prev_time = millis();
      }
      httpRequestData = "LAT=" + (String)result_lat + "&LON=" + (String)result_lon + "&HR=" + (String)pox.getHeartRate() + "&O2=" + (String)pox.getSpO2() + "&TEMP=" + (String)mlx.readObjectTempC() + "&SHOCKVAL=" + (String)sensor;
      //---------------------------------------------------------------------------------------------------
      //---------------------------------------------------------------------------------------------------

      
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");

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
