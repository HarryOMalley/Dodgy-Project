#include "motorEncoders.h"

motorEncoders::motorEncoders()
{
	//Encoder motorRight(enc1, enc2);
	//Encoder motorLeft(enc3, enc4);
}

motorEncoders::~motorEncoders()
{
}

long motorEncoders::readMotors()
{
	long newRight, newLeft;
	newRight = motorRight.read();
	newLeft = motorLeft.read();
	Serial.print("Read Encoders ");
	Serial.print(newRight);
	Serial.println(newLeft);
	return newLeft, newRight;
}

void motorEncoders::resetMotors()
{
	motorRight.write(0);
	motorLeft.write(0);
	Serial.println("reset the motors");
}
