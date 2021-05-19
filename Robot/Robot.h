// Robot.h

#pragma once

#include "TServoE.hpp"

enum Part {LL, RL, LF, RF};
enum Direction {FORWARD, BACKWARD};
enum Side {LEFT, RIGHT};
enum Speed {SLOW, NORMAL, RAPID};

/***********************************************************************************
Class Robot
************************************************************************************

Robot class for OttoDIY with only legs and feet movement functionnalities
*/

class Robot : public TServoE<4>
{
  public:
    Robot(unsigned pinLL, unsigned pinRL, unsigned pinLF, unsigned pinRF, bool calibrated = true); // Constructor
    void setSpeed(Speed spd);                        // To change the movement speed
    void move(double tPos[]);                        // Blocking controlled parallel movements to tPos
    void home();                                     // Blocking controlled parallel movements to {90,90,90,90}
    void walk(Direction dir, unsigned int nRep = 0); // To start a walk non blocking movement              
    void turn(Side sid, unsigned int nRep = 0);      // To start a turn non blocking movement 
    void walk_turn(Direction dir, Side sid, unsigned int nRep = 0); // To start a walk_turn non blocking movement
  
  private:
    Speed _spd;
    void setMov(double tA[], double tB[], double tPhi[], unsigned int nRep);
};
