// Movement.h

#pragma once

#include "Arduino.h"

/***********************************************************************************
Class Movement
************************************************************************************

Define a movement using a parametric function {<double[...](double)>}
eventually repeated and with sampling functionnalities 

Ex :
  Movement m;
  m.selOsc(2,4,0,1000,1); // To select the Osc[2,4,0,1000] movement function 2 times used
  // Now can use m(t) as Osc[2,4,0,1000](t) when 0≤t≤1000
  m.start();              // To start the sampling with TS period
  m.update();             // To update the sampling ; return true if a new sample if availaible
  m.stop();               // To stop the sampling (*)
  m.start();              // To restart the sampling
  // Just after, call m.val() to obtain the sampled value 
  // (*) But m.update() return true and m.val() the last sampled value
*/

#define TS 20            // Sampling period(ms) to update movements

enum StateMovement {active, stopped, inactive};

class Movement
{
  typedef double (Movement::*PtrMovementF)(double);  
  // Type of pointer on a movement function
  
  public:
    // Constructor
    Movement();
    
    // Selection methods (NB : speed (unit/s) >0)
    void selAff(double a, double b, double T, unsigned nRep = 0);
    void selOsc(double a, double b, double phi, double  T, unsigned nRep = 0);

    // Access to private fields 
    double T() const {return _T;}
    void setT(double T);   
    StateMovement stateMov() const {return _stateMov;}
    void setStateMov(StateMovement stateMov) {_stateMov = stateMov;} 
    double operator()(double t) {return ((*this).*_pMovF)(t);} // Selected function
    
    // Sampling with TS period
    void start();    
    bool update();
    void stop();
    double val() const {return _val;}

       
  private:
    // Movement functions
    double Aff(double t) {return _a*(1-t/_T)+_b*t/_T;}       // Affine 
    double Osc(double t) {return _a*sin(2*PI*t/_T+_phi)+_b;} // Oscillation 
    
    // Parameters
    double _a;
    double _b;  
    double _phi; // (radians)
    double _T;   // Period(ms) > 0 (no control)
    
    // Other fields
    PtrMovementF _pMovF;         // Pointer on the selected function
    StateMovement _stateMov;     // State movement
    unsigned int _nRep;         // Number of repetitions 
    unsigned int _iUse;         // Movement use number (0, 1, ..., _nUse)
    unsigned long _startTime, _endTime, _previousTime, _stopTime;
    double _val;                // Sampled value
};