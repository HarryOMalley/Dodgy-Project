#include "motorEncoders.h"

motorEncoders::motorEncoders()
{

}

motorEncoders::~motorEncoders()
{
}

readings motorEncoders::read()
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
