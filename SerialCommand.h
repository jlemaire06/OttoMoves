// SerialCommand.h

#pragma once

#include "Arduino.h"

#define MAX_OPTIONS 9
struct Command {char typ; unsigned nOpt; unsigned tOpt[MAX_OPTIONS];};  // Acceptable command

/***********************************************************************************
Class SerialCommand
************************************************************************************

Class to parse commands sended on a serial port ('\r' and '\n' are ignored)

Syntax :
  <command> = <typ><opt>#
  <typ> = <letter>
  <letter> = A|B|...|Z
  <opt> = <digit>|<digit><digit>
  <digit> = 0|...|9
  
Semantic :
  (<typ>,<opt>) in tCmd
*/                                                  
class SerialCommand 
{
  public:                                   
    SerialCommand(Stream& serial, int nCmd, Command tCmd[]);
    char typ() const {return _typ;}
    unsigned opt() const  {return _opt;}
    void resetParse();
    bool parseCommand();

  private:
    Stream& _serial;              // Serial port used for commands 
    unsigned _nCmd;               // Number of acceptable commands 
    Command *_tCmd;               // Array of acceptable commands (as reference)
    bool _okCommand;              // True if a command as been correctly parsed
    char _typ;                    // Type of this command
    unsigned _opt;                // Option of this command
    unsigned _nParse;             // Number of parsed characters
};
