// Sonar.h

#pragma once

#include "Arduino.h"
#include <elapsedMillis.h>

/***********************************************************************************
Class Sonar
************************************************************************************

Class to manage an HC-SR04 sonar with periodic measures of the distance using 
PCI (Pin Changed Interrupts) on the echo pin (need to be in [0, 7]).
*/

extern "C" void PCINT2_vect();

class Sonar
{
  public:
    Sonar(unsigned pinTrigger, unsigned pinEcho, unsigned int period);  // Constructor (ms) for period
    bool updateDistance();  
    double getDistance();   // (cm)
  
  private:
    unsigned _pinTrigger;
    unsigned _pinEcho;
    unsigned _period;
    volatile unsigned long _tauNew, _tau;
    elapsedMillis _timer;
    void funcISR();

  friend void PCINT2_vect();  // To use private funcISR() in the ISR
};
