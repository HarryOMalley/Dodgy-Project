#pragma once
#include <Arduino.h>
#include "config.h"
#include "motors.h"
#include "armServos.h"
#include <XBOXRECV.h>

class Control
{
public:
	Control();
	~Control();
	void run();
	int xbox();
	void manualControl();
	int getInput();
	int getSpeed();
	//int getRotation();
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
	long readMotors();
	void resetMotors();
	bool busy;
	int manualProgram;

private:
	Motors motors;
	armServos arm;
	int program;
	int motorSpeed;
};