// Robot.cpp

#include "Robot.h"
#include <EEPROM.h>

/***********************************************************************************
Class Robot
***********************************************************************************/
                                  
double tSpeed[] = {50, 100, 150}; // NB : °/s

Robot::Robot(unsigned pinLL, unsigned pinRL, unsigned pinLF, unsigned pinRF, bool calibrated = true)
: TServoE<4>()
{
  (*this)[LL].setPin(pinLL);
  (*this)[RL].setPin(pinRL);
  (*this)[LF].setPin(pinLF);
  (*this)[RF].setPin(pinRF);
  if (calibrated) 
    for (unsigned i=0; i<4; i++) 
    {
      int trim = EEPROM.read(i);
      if (trim > 128)trim -= 256;
      (*this)[i].setTrim(trim);
    }
  _spd = NORMAL;
}

void Robot::setSpeed(Speed spd)
{
  if (!isInactive() && spd != _spd)
  {
    double r = tSpeed[_spd]/tSpeed[spd];
    for (unsigned i=0; i<4; i++) (*this)[i].setT((*this)[i].T()*r);
  }
  _spd = spd;
}

void Robot::move(double tPos[])
{
  double x = 0.1; // Need T > 0 !
  for (unsigned i=0; i<4; i++) x = max(x, abs((*this)[i].pos()-tPos[i]));
  double T = 1000*x/tSpeed[_spd];
  TServoE::move(tPos, T);
}

void Robot::home()
{
  double tPos[4] = {90, 90, 90, 90};
  move(tPos);
}

void Robot::walk(Direction dir, unsigned int nRep = 0)
{
  double phi;
  switch (dir)
  {
    case FORWARD: phi = -PI/2; break;
    case BACKWARD: phi = PI/2; break;
  }
  double tA[4] = {30, 30, 20, 20};
  double tB[4] = {90, 90, 94, 86};
  double tPhi[4] = {0, 0, phi, phi};
  setMov(tA, tB, tPhi, nRep);
}

void Robot::turn(Side sid, unsigned int nRep = 0)
{
  double phi;
  switch (sid)
  {
    case LEFT: phi = -PI; break;
    case RIGHT: phi = 0; break;
  }
  double tA[4] = {15, 15, 20, 20};
  double tB[4] = {105, 75, 94, 86};
  double tPhi[4] = {-PI/2, -3*PI/2, phi, phi};
  setMov(tA, tB, tPhi, nRep);
}

void Robot::walk_turn(Direction dir, Side sid, unsigned int nRep = 0)
{
  double aLL, aRL, phi;
  switch (dir)
  {
    case FORWARD: phi = -PI/2; break;
    case BACKWARD: phi = PI/2; break;
  }
  switch (sid)
  {
    case LEFT: aLL = 30; aRL = 10; break;
    case RIGHT: aLL = 10; aRL = 30; break;
  }
  double tA[4] = {aLL, aRL, 20, 20};
  double tB[4] = {90, 90, 94, 86};
  double tPhi[4] = {0, 0, phi, phi};
  setMov(tA, tB, tPhi, nRep);
}

void Robot::setMov(double tA[], double tB[], double tPhi[], unsigned int nRep)
{
  double tPos[4];
  for (unsigned i=0; i<4; i++) tPos[i] = tA[i]*sin(tPhi[i])+tB[i];
  move(tPos); 
  double x = 30.;
  double T = 4000*x/tSpeed[_spd];
  for (unsigned i=0; i<4; i++) (*this)[i].selOsc(tA[i], tB[i], tPhi[i], T, nRep);
  start();
}


  
