#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2,3); // software sirial rx, tx

byte sensorValue[1024];

void setup() {
  // put your setup code here, to run once:
  BTSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
