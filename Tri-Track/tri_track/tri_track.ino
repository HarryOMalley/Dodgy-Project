/*
  Name:		tri-track.ino
  Created:	4/20/2018 02:46:27 AM
  Author:	kushalpankhania
*/
//#include "motors.h"
#include <XBOXRECV.h>
#include <Servo.h>
#include "io.h"

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
float FB, LR;

// global variables
IO io;

void setup() {
  Serial.begin(9600);
  motor1.attach(9); // Attaches a pin to a servo.
  motor2.attach(8);

#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  io.busy = true;
  io.manualProgram = 0;
}

void loop() {
  //***********************************-XBOX CONTROLLER-*************************************//
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonClick(Y, i)) { // manual override/mqtt mode
          if (io.busy == true) {
            io.busy = false;
          } else {
            io.busy = true;
            io.manualProgram = 0;
            delay(100);
          }
        }
        if (io.busy == true) {
          io.run();
          //delay(100);
        } else if (io.busy == false) {
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
          } else {
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
}
/*
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
