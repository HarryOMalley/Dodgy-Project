// arm.h

#ifndef _ARM_h
#define _ARM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include <Servo.h>
#include <EEPROM.h>

class arm {
public:
	//int* fillarr(int arr[])
	arm(int, int, int, int, int, int);
	int servoRun(int);
	int servoRun(int, int);
	void servoAttach();
	void servoDetach();
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
	int s1, s2, s3, s4, s5, s6 = -1;
	#define armState 21
};

#else
	#include "WProgram.h"
#endif


#endif
