// TServoE.hpp

#pragma once

#include "ServoE.h"

/***********************************************************************************
Class TServoE<N>
************************************************************************************

Table of N extended servos (template)

Public methods :
  TServoE() : constructor
  TServoE(unsigned tPin[], double tTrim[] = NULL) : constructor
  ServoE &operator[](unsigned i) : access to servos
  void attach() : attach
  void detach() : detach
  void move(double tPos[], double T) : blocking controlled parallel movements 
  void start() :  start or restart non blocking controlled parallel movements
  bool update() : update non blocking controlled parallel movements
  void stop() : stop non blocking controlled parallel movements
  bool isInactive() : test if all the servos are inactive
*/

template <unsigned N> class TServoE
{
  public:
    // Constructors
    TServoE(){}
    
    TServoE(unsigned tPin[], double tTrim[] = NULL)
    {
      for (unsigned i=0; i<N; i++) 
      {
        _tServ[i].setPin(tPin[i]);
        if (tTrim != NULL) _tServ[i].setTrim(tTrim[i]); 
        else _tServ[i].setTrim(0.); 
      }    
    }
    
    // Access to private fields
    ServoE& operator[](unsigned i) {return _tServ[i];}
      
    // Other methods
    void attach() {for (unsigned i=0; i<N; i++) _tServ[i].attach();} 
    void detach() {for (unsigned i=0; i<N; i++) _tServ[i].detach();}
    // Blocking controlled parallel movements
    void move(double tPos[], double T)
    {
      for (unsigned i=0; i<N; i++) 
      {
        _tServ[i].selAff(_tServ[i].pos(), tPos[i], T);   
        _tServ[i].start();
      }
      bool toDo;
      do
      {
        toDo = false;
        for (unsigned i=0; i<N; i++) if (_tServ[i].stateMov()==active)
        {
          toDo = true;
          _tServ[i].update();
        } 
      } while (toDo);
      delay(20); // To end the last update
    }    
    // Non blocking controlled parallel movements
    void start() {for (unsigned i=0; i<N; i++) _tServ[i].start();}     
    bool update()
    {
      bool updated = false;
      for (unsigned i=0; i<N; i++) if (_tServ[i].update()) updated = true;
      return updated;
    }    
    void stop() {for (unsigned i=0; i<N; i++) _tServ[i].stop();}       
    bool isInactive()
    {
      bool ok = true;
      for (unsigned i=0; i<N; i++) if (!_tServ[i].isInactive()) ok = false;
      return ok;
    }    
  
  private:
    ServoE _tServ[N]; // Array of servos
};