// TestMovement.ino

#include <Movement.h>

Movement m;
unsigned long oldTime, newTime;
byte state;

void print(double x) 
{
  Serial.print(x); Serial.print('\r');
}

void setup()
{
  Serial.begin(9600);
  delay(100);
  m.selOsc(2, 4, 0, 1000, 2);  // Osc[2,4,0,1000] 3 times
  m.start();
  print(m.val());
  oldTime = millis();
  state = 0;
}

void loop() 
{
  if (m.update()) print(m.val());
  newTime = millis();
  if (newTime-oldTime >= 500) 
  {
    oldTime = newTime;
    if (state==0) {m.setT(500); state++;}       // Period/2 
    else if (state==1) {m.stop(); state++;}     // Stop
    else if (state==2) {m.start(); state++;}    // Restart
  } 
}




