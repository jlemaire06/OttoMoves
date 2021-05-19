// TestRobotBT.ino

#include <RobotSC.h>
#include <SoftwareSerial.h>           

SoftwareSerial BTSerial(11,12);       
RobotSC r(2, 3, 4, 5, BTSerial);

void setup() 
{
  BTSerial.begin (9600);
  delay(100);
}

void loop() 
{
  r.processCommand();
  r.update();
}