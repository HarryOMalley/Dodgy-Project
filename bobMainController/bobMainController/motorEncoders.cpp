#include "motorEncoders.h"

motorEncoders::motorEncoders()
{
	rightMotorAnalogue = 0;
	leftMotorAnalogue = 0;
}

motorEncoders::~motorEncoders()
{
}

auto motorEncoders::read()
{
	long right, left;
	right = motorRight.read();
	left = motorLeft.read();
	 // returning both parameters in a struct
	return readings{ right, left };
}

void motorEncoders::reset()
{
	motorRight.write(0);
	motorLeft.write(0);
	Serial.println("Reset the motors");
}

int motorEncoders::speedRight()
{
	int calibratedSpeed = motorSpeed + rightMotorAnalogue;
	return calibratedSpeed;
}

int motorEncoders::speedLeft()
{
	int calibratedSpeed = motorSpeed + leftMotorAnalogue;
	return calibratedSpeed;
}
