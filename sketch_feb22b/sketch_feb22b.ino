#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(10, 11); // RX, TX
void setup () {
  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module
  delay(1);  //wait 1ms for mp3 module to set volume
  mp3_set_volume (15);        // 0~30
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
}
void loop ()
{         
  if(digitalRead(7) == LOW)
  {
    delay(100);
    mp3_next (); 
  }
  else if(digitalRead(8) == LOW)
  {
    delay(100);
    mp3_pause ();
  }
}
