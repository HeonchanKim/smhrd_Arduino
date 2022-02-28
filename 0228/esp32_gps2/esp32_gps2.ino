#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial serial_connection(19,18); //RX=pin 19, TX=pin 18
TinyGPSPlus gps;
 
void setup() {
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.println("GPS Start");
}
 
void loop() {
 while(serial_connection.available())
 {
  gps.encode(serial_connection.read());
 }
 if(gps.location.isUpdated())
 {
  Serial.print(gps.location.lat(),6);
  Serial.print(",");
  Serial.println(gps.location.lng(),6);
 }
}
