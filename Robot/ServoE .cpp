// ServoE.cpp

#include "ServoE.h"

/***********************************************************************************
Class ServoE
***********************************************************************************/

ServoE::ServoE() : Servo(), Movement()
{
  _pin = 255;
  _trim = 0.;
}

ServoE::ServoE(unsigned pin, double trim = 0.) : Servo()
{
  _pin = pin;
  _trim = trim;
}

void ServoE::ServoE::attach()
{
  if (_pin < 255)        
  {
    Servo::attach(_pin);
    while (!attached()) {}
    move(90);
    delay(300);
  }
}

void ServoE::ServoE::detach()
{
  if (attached())
  { 
    delay(300); // Necessary to end correctly the movements
    Servo::detach();
    setStateMov(inactive);
  }
}

void ServoE::ServoE::move(double pos)
{
  if (attached())
  {
    write(round(pos + _trim));
    _pos = pos;
  }
}

void ServoE::move(double pos, double T)
{
  if (attached())
  {
    selAff(_pos, pos, T);
    start();
    while (stateMov()==active) if(update()) move(val());
    delay(20); // To end the last update
  }
}
   
void ServoE::start()
{
  if (attached()) 
  {
    Movement::start();
    move(val());
  }
}

bool ServoE::update()
{
  if (Movement::update()) 
  {
    move(val());
    return true;
  }
  else return false;
}

void ServoE::stop()
{
  if (attached()) Movement::stop();
}

bool ServoE::isInactive()
{
  return (stateMov()==inactive);
}
