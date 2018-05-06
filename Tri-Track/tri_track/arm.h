// arm.h

#ifndef _ARM_h
#define _ARM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include <Servo.h>
#include <EEPROM.h>

class arm {
public:
	arm();
	int servoRun(int);
	int servoRun(int, int);
	void servoAttach();
	void servoDetatch();
	void compactMode();
	void stabMode();
	void flickSwitch();
	void rotate(int);
private:
	void saveState(int);
	Servo servo1;
	Servo servo2;
	Servo servo3;
	Servo servo4;
	Servo servo5;
	Servo servo6;
	//int s1, s2, s3, s4, s5, s6 = -1;
  int s1 = 2;
  int s2 = 3;
  int s3 = 4;
  int s4 = 5;
  int s5 = 6;
  int s6 = 7;
	#define armState 21
};

#else
	#include "WProgram.h"
#endif


#endif
