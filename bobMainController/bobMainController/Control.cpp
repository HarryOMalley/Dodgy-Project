#include "Control.h"

Control::Control()
{
	program = 0;
}

Control::~Control()
{
}

void Control::run()
{
	int newProgram;
	newProgram = getInput();
	while (Serial.available() > 0)
	{
		Serial.println("recieved");
		newProgram = Serial.parseInt();
	}
	if (newProgram == 0)
	{
		motors.run();
	}
	else
	{
		program = newProgram;
		Serial.print("Program: ");
		Serial.println(program);
	}
	switch (newProgram)
	{
	case 1: // off
		motors.motorOff();
		break;
	case 2: // on
		motors.motorOn();
		break;
	case 3: // change direction
		motors.motorReverse();
		break;
	case 4:
		motors.setDirection(1); // forwards
		break;
	case 5:
		motors.setDirection(0); // backwards
		break;
	case 6:
		motors.setSpeed(getSpeed());
		break;
	case 7:
		motors.rotate(0); // right
		break;
	case 8:
		motors.rotate(1); // left
		break;
	case 9:
		motors.rotate(); // different angle
		break;
	case 10:
		motors.getStatus(); // get current speed etc.
		break;
	case 11:
		motors.calibrate();
		break;
	default: // run the motors
		motors.run();
		break;
	}

	return;
}

int Control::getInput()
{
	int check;
	check = digitalRead(pwm1);
	if (check != 1)
		return 0;
	int newProgram;
	newProgram = pulseIn(pwm2, HIGH);
	//Serial.print("input: ");
	//Serial.println(newProgram);
	if (newProgram > 500 && newProgram < 1500)
		program = 1;
	else if (newProgram > 1500 && newProgram < 2500)
		program = 2;
	else if (newProgram > 2500 && newProgram < 3500)
		program = 3;
	else if (newProgram > 3500 && newProgram < 4500)
		program = 4;
	else if (newProgram > 4500 && newProgram < 5500)
		program = 5;
	else if (newProgram > 5500 && newProgram < 6500)
		program = 6;
	else if (newProgram > 6500 && newProgram < 7500)
		program = 7;
	else if (newProgram > 7500 && newProgram < 8500)
		program = 8;
	else if (newProgram > 8500 && newProgram < 9500)
		program = 9;
	else
		return 0;
	return program;
}

int Control::getSpeed()
{
	int newSpeed;
	newSpeed = (pulseIn(pwm3, HIGH)) / 10;
	Serial.println(newSpeed);
	return newSpeed;
}


void Control::updateEEPROM(int motorSpeed, int motorStatus, int currentDirection)
{
	EEPROM.write(MOTOR_SPEED, motorSpeed);
	EEPROM.write(MOTOR_STATUS, motorStatus);
	EEPROM.write(MOTOR_DIRECTION, currentDirection);
}

long Control::readMotors()
{

}

void Control::resetMotors()
{

}

