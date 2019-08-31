#include <SoftwareSerial.h>

#define PIN_RX 12
#define PIN_TX 11

SoftwareSerial btSerial(PIN_TX,PIN_RX); // software sirial rx, tx

byte sensorValue[1024];

void setup() {
  // put your setup code here, to run once:
  btSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(btSerial.available())
  {
    Serial.write(btSerial.read());
  }
  
  if(Serial.available())
  {
    btSerial.write(Serial.read());
  }
}
