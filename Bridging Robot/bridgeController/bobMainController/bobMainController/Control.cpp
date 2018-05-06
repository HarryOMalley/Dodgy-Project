#include "Control.h"

Control::Control()
{
	program = 0;
	motorSpeed = 100;
}

Control::~Control()
{
}

void Control::run()
{


	if (xbox() == 0)
	{

		int newProgram;
		newProgram = getInput();
		while (Serial.available() > 0)
		{
			Serial.println("recieved");
			newProgram = Serial.parseInt();
		}
		if (newProgram == 0)
		{
			motors.run();
		}
		else
		{
			program = newProgram;
			Serial.print("Program: ");
			Serial.println(program);
		}
		switch (newProgram)
		{
		case 1: // off
			motors.motorOff();
			break;
		case 2: // on
			motors.motorOn();
			break;
		case 3: // change direction
			motors.motorReverse();
			break;
		case 4:
			motors.setDirection(1); // forwards
			break;
		case 5:
			motors.setDirection(0); // backwards
			break;
		case 6:
			motorSpeed += 20;
			motors.setSpeed(motorSpeed);
			break;
		case 7:
			motorSpeed -= 20;
			motors.setSpeed(motorSpeed);
			//motors.rotate(0); // right
			break;
		case 8:
			motors.rotate(1); // left
			break;
		case 9:
			motors.rotate(); // different angle
			break;
		case 10:
			motors.getStatus(); // get current speed etc.
			break;
		case 11:
			//motors.calibrate();
			break;
		case 12:
			arm.up(10);
		case 13:
			arm.down(10);
		default: // run the motors
			motors.run();
			break;
		}
		return;
	}
	else
		manualControl();
}

int Control::xbox()
{
	Usb.Task();
	if (Xbox.XboxReceiverConnected)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (Xbox.Xbox360Connected[i])
			{
				if (Xbox.getButtonClick(Y, i))
				{ // manual override/mqtt mode
					if (busy == true) 
					{
						busy = false;
					}
					else
					{
						busy = true;
						manualProgram = 0;
						delay(100);
					}
				}
				if (busy == true)
				{
					run();
					//delay(100);
				}
				else if (busy == false)
				{
					if ((Xbox.getAnalogHat(LeftHatX, i) > 8000 || Xbox.getAnalogHat(LeftHatX, i) < -8000 || Xbox.getAnalogHat(LeftHatY, i) > 8000 || Xbox.getAnalogHat(LeftHatY, i) < -8000))
					{
						LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
						FB = Xbox.getAnalogHat(LeftHatY, i);
						LR = LR * -1; // Converts the recieved value from controller to a value between 30 and 150 which is what the servos work off.
						LR = LR / 32768;
						LR = LR * 60;
						LR = LR;
						/*Serial.print(F("LeftHatX: ")); // Used for debugging.
						Serial.print(LR);
						Serial.print("\t");*/
						FB = FB * -1; // Same process, but for the forward backward movement.
						FB = FB / 32768;
						FB = FB * 60;
						FB = FB + 90;
						drive(LR, FB);
					}
					else 
					{
						drive(neutral, neutral); // dont turn the motors if nothing from analogue or deadzone
					}
					//          Serial.print(motor1.read());
					//          Serial.print("  ");
					//          Serial.println(motor2.read());
					if (Xbox.getButtonClick(X, i)) // compact
					{ 
						manualProgram = 1;
						run();
					}
					if (Xbox.getButtonClick(A, i)) // stabmode
					{ 
						manualProgram = 2;
						run();
					}
					if (Xbox.getButtonClick(B, i)) // flick
					{ 
						manualProgram = 3;
						run();
					}
				}
			}
		}
	}
	if ((manualProgram == 0) && (busy)) {
		return 0;
		if (check != 0) {
			Serial.println("run from mqtt");
			if (newProgram > 500 && newProgram < 1500) { // compact
				tri_track.servoRun(1);
			}
			else if (newProgram > 1500 && newProgram < 2500) // stab
				tri_track.servoRun(2);
			else if (newProgram > 2500 && newProgram < 3500) // flick
				tri_track.servoRun(3);
			else if (newProgram > 3500 && newProgram < 4500) //
				tri_track.servoRun(4);
			else if (newProgram > 4500 && newProgram < 5500) //
				tri_track.servoRun(5);
			if (rotation == 0) {
				tri_track.servoRun(6, 0);
			}
			else if (rotation == 1) {
				tri_track.servoRun(6, 1);
			}
		}
	}
	else if (manualProgram != 0) {
		if (manualProgram == 1) // compact
			tri_track.servoRun(1);
		if (manualProgram == 2) // stab
			tri_track.servoRun(2);
		if (manualProgram == 3) // flick
			tri_track.servoRun(3);
		manualProgram = 0;
	}
}

void Control::manualControl()
{

}

int Control::getInput()
{
	int check;
	check = digitalRead(pwm1);
	if (check != 1)
		return 0;
	int newProgram;
	newProgram = pulseIn(pwm2, HIGH);
	//Serial.print("input: ");
	//Serial.println(newProgram);
	if (newProgram > 500 && newProgram < 1500)
		program = 1;
	else if (newProgram > 1500 && newProgram < 2500)
		program = 2;
	else if (newProgram > 2500 && newProgram < 3500)
		program = 3;
	else if (newProgram > 3500 && newProgram < 4500)
		program = 4;
	else if (newProgram > 4500 && newProgram < 5500)
		program = 5;
	else if (newProgram > 5500 && newProgram < 6500)
		program = 6;
	else if (newProgram > 6500 && newProgram < 7500)
		program = 7;
	else if (newProgram > 7500 && newProgram < 8500)
		program = 8;
	else if (newProgram > 8500 && newProgram < 9500)
		program = 9;
	else
		return 0;
	return program;
}

int Control::getSpeed()
{
	int newSpeed;
	newSpeed = (pulseIn(pwm3, HIGH)) / 10;
	Serial.println(newSpeed);
	return newSpeed;
}


void Control::updateEEPROM(int motorSpeed, int motorStatus, int currentDirection)
{
	EEPROM.write(MOTOR_SPEED, motorSpeed);
	EEPROM.write(MOTOR_STATUS, motorStatus);
	EEPROM.write(MOTOR_DIRECTION, currentDirection);
}

long Control::readMotors()
{

}

void Control::resetMotors()
{

}
