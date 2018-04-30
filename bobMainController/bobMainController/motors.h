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
	long readMotors();
	void resetMotors();
	void getStatus();
	int motorSpeedRight();
	int motorSpeedLeft();
	void calibrate(void);
private:
	int currentDirection;
	int motorStatus;
	int motorSpeed;
	int rightMotorAnalogue;
	int leftMotorAnalogue;
	//Encoder motorRight, motorLeft;
};