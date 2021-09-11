// Sonar.cpp

#include "Sonar.h"

/***********************************************************************************
ISR 
***********************************************************************************/

Sonar* pSonar; // As static
ISR(PCINT2_vect)
{
  pSonar->funcISR();
}

/***********************************************************************************
Class Sonar
***********************************************************************************/

Sonar::Sonar(unsigned pinTrigger, unsigned pinEcho, unsigned int period)
{
  pSonar = this;
  _pinTrigger = pinTrigger;
  _pinEcho = pinEcho;
  _period = period;
  
  pinMode(_pinTrigger, OUTPUT);
  digitalWrite(_pinTrigger, LOW);
  pinMode(_pinEcho, INPUT);
  bitSet(PCMSK2, _pinEcho); // Enable PCI for _pinEcho
}

bool Sonar::updateDistance()
{
  if (_timer > _period)
  {
    _timer = 0;

    // Ping 
    digitalWrite(_pinTrigger, HIGH);
    digitalWrite(_pinTrigger, LOW);

    // Enable PCI for Port2
    bitSet(PCICR, PCIE2);
    
    // return
    return true;
  }
  else return false;
}

double Sonar::getDistance()
{
  return (_tau/58.82);
}

void Sonar::funcISR()
{
  unsigned long t = micros();
  if (digitalRead(_pinEcho)) _tauNew = t;
  else 
  {
    _tauNew = t - _tauNew;
    if (_tauNew >= 50 && _tauNew <= 25000) 
    {
      _tau = _tauNew;
      bitClear(PCICR, PCIE2); // Stop PCI for Port2 
    }
  }
}

                                
