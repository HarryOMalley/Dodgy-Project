/* Arm testing code to make the servos go from lowest position to highest postion, only really useful to test if they are working.
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;		// twelve servo objects can be created on most boards
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;

float pos = 0;    // variable to store the servo position

void setup() {
	myservo.attach(2);		// attaches the servo owhat voltn pin 9 to the servo object
	myservo2.attach(3);
	myservo3.attach(4);
	myservo4.attach(5);
	myservo5.attach(6);
	myservo6.attach(7);
	myservo7.attach(8);
	myservo8.attach(9);

	myservo6.write(90);
	myservo7.write(0);

	Serial.begin(9600);
}

void loop() {
	for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees
										  // in steps of 1 degree
		myservo.write(pos);				  // tell servo to go to position in variable 'pos'
		myservo2.write(pos);
		myservo3.write(pos);
		myservo4.write(pos);
		myservo5.write(pos);
		myservo6.write(pos);
		myservo7.write(pos);
		myservo8.write(pos);

		delay(1);                       // waits 15ms for the servo to reach the position
		Serial.println("Im doing something!");
	}
	for (pos = 180; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
										  //myservo.write(pos);              // tell servo to go to position in variable 'pos'
		myservo.write(pos);				  // tell servo to go to position in variable 'pos'
		myservo2.write(pos);
		myservo3.write(pos);
		myservo4.write(pos);
		myservo5.write(pos);
		myservo6.write(pos);
		myservo7.write(pos);
		myservo8.write(pos);
		delay(1);                       // waits 15ms for the servo to reach the position
		Serial.println("Im doing something different!");
	}
}