// Buzzer.h

#pragma once

#include "Arduino.h"
#include "Pitches.h"

/***********************************************************************************
Class Buzzer
************************************************************************************

Class to manage asynchonous tone on pin 11 using Timer2 CompA interrupts 
and PWM phase-correct with top in OCRA
*/

extern "C" void TIMER2_COMPA_vect();

struct Note
{
  unsigned int freq;
  unsigned int len;
};

class Buzzer
{
  public:
    Buzzer();
    void tone(Note note);
    void play(Note tNote[], unsigned int nbNote, unsigned int nbPlay=1);
    bool isPlaying() const {return _isPlaying;}
  
  private:
    unsigned int _idNote, _nbNote;
    unsigned int _idPlay, _nbPlay;
    bool _okTone;
    Note *_tNote;
    unsigned long _endTime;  
    void funcISR();
    bool _isPlaying;

  friend void TIMER2_COMPA_vect();  // To use private funcISR() in the ISR
};
