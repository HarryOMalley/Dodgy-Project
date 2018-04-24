/*
Name:		tri-track.ino
Created:	4/20/2018 02:46:27 AM
Author:	kushalpankhania
*/
//#include "motors.h"
#include "classes.h"
/*
// pins used for ultrasonic sensors
#define trigPin 51
#define echoPin 53

// Defines FB and LR as float values for sending to the sabertooth.
#define neutral 90
#define LR 20
#define FB 20
*/

// Defines all the servos and usb devices.
/* servo
1 rotating base
2 rising base
3 elbow lower
4 elbow higher
5 wrist
6 claw
160 = closed do not close any further
30 = open do not open any further
*/

//Servos
/*Servo myservo1; // base
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6; // claw*/

// global variables
IO io;

void setup() {
	Serial.begin(9600);
  Serial.println("setup");
}

void loop() {
	io.run();
	delay(100);
	/*
		if (newProgram == 0)
	{
		// do nothing
	}
	else
	{
		int program = newProgram;
		Serial.print("Program: ");
		Serial.println(program);
		servoRun(program);
		//motorRun(program);
	}
	//motors.run();
	*/
}

/*
void drive(float LeftRight, float FrontBack) {
	motor2.write(LeftRight); // Writes value to sabtertooth to drive motors
	motor1.write(FrontBack);
}

void floorDetect() {
	float distance, duration;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) / 29.1;
	if (distance > 4.00) {
		Serial.println("HOLE!");
		drive(neutral, neutral);
		delay(500);
		drive(neutral, neutral - FB);
		delay(700);
		drive(neutral, neutral);
	}
	Serial.print(distance);
	delay(10);
}
*/
