// TestRobot.ino

#include <Robot.h>

Robot r(2, 3, 4, 5);

void setup() 
{
  r.attach();
  r.home();
  r.walk(FORWARD, 5);
}

void loop() 
{
  r.update();
  if (r.isInactive()) 
  {
      r.home();
      r.detach();
  }
}
