#include <RH_ASK.h>
#include <SPI.h> 
 
RH_ASK rf_driver;
uint8_t* dataPacket;

void setup()
{
    Serial.begin(9600);
    dataPacket = new uint8_t[2];
    rf_driver.init();
}
 
void loop(){
  
  const uint8_t joystickX = map(analogRead(A0), 0, 1023, 0, 255);
  const uint8_t joystickY = map(analogRead(A1), 0, 1023, 0, 255);
  dataPacket[0] = joystickX;
  dataPacket[1] = joystickY;
  
  Serial.print("X: ");
  Serial.print(joystickX);
  Serial.print(" Y: ");
  Serial.println(joystickY);
  
  rf_driver.send(dataPacket, 2);
  rf_driver.waitPacketSent();
  delay(50);
}
