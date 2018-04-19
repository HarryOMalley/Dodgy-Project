#pragma once
#include <EEPROM.h>
#include <Arduino.h>
#include "motorEncoders.h"
#include "IO.h"
class Motors
{
public:
	Motors();
	~Motors();
	void motorReverse();
	void setDirection(int direction);
	void getStatus();
	void motorOn();
	void motorOff();
	void setSpeed();
	void rotate();
	void setup();
	void run(int);
	void run();
	void updateEEPROM();
	void turn(int);
	void move(int);
private:
	int currentDirection;
	int motorStatus;
	int motorSpeed;
	motorEncoders encoder;
};