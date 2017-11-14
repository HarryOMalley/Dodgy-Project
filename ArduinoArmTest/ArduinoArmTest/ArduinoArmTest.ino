/* Arm testing code to make the servos go crazy
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;		// twelve servo objects can be created on most boards
Servo myservo4;
Servo myservo5;
Servo myservo6;

float pos = 0;    // variable to store the servo position

void setup() {
	myservo.attach(8);		// attaches the servo owhat voltn pin 9 to the servo object
	myservo2.attach(9);
	myservo3.attach(10);
	myservo4.attach(11);
	myservo5.attach(12);
	myservo6.attach(13);

	myservo.write(90);
	myservo3.write(0);

	Serial.begin(9600);
}

void loop() {
	for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees
										  // in steps of 1 degree
										  // tell servo to go to position in variable 'pos'
		myservo2.write(pos);

		myservo4.write(pos);
		myservo5.write(pos);
		myservo6.write(pos);
		delay(1);                       // waits 15ms for the servo to reach the position
		Serial.println("Im doing something!");
	}
	for (pos = 180; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
										  //myservo.write(pos);              // tell servo to go to position in variable 'pos'
		myservo2.write(pos);
		//myservo3.write(pos);
		myservo4.write(pos);
		myservo5.write(pos);
		myservo6.write(pos);
		delay(1);                       // waits 15ms for the servo to reach the position
		Serial.println("Im doing something different!");
	}
}