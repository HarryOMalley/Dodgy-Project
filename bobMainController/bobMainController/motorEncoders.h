#include <Encoder.h>
#include <Arduino.h>
#include "config.h"
class motorEncoders
{
public:
	motorEncoders();
	~motorEncoders();
	long readMotors();
	void resetMotors();
private:
	long positionLeft;
	long positionRight;
	Encoder motorRight, motorLeft; // I added Encoder(){} to the library so there was a default constructor, otherwise the object cannot be initialised without arguments
};


