// TestServoE.ino

#include <ServoE.h>

ServoE s(3,-5);  // Servo on pin 3 with trim -5
unsigned long oldTime, newTime;
unsigned sta;

void print(double x) 
{
  Serial.print(x); Serial.print('\r');
}

void setup() 
{
  Serial.begin(9600);
  delay(100);
  s.attach(); 
  
  // Oscillation (x4) with 3000ms period
  s.selOsc(90, 90, 0, 3000, 3);
  s.start();
  print(s.pos());
  oldTime = millis();
  sta = 0;
}

void loop() 
{
  if (s.update()) print(s.pos());
  newTime = millis();
  if (newTime-oldTime >= 2000) 
  {
    oldTime = newTime;
    if (sta == 0) {s.setT(1000); sta++;}    // Period/3 at 2s
    else if (sta == 1) {s.stop(); sta++;}   // Stop at 4s
    else if (sta == 2) {s.start(); sta++;}  // Restart at 6s
  }
  if (s.isInactive()) s.detach();
}
