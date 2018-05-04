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
int currentDirection, motorStatus, motorSpeed, program, positionRight, positionLeft;
void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int newProgram;
	control.run();
	encoders();
}

void encoders()
{
	int newRight = motorRight.read();
	int newLeft = motorLeft.read();
	
	if (newLeft != positionLeft || newRight != positionRight) {
		Serial.print("Left = ");
		Serial.print(newLeft);
		Serial.print(", Right = ");
		Serial.print(newRight);
		Serial.println();
		positionLeft = newLeft;
		positionRight = newRight;
	}
}