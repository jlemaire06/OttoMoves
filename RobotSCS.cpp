// RobotSCS.cpp

#include "RobotSCS.h"

Note alm1[] = {{NOTE_B4, 250}, {NOTE_G3, 250}};
Note alm2[] = {{NOTE_B4, 125}, {NOTE_G3, 125}};

#define DIST1 15
#define DIST2 10

/***********************************************************************************
Class RobotSCS
***********************************************************************************/

RobotSCS::RobotSCS(int pinLL, int pinRL, int pinLF, int pinRF, Stream& serial, int pinT, int pinE, bool calibrated = true)
: RobotSC(pinLL, pinRL, pinLF, pinRF, serial, calibrated), Sonar(pinT, pinE, 20), Buzzer()
{
}

void RobotSCS::processSonar()
{
  if (updateDistance() && !isPlaying())
  {
    double dist = getDistance();
    if (dist < DIST2) play(alm2, 2);
    else if (dist < DIST1) play(alm1, 2);
  }
}
 
