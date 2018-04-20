#pragma once
#include <EEPROM.h>
#include <Arduino.h>
#include "motorEncoders.h"

class IO
{
public:
	IO();
	int getInput();
	int getSpeed();
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
private:
	int program;
};

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
	void turn(int);
	void move(int);
	void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection);
	
private:
	int currentDirection;
	int motorStatus;
	int motorSpeed;
	motorEncoders encoder;
	IO io;
};