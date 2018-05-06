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
	readings read();
	void reset();
private:
	long positionLeft;
	long positionRight;
};


