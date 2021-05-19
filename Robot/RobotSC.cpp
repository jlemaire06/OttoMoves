// RobotSC.cpp

#include "RobotSC.h"

Command tCmd[] =    // Acceptable commands
{
  {'C',2,{1,0}},    // Contact : 1=>on, 0=>off 
  {'M',9,{0,1,2,3,4,13,14,23,24}},  
  // Movement : 0=>home, 1/2=>walk FORWARD/BACKWARD, 3/4=>turn LEFT/RIGHT, 13=>walk FORWARD and turn LEFT, etc.
  {'I',2,{1,0}},    // Interruption : 1=>on, 0=>off
  {'S',3,{1,2,3}}   // Speed : 1=>SLOW, 2=>NORMAL, 3=>RAPID
};

#define REP 100

/***********************************************************************************
Class RobotSC
***********************************************************************************/

RobotSC::RobotSC(int pinLL, int pinRL, int pinLF, int pinRF, Stream& serial, bool calibrated = true)
: Robot(pinLL, pinRL, pinLF, pinRF, calibrated), SerialCommand(serial, 4, tCmd)
{
}

void RobotSC::processCommand()
{
  if (parseCommand())
  {
    resetParse();
    unsigned _opt = opt();
    switch (typ())
    {
      case 'C':
        if (_opt==1) attach();
        else if (_opt==0) detach();
        break;
      case 'M': 
        if (_opt==0) home();
        else if (_opt==1) walk(FORWARD, REP);     
        else if (_opt==2) walk(BACKWARD, REP);
        else if (_opt==3) turn(LEFT, REP);
        else if (_opt==4) turn(RIGHT, REP);
        else if (_opt==13) walk_turn(FORWARD, LEFT, REP);
        else if (_opt==14) walk_turn(FORWARD, RIGHT, REP);
        else if (_opt==23) walk_turn(BACKWARD, LEFT, REP);
        else if (_opt==24) walk_turn(BACKWARD, RIGHT, REP);
        break;
      case 'I':
        if (_opt==1) stop();
        else if (_opt==0) start();
        break;
      case 'S':
        if (_opt==1) setSpeed(LOW);
        else if (_opt==2) setSpeed(NORMAL);
        else if (_opt==3) setSpeed(RAPID);       
        break;
    }
  }
}
