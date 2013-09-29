/*
 * cGcodeInterface.h
 *
 *  Created on: Sep 7, 2013
 *      Author: jwb
 */

#ifndef CGCODEINTERFACE_H_
#define CGCODEINTERFACE_H_

#include "BigSoftwareSerial.h"

class cGcodeInterface//: public iGCodeInterface
{

public:
  cGcodeInterface(BigSoftwareSerial* grblSerial, char outPin);
  virtual ~cGcodeInterface();
  
  int processNextChar();

private:
  BigSoftwareSerial* mGrblSerial; 
  char mOutPin;

  const unsigned long mPowerCommandTimeout = 3000;
  const unsigned long mMaxMillis = 4294967295;
  
  int processSCommand();
};


#endif /* CGCODEINTERFACE_H_ */
