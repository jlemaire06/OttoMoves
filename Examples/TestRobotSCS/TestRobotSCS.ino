// TestRobotSCS.ino

#include <RobotSCS.h>

RobotSCS r(2, 3, 4, 5, Serial, 8, 7);

void setup() 
{
  Serial.begin(9600);   
  delay(100);
}

void loop() 
{
  r.processSonar();
  r.processCommand();
  r.update();
}