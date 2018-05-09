#pragma once
#include <Arduino.h>
#include "config.h"
#include "motors.h"
#include "armServos.h"
#include <XBOXRECV.h>
#include "LEDS.h"

class Control
{
public:
	Control();
	~Control();
	void setup();
	void run();
	int xbox();
	int getInput();
	int getSpeed();
	//int getRotation();
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
	bool busy;
	int manualProgram;

private:
	Motors motors;
	LEDS leds;
	int program;
	int motorSpeed;
	int manual;
};