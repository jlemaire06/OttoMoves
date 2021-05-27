// SendAT.ino

#include <SoftwareSerial.h>           

SoftwareSerial BTSerial(11,12);       

void setup() 
{
  Serial.begin(9600);
  BTSerial.begin(38400);
  delay(100);
}

void loop() 
{
  while(BTSerial.available()>0)
  {
    Serial.print((char)BTSerial.read());
  }
  while(Serial.available()>0)
  {
    char c = (char)Serial.read();
    BTSerial.print(c);
    Serial.print(c); // For local echo
  }
}
