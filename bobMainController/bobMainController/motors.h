#pragma once

#include <EEPROM.h>
#include <Arduino.h>
#include <Encoder.h>
#include "config.h"
extern Encoder motorRight, motorLeft;
class Motors
{
public:
	Motors();
	~Motors();
	void setup();
	void run();
	void motorOff();
	void setSpeed(int);
	void motorOn();
	void motorReverse();
	void setDirection(int);
	void getStatus();
	void turn(int);
	void rotate();
	int getRotation();
	int getRotationDirection();
	void move(int);
	void updateEEPROM(int, int, int);
	long readMotors();
	void resetMotors();
private:
	int currentDirection;
	int motorStatus;
	int motorSpeed;
	
	//Encoder motorRight, motorLeft;
};