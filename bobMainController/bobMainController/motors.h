#pragma once
#include <EEPROM.h>
#include "config.h"
#include <Arduino.h>
class Motors
{
public:
	Motors();
	~Motors();
	void motorReverse();
	void setDirectionForwards();
	void setDirectionBackwards();
	void getStatus();
	void motorOn();
	void motorOff();
	void setSpeed();
	void rotate();
	void setup();
	void run(int);
	void run();
	void updateEEPROM();
private:
	int currentDirection;
	int motorStatus;
	int motorSpeed;
};