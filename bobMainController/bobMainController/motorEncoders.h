#include <Encoder.h>
#include <Arduino.h>
class motorEncoders
{
public:
	motorEncoders(int pin1, int pin2, int pin3, int pin4);
	~motorEncoders();
	long readMotors();
private:
	long positionLeft;
	long positionRight;
	Encoder motorRight, motorLeft; // I added Encoder(){} to the library so there was a default constructor, otherwise the object cannot be initialised without arguments
};


