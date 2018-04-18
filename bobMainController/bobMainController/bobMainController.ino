/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/
#include <Encoder.h>
#include "motorEncoders.h"
#include "motors.h"
#include <EEPROM.h>

Motors motors;

int currentDirection, motorStatus, motorSpeed;
void setup()
{
	// set all the motor control pins to outputs
	Serial.begin(9600);
	Serial.println("Current direction, status and speed are: ");
	Serial.println(currentDirection);
	Serial.println(motorStatus);
	Serial.println(motorSpeed);
}

void loop()
{
	int program;
	while (Serial.available() > 0)
	{
		program = Serial.parseInt();
		motors.run(program);
	}
	while (Serial.available() == 0)
	{
		motors.run();
	}
}
