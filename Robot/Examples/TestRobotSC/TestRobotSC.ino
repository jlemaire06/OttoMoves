// TestRobotSC.ino

#include <RobotSC.h>

RobotSC r(2, 3, 4, 5, Serial);

void setup() 
{
  Serial.begin(9600);   
  delay(100);
}

void loop() 
{
  r.processCommand();
  r.update();
}