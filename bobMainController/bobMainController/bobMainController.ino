/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/
#include <EEPROM.h>
#include "Control.h"

Encoder motorRight(enc1, enc2);
Encoder motorLeft(enc3, enc4);
Control control;
int currentDirection, motorStatus, motorSpeed, program, positionRight, encoderRun, positionLeft;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	control.run();
	/*if (encoderRun == 1)
	{
		int encoderRight, encoderLeft;
		encoderRight, encoderLeft = encoders();
		encoderRun = control.run(encoderRight, encoderLeft);
	}
	else if (encoderRun == 2)
	{
		encoderReset();
		encoderRun = 0;
	}
	else
		encoderRun = control.run();*/
}

int encoders()
{
	int newRight = motorRight.read();
	int newLeft = motorLeft.read();
	return newRight, newLeft;
	// if (newLeft != positionLeft || newRight != positionRight) {
	// 	Serial.print("Left = ");
	// 	Serial.print(newLeft);
	// 	Serial.print(", Right = ");
	// 	Serial.print(newRight);
	// 	Serial.println();
	// 	positionLeft = newLeft;
	// 	positionRight = newRight;
	// }
}

void encoderReset()
{
	motorRight.write(0);
	motorLeft.write(0);
}
