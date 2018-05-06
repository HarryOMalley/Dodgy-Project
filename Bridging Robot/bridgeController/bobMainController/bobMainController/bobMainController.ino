/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/

#include <Servo.h>
#include <EEPROM.h>
#include "Control.h"
Servo myservo, myservo2;
USB Usb;
XBOXRECV Xbox(&Usb);
Encoder motorRight(enc1, enc2);
Encoder motorLeft(enc3, enc4);
Control control;
int currentDirection, motorStatus, motorSpeed, program, positionRight, encoderRun, positionLeft, pos = 0;

void setup()
{
	Serial.begin(9600);
#if !defined(__MIPSEL__)
	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
	if (Usb.Init() == -1) {
		Serial.print(F("\r\nOSC did not start"));
		while (1); //halt
	}
	Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
	Serial.println("Started!");
	//myservo.attach(9);
	//myservo2.attach(10);
	pos = 180;

	myservo.write(pos);
	myservo2.write(180 - pos);	// tell servo to go to position in variable 'pos'
	delay(150);                       // waits 15ms for the servo to reach the position

}

void loop()
{

	Usb.Task();
	if (Xbox.XboxReceiverConnected) {
		for (uint8_t i = 0; i < 4; i++) {
			if (Xbox.Xbox360Connected[i]) {
				if (Xbox.getButtonClick(Y, i)) { // manual override/mqtt mode
					if (io.busy == true) {
						io.busy = false;
					}
					else {
						io.busy = true;
						io.manualProgram = 0;
						delay(100);
					}
				}
				if (io.busy == true) {
					io.run();
					//delay(100);
				}
				else if (io.busy == false) {
					if ((Xbox.getAnalogHat(LeftHatX, i) > 8000 || Xbox.getAnalogHat(LeftHatX, i) < -8000 || Xbox.getAnalogHat(LeftHatY, i) > 8000 || Xbox.getAnalogHat(LeftHatY, i) < -8000)) {
						LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
						FB = Xbox.getAnalogHat(LeftHatY, i);
						LR = LR * -1; // Converts the recieved value from controller to a value between 30 and 150 which is what the servos work off.
						LR = LR / 32768;
						LR = LR * 60;
						LR = LR + 90;
						/*Serial.print(F("LeftHatX: ")); // Used for debugging.
						Serial.print(LR);
						Serial.print("\t");*/
						FB = FB * -1; // Same process, but for the forward backward movement.
						FB = FB / 32768;
						FB = FB * 60;
						FB = FB + 90;
						drive(LR, FB);
					}
					else {
						drive(neutral, neutral); // dont turn the motors if nothing from analogue or deadzone
					}
					//          Serial.print(motor1.read());
					//          Serial.print("  ");
					//          Serial.println(motor2.read());
					if (Xbox.getButtonClick(X, i)) { // compact
						io.manualProgram = 1;
						io.run();
					}
					if (Xbox.getButtonClick(A, i)) { // stabmode
						io.manualProgram = 2;
						io.run();
					}
					if (Xbox.getButtonClick(B, i)) { // flick
						io.manualProgram = 3;
						io.run();
					}
				}
			}
		}
	
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
