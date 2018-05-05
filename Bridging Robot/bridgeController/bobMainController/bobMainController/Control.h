#pragma once
#include <Arduino.h>
#include "config.h"
#include "motors.h"

class Control
{
public:
	Control();
	~Control();
	void run();
	int getInput();
	int getSpeed();
	int getRotation();
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
	long readMotors();
	void resetMotors();

private:
	Motors motors;
	int program;
	int motorSpeed;
};