#include <Encoder.h>
#include <Arduino.h>
#include "config.h"
extern Encoder motorRight, motorLeft;
struct readings { int right; int left; };
class motorEncoders
{
public:
	motorEncoders();
	~motorEncoders();
	auto read();
	void reset();
	int speedRight();
	int speedLeft();
	void calibrate(void);
private:
	long positionLeft;
	long positionRight;
	int rightMotorAnalogue;
	int leftMotorAnalogue;
};


