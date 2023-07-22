#include <Servo.h>

const int escPin = 9;
Servo esc;

const int throttlePin = A1;


void setup() {
  esc.attach(escPin);
  
  pinMode(throttlePin, INPUT);
}


void loop() {
  int throttle = analogRead(throttlePin);

  int throttleval = map(throttle, 0, 1023, 1500, 2100);
  if(throttleval <= 1550){
    throttleval = 1500;
  }
  esc.writeMicroseconds(throttleval);
}
