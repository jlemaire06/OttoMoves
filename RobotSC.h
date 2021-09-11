// RobotSC.h

#pragma once

#include "Robot.h"
#include "SerialCommand.h"

/***********************************************************************************
Class RobotSC
************************************************************************************

Add serial commands (Contact, Move, Interrupt, Speed) to OttoDIY 
*/

class RobotSC : public Robot, public SerialCommand
{
  public:
    RobotSC(int pinLL, int pinRL, int pinLF, int pinRF, Stream& serial, bool calibrated = true);
    void processCommand();
};
