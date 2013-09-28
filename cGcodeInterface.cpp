/*
 * cGcodeInterface.cpp
 *
 *  Created on: Sep 7, 2013
 *      Author: jwb
 */

#include "cGcodeInterface.h"
#include <Arduino.h>

cGcodeInterface::cGcodeInterface(BigSoftwareSerial* grblSerial, char outPin)
{
  mGrblSerial = grblSerial;
  mOutPin = outPin;
}

cGcodeInterface::~cGcodeInterface()
{
	// TODO Auto-generated destructor stub
}

///
int cGcodeInterface::processNextChar()
{
	//*command = gCodeIn.get();

        char command;
        
	int error = 0;

	if( command == 'S' || command == 's')
	{
		cGcodeInterface::processSCommand();
	}
	else
	{
	    sendCharToGRBL(command);
	}

	return error;
}

int cGcodeInterface::sendCharToGRBL(char ch)
{
	//std::cout << ch;
        mGrblSerial->write(ch);

	return 0;
}

int cGcodeInterface::processSCommand()
{
	char numberStr[] = "\0\0\0\0";
	unsigned char cnt = 0;
	unsigned int power = 0;
	char ch = '\0';
	int error = 0;


	while( ch!= '\r' )
	{
		//ch = gCodeIn.get();

		//if timeout || unexpected char.... break and return 1;

		if( ch =='\r' || ch == '\n' || ch == ' ')
		{

		}
		else if( ch >= '0' && ch <= '9' )
		{
			numberStr[cnt++] = ch;
		}
		else
		{
			error = 1;
			break;
		}

	}

	if(!error)
	{
		char mul = 1;
		//convert str to number and set pwm
		char i = cnt - 1;

		while( i >= 0 )
		{
			power += mul * ( numberStr[i--] - 0x30 );
			mul *= 10;
		}
		//set pwm
		setPWM(power);
		//send ack
	}
	else
	{
		//send nack
	}


	return error;
}

int cGcodeInterface::setPWM( unsigned char power )
{
	//std::cout <<"Setting power: "<< (int)power << std::endl;
    analogWrite(mOutPin, power);
    
    return 0;
}

