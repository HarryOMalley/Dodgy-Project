/*
  Name:		tri-track.ino
  Created:	4/20/2018 02:46:27 AM
  Author:	kushalpankhania
*/
//#include "motors.h"
#include <XBOXRECV.h>
#include <Servo.h>
#include "control.h"

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

#define neutral 90
#define LRboard 20
#define FBboard 20

USB Usb;
XBOXRECV Xbox(&Usb);

Servo motor1;
Servo motor2;

// global variables
float FB = 90;
float LR = 90;

// global variables
control control;

void setup() {
  Serial.begin(9600);
  motor1.attach(12); // Attaches a pin to a servo.
  motor2.attach(11);

#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connectcontroln
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  control.busy = true;
  control.manualProgram = 0;
}

void loop() {
  //***********************************-XBOX CONTROLLER-*************************************//
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonClick(Y, i)) { // manual override/mqtt mode
          Serial.println("y");
          drive(90, 90);
          if (control.busy == true) {
            control.busy = false;
          } else {
            control.busy = true;
            control.manualProgram = 0;
            delay(100);
          }
        }
        if (control.busy == true) {
          control.run();
          //delay(100);
        } else if (control.busy == false) {
          if ((Xbox.getAnalogHat(LeftHatX, i) > 8000 || Xbox.getAnalogHat(LeftHatX, i) < -8000 || Xbox.getAnalogHat(LeftHatY, i) > 8000 || Xbox.getAnalogHat(LeftHatY, i) < -8000)) {
            LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
            //FB = Xbox.getAnalogHat(LeftHatY, i);
            LR = LR * -1; // Converts the recieved value from controller to a value between 30 and 150 which is what the servos work off.
            LR = LR / 32768;
            LR = LR * 60;
            LR = LR + 90;
            //Serial.print(LR);
            delay(10);

          } else {
            LR = 90;
            delay(10);
          }
          if (Xbox.getButtonPress(R2, i) > 10) {
            FB = Xbox.getButtonPress(R2, i);
            FB = map(FB, 0, 255 , 90, 30);
          } else if (Xbox.getButtonPress(L2, i) > 10) {
            FB = Xbox.getButtonPress(L2, i);
            FB = map(FB, 0, 255 , 90, 150);
          } else {
            FB = 90;
          }
          drive(LR, FB); // dont turn the motors if nothing from analogue or deadzone

          Serial.print("  ");
          //          Serial.println(motor2.read());
          if (Xbox.getButtonClick(DOWN, i)) { 
          }
          if (Xbox.getButtonClick(LEFT, i)) {
            control.manualProgram = 1;
            control.run();
          }
          if (Xbox.getButtonClick(RIGHT, i)) { 
            control.manualProgram = 2;
            control.run();
          }
          if (Xbox.getButtonClick(UP, i)) { 
            control.manualProgram = 3;
            control.run();
          }
        }
      }
    }
  }
  //***********************************-XBOX CONTROLLER-*************************************//
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

void drive(float LeftRight, float FrontBack) {
  motor2.write(LeftRight); // Writes value to sabtertooth to drive motors
  motor1.write(FrontBack);
  //  Serial.print(FrontBack);
  //  Serial.print("  ");
  //  Serial.println(LeftRight);
}

/*
  void floorDetect() {
	float distance, duratcontroln;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duratcontroln = pulseIn(echoPin, HIGH);
	distance = (duratcontroln / 2) / 29.1;
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
