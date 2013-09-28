/*
The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
*/

#include "BigSoftwareSerial.h"
#include "cGcodeInterface.h"


const char laserPowerLevelPin = 9;
BigSoftwareSerial grblSerial(10, 11); // RX, TX
cGcodeInterface gCodeObj(&grblSerial, laserPowerLevelPin);

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
  if (grblSerial.available()) //ack is ok\r nack is error:Number\r
    Serial.write(grblSerial.read());
  if (Serial.available())
    gCodeObj.processNextChar();
}

//                                in       out 
//  outputValue = map(inputValue, 0, 1023, 0, 255);  
//  analogWrite(laserPowerLevelPin, laserPowerLevel);  
