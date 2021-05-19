// SerialCommand.cpp

#include "SerialCommand.h"

/***********************************************************************************
Class SerialCommand
***********************************************************************************/

SerialCommand::SerialCommand(Stream& serial, int nCmd, Command tCmd[]) : _serial(serial)
{
  _nCmd = nCmd;
  _tCmd = tCmd;
  resetParse();
} 

void SerialCommand::resetParse()
{
  _nParse = 0;
  _okCommand = false;
}  

bool SerialCommand::parseCommand()
{
  // Syntax 
  while (_serial.available()>0)
  {
    char inChar = _serial.read(); 
    if (inChar != '\n' && inChar != '\r')  // '\r' and '\n' are ignored
    {
      if (_nParse==0)
      {
        if (inChar >= 'A' && inChar <= 'Z') {_typ = inChar; _nParse++;}
      }
      else if (_nParse==1)
      {
        if (isDigit(inChar)) {_opt = inChar - '0'; _nParse++;}
        else resetParse(); 
      }
      else if (_nParse==2)
      {
        if (isDigit(inChar)) {_opt = 10*_opt + (inChar - '0'); _nParse++;}
        else if (inChar=='#') _okCommand = true;
        else resetParse(); 
      }
      else if (_nParse==3)
      {
        if (inChar=='#') _okCommand = true;
        else resetParse(); 
      }
    }
  }

  // Semmantic
  if (_okCommand)
  {
    unsigned i = 0;
    while (i<_nCmd && _typ!=_tCmd[i].typ) i++;
    if (i==_nCmd) resetParse();   
    else
    {
      unsigned j = 0;                                
      while (j<_tCmd[i].nOpt && _opt!=_tCmd[i].tOpt[j]) j++;
      if (j==_tCmd[i].nOpt) resetParse();
    }     
  } 
  return _okCommand;
} 

  
