#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(18, 19); // 18tx 19rx

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  
  Serial.println(TinyGPS::library_version());
  Serial.println();
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
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
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    float x = (flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat);
    long r1 = x*1000000;
    float result1 = r1 / 1000000;
    Serial.print(" ");
    Serial.print("LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    float y = (flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon);
    long r2 = y*1000000;
    float result2 = r2 / 1000000;
    Serial.println();
    Serial.print("parsing LAT = ");
    Serial.println(r1);
    Serial.print("parsing LON = ");  
    Serial.println(r2);

  }else{
    Serial.print("LAT=FAIL");
    Serial.print(" ");
    Serial.print("LON=FAIL");
    Serial.println(" ");
    }
  
}
