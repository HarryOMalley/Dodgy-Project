/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/
#include <EEPROM.h>
#include <Encoder.h>
#include "motors.h"
IO io;
Motors motors;
Encoder motorRight(enc1, enc2);
Encoder motorLeft(enc3, enc4);
int currentDirection, motorStatus, motorSpeed, program;
void setup()
{
	// set all the motor control pins to outputs
	Serial.begin(9600);
}

void loop()
{
	int newProgram;
	//newProgram = io.getInput();
	//if (newProgram == 0)
	//{
	//	motors.run();
	//}
	//else
	//{
	//	program = newProgram;
	//	Serial.print("Program: ");
	//	Serial.println(program);
	//	motors.run(program);
	//}
	int right = motorRight.read();
	Serial.println(right);
	//while (Serial.available() > 0)
	//{
	//	Serial.println("recieved");
	//	newProgram = Serial.parseInt();
	//	motors.run(newProgram);
	//}
	//while (Serial.available() == 0)
	//{
	//	motors.run();
	//}
}
