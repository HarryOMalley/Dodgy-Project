// control.h

#ifndef _CLASSES_h
#define _CLASSES_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include "arm.h"
#include <EEPROM.h>

// eeprom memory locatcontrolns
// motor variables
// move to motor header file
#define motorSpeed 0
#define motorDirectcontroln 1
#define motorStatus 2

// pwm pins
#define status 11
#define pwm2 12
#define pwm3 12

/*
Servo motor1;
Servo motor2;
*/

class control
{
public:
	control();
	void run();/*
	int getSpeed();
	void updateEEPROM(int locatcontroln, int save);*/
  bool busy;
  int manualProgram;
private:
	int program;
	arm tri_track;
};
#else
	#include "WProgram.h"
#endif

#endif

