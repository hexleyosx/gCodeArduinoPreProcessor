/*
The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
*/

#include <SoftwareSerial.h>

const int laserPowerLevelPin = 9;
SoftwareSerial grblSerial(10, 11); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  //Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  grblSerial.begin(9600);
  //grblSerial.println("Hello, world?");
}

void loop() // run over and over
{
  if (grblSerial.available())
    Serial.write(grblSerial.read());
  if (Serial.available())
    grblSerial.write(Serial.read());
}

//                                in       out 
//  outputValue = map(inputValue, 0, 1023, 0, 255);  
//  analogWrite(laserPowerLevelPin, laserPowerLevel);  
