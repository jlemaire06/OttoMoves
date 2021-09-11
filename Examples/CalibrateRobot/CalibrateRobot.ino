// CalibrateRobot.ino

#include <Robot.h>
#include <EEPROM.h>

Robot r(2, 3, 4, 5, false);
int tTrim[] = {-5, -7, 4, -6};

void writeEEPROM(int i, int val)
{
  if (val < 0) val = 256+val;
  EEPROM.write(i, (byte)val);
}

void setup() 
{
  for (int i=0; i<4; i++) r[i].setTrim(tTrim[i]);
  r.attach();
  r.home();
  for (int i=0; i<4; i++) writeEEPROM(i, tTrim[i]);
}

void loop() 
{
}