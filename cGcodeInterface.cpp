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

int cGcodeInterface::processNextChar()
{
        char ch = Serial.read();
        
	int error = 0;

	if( ch == 'S' || ch == 's')
	{
		cGcodeInterface::processSCommand();
	}
	else
	{
	    mGrblSerial->write(ch);
	}

	return error;
}


int cGcodeInterface::processSCommand()
{
	char numberStr[] = "\0\0\0\0";
	unsigned char cnt = 0;
	unsigned int power = 0;
	char ch = '\0';
	int error = 0;


	while( ch!= '\r' && !error)
	{
		unsigned long startTime = millis();
		
		while(!Serial.available())
		{
			unsigned long curTime = millis();
			
			if(curTime > startTime)
			{
				if((curTime - startTime) > mPowerCommandTimeout)
				{
					error = 2;
					break;
				}
			}
			else 
			{
				if((mMaxMillis - startTime) + curTime > mPowerCommandTimeout)
				{
					error = 2;
					break;
				}
			}
		}

		//if timeout 
		
		if(!error)
		{		
			ch = Serial.read();
			
			if( ch =='\r' || ch == '\n' || ch == ' ')
			{
	
			}
			else if( ch >= '0' && ch <= '9' )
			{
				numberStr[cnt++] = ch;
			}
			else
			{
				//unexpected char.... break and return 1;
				error = 1;
				break;
			}
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
		analogWrite(mOutPin, power);
		//send ack
		Serial.print("ok\r");
	}
	else if (error == 1)
	{
		//send nack
		Serial.print("err:S\r");
	}
	else if (error == 2)
	{
		//send timout
		Serial.print("err:T\r");
	}

	return error;
}

