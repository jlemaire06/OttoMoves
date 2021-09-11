// Buzzer.cpp

#include "Buzzer.h"

/***********************************************************************************
ISR 
***********************************************************************************/

Buzzer* pBuzzer; // As static
ISR(TIMER2_COMPA_vect)
{
  pBuzzer->funcISR();
}

/***********************************************************************************
Class Buzzer
***********************************************************************************/

Buzzer::Buzzer()
{
  pBuzzer = this;
  pinMode(11, OUTPUT);
  _isPlaying = false;
  
  // WGM2 = 0b101 => Phase-correct PWM with TOP in OCR2A
  TCCR2A = (1<<WGM20);
  TCCR2B = (1<<WGM22);
}

void Buzzer::tone(Note note)
{
  // End time
  if (note.len > 0) _endTime = millis() + note.len; 
  else _endTime = 0xFFFFFFFF;

  unsigned int freq = note.freq;
  if (freq > 0)
  {
    // CS2 and OCR2A
    unsigned CS2;
    unsigned int fact;
    if (freq < 60) {CS2 = 7; fact = 3906; OCR2A = fact/freq;}         // Prescaler = 1024
    else if (freq < 120) {CS2 = 6; fact = 15625; OCR2A = fact/freq;}  // Prescaler = 256
    else if (freq < 240) {CS2 = 5; fact = 31250; OCR2A = fact/freq;}  // Prescaler = 128
    else if (freq < 480) {CS2 = 4; fact = 62500; OCR2A = fact/freq;}  // Prescaler = 64
    else {CS2 = 4; fact = 62500; OCR2A = round(fact/freq);}           // Prescaler = 64
    
    // Enable PWM output on pin 11 with 50% duty cycle (Toggle OC2A on compare match)
    bitSet(TCCR2A, COM2A0);  
    
    // Set prescaler using CS2
    TCCR2B &= 0xF8; // Clear CS2 bits
    TCCR2B |= CS2;  // Set CS2 bits

    // Enable COMPA interrupt
    TIMSK2 = (1<<OCIE2A);  
    
    // Tone flag
    _okTone = true;
  }
}

void Buzzer::play(Note tNote[], unsigned int nbNote, unsigned int nbPlay=1)
{
  _tNote = tNote;
  _idNote = 0;
  _nbNote = nbNote;
  _idPlay = 0;
  _nbPlay = nbPlay;
  if (_nbNote > 0) 
  {
    _isPlaying = true;
    tone(_tNote[0]);
  }
}

void Buzzer::funcISR()
{
  if (millis()>=_endTime)
  {
    if (_okTone)
    {
      bitClear(TCCR2A, COM2A0);  // Stop PWM output on pin 11 (but keep COMPA interrupt active)
      _okTone = false;           // Tone flag
      _endTime += 50;            // 50ms delay after tone
      if (_idNote == _nbNote-1) _endTime += 200;
    }
    else
    {
      _idNote++;                 // Next note
      if (_idNote == _nbNote)
      {
        _idNote = 0;
        _idPlay++;
      }    
      if (_idPlay < _nbPlay) tone(_tNote[_idNote]); // Tone call 
      else
      {
        TIMSK2 = 0; // Stop COMPA interrupt
        _isPlaying = false;
      }
    }
  }
}
