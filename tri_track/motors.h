// motors.h

#ifndef _MOTORS_h
#define _MOTORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
// 
// 
// 
/*

*/
class motor {
public:
	motor();
	~motor();
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
	// motor one
	#define enA 10
	#define in1 9
	#define in2 8
	// motor two
	#define enB 5
	#define in3 7
	#define in4 6
	int currentDirection;
	int motorStatus;
	int motorSpeed;
	motor Encoders encoder;
	IO io;
};
#else
	#include "WProgram.h"
#endif


#endif

