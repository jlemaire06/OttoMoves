// TestTServoE.ino

#include <TServoE.hpp>

unsigned tPin[] = {2,3};
double tTrim[] = {-12,-5};
TServoE<2> tS(tPin, tTrim);
unsigned long oldTime, newTime;
unsigned sta;  

void print(double x, double y) 
{
  Serial.print(x); Serial.print(','); Serial.print(y); Serial.print('\r');
}

void setup() 
{
  Serial.begin(9600);
  delay(100);
  tS.attach(); 

  // Blocking controlled parallel movements to start positions
  double tPos[] = {45, 180};
  tS.move(tPos, 500);  

  // Non blocking controlled parallel movements 
  tS[0].selOsc(45, 45, 0, 2000, 3);
  tS[1].selOsc(45, 135, PI/2, 3000, 3);
  tS.start();
  print(tS[0].pos(), tS[1].pos());
  oldTime = millis();
  sta = 0;
}

void loop()
{   
  if (tS.update()) print(tS[0].pos(), tS[1].pos());
  newTime = millis();
  if (newTime-oldTime >= 2000) 
  {
    oldTime = newTime;
    if (sta == 0) {tS[1].setT(1000); sta++;}   // Period/3 at 2s
    else if (sta == 1) {tS[1].stop(); sta++;}  // Stop at 4s
    else if (sta == 2) {tS[1].start(); sta++;} // Restart at 6s
  }
  if (tS.isInactive()) tS.detach();  
}