/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/
#include <Servo.h>
#include <EEPROM.h>
#include "Control.h"

Servo myservo, myservo2;

Encoder motorRight(enc1, enc2);
Encoder motorLeft(enc3, enc4);
Control control;
int currentDirection, motorStatus, motorSpeed, program, positionRight, encoderRun, positionLeft, pos = 0;

void setup()
{
	Serial.begin(9600);
	Serial.println("Started!");
	myservo.attach(9);
	myservo2.attach(10);
	pos = 180;

	myservo.write(pos);
	myservo2.write(180 - pos);	// tell servo to go to position in variable 'pos'
	delay(150);                       // waits 15ms for the servo to reach the position

}

void loop()
{

	for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
										  // in steps of 1 degree
		myservo.write(pos);
		myservo2.write(180 - pos);	// tell servo to go to position in variable 'pos'
		delay(10);                       // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
		myservo.write(pos);
		myservo2.write(180 - pos);	// tell servo to go to position in variable 'pos'
		delay(10);                       // waits 15ms for the servo to reach the position
	}

	//control.run();
}
