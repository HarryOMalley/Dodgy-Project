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
}
