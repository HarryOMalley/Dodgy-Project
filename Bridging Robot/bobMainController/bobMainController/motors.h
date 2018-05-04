#pragma once

#include <EEPROM.h>
#include <Arduino.h>
#include <Encoder.h>
#include "config.h"

class Motors
{
public:
	Motors();
	~Motors();
	void setup();
	void run();
	void motorOff();
	void setSpeed(int newSpeed);
	void motorOn();
	void motorReverse();
	void setDirection(int direction);
	void getStatus();
	void turn(int);
	void rotate();
	void move(int);
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
	long readMotors();
	void resetMotors();
private:
	int currentDirection;
	int motorStatus;
	int motorSpeed;
	//Encoder motorRight, motorLeft;
};