// ServoE.h

#pragma once

#include "Arduino.h"
#include <Servo.h>
#include <Movement.h>

/***********************************************************************************
Class ServoE
************************************************************************************

Extension of the Servo class with these functionnalities :

- Trim correction
- Movement control with time (blocking and non blocking)
- Stop/restart 
*/

class ServoE : public Servo, public Movement
{
  public:
    // Constructors
    ServoE(); 
    ServoE(unsigned pin, double trim = 0.); 
    
    // Access to private fields (only necessary)
    void setPin(unsigned pin) {_pin = pin;}; 
    void setTrim(double trim) {_trim = trim;};
    void setPos(double pos) {_pos = pos;};  
    double pos() const {return _pos;}; 
    
    // Methods 
    void attach();                   
    void detach();                   
    // Blocking movement
    void move(double pos);           // Uncontrolled
    void move(double pos, double T); // Controlled
    // Non blocking controlled movement
    void start();                    
    bool update();                   
    void stop();  
    bool isInactive();    
        
  private:
    unsigned _pin;         // Arduino pin where the servo is connected
    double _trim;          // Trim value on writing (°)
    double _pos;           // Current position (°)
};
