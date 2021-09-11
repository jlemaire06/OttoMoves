// TestRobotBTS.ino

#include <RobotSCS.h>
#include <SoftwareSerial.h>        

SoftwareSerial BTSerial(13,12); 
RobotSCS r(2, 3, 4, 5, BTSerial, 8, 7);

void setup() 
{
  BTSerial.begin(9600);   
  delay(100);
}

void loop() 
{
  r.processSonar();
  r.processCommand();
  r.update();
}