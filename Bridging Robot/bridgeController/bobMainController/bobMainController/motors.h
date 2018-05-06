#pragma once

#include <EEPROM.h>
#include <Arduino.h>
#include "motorEncoders.h"
#include "config.h"

class Motors
{
public:
	Motors();
	~Motors();
	void setup();
	void run();
	void motorReverse();
	void setDirection(int direction);
	void motorOn();
	void motorOff();
	void setSpeed(int newSpeed);
	void rotate(int direction);
	void rotate();
	int getRotation();
	int getRotationDirection();
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
	void getStatus();
	//void calibrate(void); need to fix this, or not use
private:
	int currentDirection;
	int motorStatus;
	int motorSpeed;
	motorEncoders encoders;
};