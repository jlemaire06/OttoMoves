// Movement.cpp

#include "Movement.h"

/***********************************************************************************
Class Movement
***********************************************************************************/

Movement::Movement()
{
  _nRep = 0;
  _stateMov = inactive;
  _pMovF = NULL;
}

void Movement::selAff(double a, double b, double T, unsigned nRep = 0) 
{
  _a = a; _b  = b; _T = T; 
  _nRep = nRep;
  _pMovF = &Movement::Aff;
  _stateMov = inactive;
}

void Movement::selOsc(double a, double b, double phi, double T, unsigned nRep = 0) 
{ 
  _a = a; _b  = b; _phi = phi; _T = T; 
  _nRep = nRep;  
  _pMovF = &Movement::Osc;
  _stateMov = inactive;
}  

void Movement::setT(double T)
{
  if (_stateMov != inactive)
  {
    unsigned long t = millis();
    double r = T/_T;
    _startTime = (unsigned long)(t*(1-r) + _startTime*r);
    _endTime = (unsigned long)(t*(1-r) + _endTime*r);
    _previousTime = (unsigned long)(t*(1-r) + _previousTime*r);
    _stopTime = (unsigned long)(t*(1-r) + _stopTime*r);
  }
  _T = T;
}

void Movement::start()
{
  if (_stateMov == active || _pMovF==NULL)  return;
  switch (_stateMov)
  {
    case inactive:
      _startTime = millis(); 
      _endTime = _startTime + _T;
      _previousTime = _startTime;
      _iUse = 0;
      _val = (*this)(0);
      break;
    case stopped:
      unsigned long delta = _previousTime - _stopTime;
      _startTime += delta;
      _endTime += delta;
      break;
  }
  _stateMov = active;
}  

bool Movement::update()
{
  if (_stateMov == inactive) return false;
  unsigned long newTime = millis();
  if ((newTime - _previousTime) >= TS)
  {
    _previousTime += TS;
    if (_stateMov != stopped)
    {
      if (_previousTime < _endTime) 
      {
        _val = (*this)(_previousTime - _startTime);
      }
      else // _previousTime >= _endTime
      {
        if (_iUse == _nRep)
        {
          _stateMov = inactive;  // Ended
          _val = (*this)(_endTime - _startTime);
        }
        else // _iUse < _nRep
        {
          _iUse++;
          _startTime = _endTime;
          _endTime = _startTime + _T;
          _val = (*this)(_previousTime - _startTime);
        }
      }      
    }
    return true;
  }
  else return false;
}

void Movement::stop()
{
  if (_stateMov != active) return;
  _stateMov = stopped;
  _stopTime = _previousTime;
}
