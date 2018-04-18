#include "motorEncoders.h"

motorEncoders::motorEncoders(int pin1, int pin2, int pin3, int pin4)
{
	Encoder motorRight(pin1, pin2);
	Encoder motorLeft(pin3, pin4);
}

motorEncoders::~motorEncoders()
{
}

long motorEncoders::readMotors()
{
	long newRight, newLeft;
	newRight = motorRight.read();
	newLeft = motorLeft.read();
	return newLeft, newRight;
}