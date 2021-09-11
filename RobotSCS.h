// RobotSCS.h

#pragma once

#include "RobotSC.h"
#include "Sonar.h"
#include "Buzzer.h"

/***********************************************************************************
Class RobotSCS
************************************************************************************

Add a sonar and a buzzer to RobotSC
*/

class RobotSCS : public RobotSC, public Sonar, public Buzzer
{
  public:
    RobotSCS(int pinLL, int pinRL, int pinLF, int pinRF, Stream& serial, int pinT, int pinE, bool calibrated = true);
    void processSonar();
};
