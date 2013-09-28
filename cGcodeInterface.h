/*
 * cGcodeInterface.h
 *
 *  Created on: Sep 7, 2013
 *      Author: jwb
 */

#ifndef CGCODEINTERFACE_H_
#define CGCODEINTERFACE_H_

//#include <iostream>
//#include <fstream>
#include "BigSoftwareSerial.h"

class cGcodeInterface//: public iGCodeInterface
{

public:
  cGcodeInterface(BigSoftwareSerial* grblSerial, char outPin);
  virtual ~cGcodeInterface();
  
  int processNextChar();
  int sendCharToGRBL(char ch);
  int processSCommand();
  int setPWM(unsigned char power);

private:
  BigSoftwareSerial* mGrblSerial;
  char mOutPin;
  //std::ifstream gCodeIn;
};


#endif /* CGCODEINTERFACE_H_ */
