#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

const int speedPinR = 6; // H-bridge enable pin for speed control
const int speedPinL = 5;
const int rMotorPinA = 7; // H-bridge leg 1
const int rMotorPinB = 12;

const int lMotorPinA = 4; // H-bridge leg 2
const int lMotorPinB = 2;

uint8_t joystickX = 128;
uint8_t joystickY = 128;

void setup()
{
    rf_driver.init();
    Serial.begin(9600);
    pinMode(speedPinR, OUTPUT);
    pinMode(speedPinL, OUTPUT);
 
    pinMode(rMotorPinA, OUTPUT);
    pinMode(rMotorPinB, OUTPUT);
 
    pinMode(lMotorPinA, OUTPUT);
    pinMode(lMotorPinB, OUTPUT);
}


void loop()
{
    uint8_t buf[2];
    uint8_t buflen = sizeof(buf);

    if (rf_driver.recv(buf, &buflen))
    {
        joystickX = buf[0];
        joystickY = buf[1];
    
        // Message received with valid checksum
        Serial.print("X: ");
        Serial.print(joystickX);
        Serial.print(" Y: ");
        Serial.println(joystickY);   
        if(joystickX < 128){
            digitalWrite(lMotorPinA, LOW);
            digitalWrite(lMotorPinB, HIGH);
            analogWrite(speedPinL, (joystickX - 128) * -2);
        }else{
            digitalWrite(lMotorPinA, HIGH);
            digitalWrite(lMotorPinB, LOW);
            analogWrite(speedPinL, (joystickX - 128) * 2);
        }
     
        if(joystickY < 128){
            digitalWrite(rMotorPinA, LOW);
            digitalWrite(rMotorPinB, HIGH);
            analogWrite(speedPinR, (joystickY - 128) * -2);
        }else{
            digitalWrite(rMotorPinA, HIGH);
            digitalWrite(rMotorPinB, LOW);
            analogWrite(speedPinR, (joystickY - 128) * 2);
        }
    }
    
    /**/   
}
