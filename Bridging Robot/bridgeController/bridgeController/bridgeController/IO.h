#pragma once
#include <Arduino.h>
#include <Encoder.h>
#include "config.h"
#include "motors.h"

class IO
{
public:
	IO();
	int getInput();
	int getSpeed();
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
	long readMotors();
	void resetMotors();
private:
	int program;
	Encoder motorRight, motorLeft; // I added Encoder(){} to the library so there was a default constructor, otherwise the object cannot be initialised without arguments
};
