#include "Control.h"
USB Usb;
XBOXRECV Xbox(&Usb);

Control::Control()
{
	program = 0;
	motorSpeed = 100;
	manual = 1;
	if (Usb.Init() == -1) {
		Serial.print(F("\r\nOSC did not start"));
		while (1);
		{

		}//halt
	}
}

Control::~Control()
{
}

void Control::setup()
{
	leds.setup();
}

void Control::run()
{
	int check = xbox();
	if (check == 0)
	{
		int newProgram;
		newProgram = getInput();
		if (newProgram == 0)
		{
			motors.run();
			return;
		}
		else
		{
			program = newProgram;
			Serial.print("Program: ");
			Serial.println(program);
		}
		while (Serial.available() > 0)
		{
			Serial.println("recieved");
			newProgram = Serial.parseInt();
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
			//motorSpeed += 20;
			motors.setSpeed(getSpeed());
			break;
		case 7:
			//motorSpeed -= 20;
			motors.setSpeed(getSpeed());
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

		case 13:

		default: // run the motors
			motors.run();
			break;
		}
		return;
	}
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
				if (manual == 0) // checking if you want to change to manual control first
				{
					if (Xbox.getButtonClick(Y, i))
					{
						manual = 1;
					}
				}
				if (manual == 1)
				{
					if (Xbox.getButtonClick(B, i)) // if now in manual mode, checking if you want to go into automatic control
					{
						manual = 0;
						return 0;
					}
					if (Xbox.getButtonPress(R2, i) > 10) // in manual control, now is doing the calculations to move using the xbox controller
					{
						int speed = Xbox.getButtonPress(R2, i);
						digitalWrite(in1, HIGH); // turn on
						digitalWrite(in2, LOW);
						digitalWrite(in3, HIGH); // turn on
						digitalWrite(in4, LOW);
						analogWrite(enA, speed - (speed / 10)); // attempting to fix the slow drift, will need to experiment with this
						analogWrite(enB, speed);
						delay(10);
					}
					else if (Xbox.getButtonPress(L2, i) > 10)
					{
						int speed = Xbox.getButtonPress(L2, i);
						digitalWrite(in1, LOW); // turn on
						digitalWrite(in2, HIGH);
						digitalWrite(in3, LOW); // turn on
						digitalWrite(in4, HIGH);
						analogWrite(enA, speed);
						analogWrite(enB, speed);
						delay(10);
					}
					else
					{
						digitalWrite(in1, LOW); // turn off
						digitalWrite(in2, LOW);
						digitalWrite(in3, LOW); // turn off
						digitalWrite(in4, LOW);
					}

					if ((Xbox.getAnalogHat(LeftHatX, i) > 8000 || Xbox.getAnalogHat(LeftHatX, i) < -8000)) // turning right and left
					{
						int LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
						float leftRight, forwardsBackwards;
						if (LR > 0) // right
						{
							leftRight = (LR / 32768) * 255; // scaling to 0 to 255, rather than 0 to -32768 for analogWrite
							digitalWrite(in1, LOW); // turn on
							digitalWrite(in2, HIGH);
							analogWrite(enA, leftRight);
							digitalWrite(in3, HIGH); // turn on
							digitalWrite(in4, LOW);
							analogWrite(enB, leftRight);
							delay(10);
						}
						else if (LR < 0) // right
						{

							leftRight = (-LR / 32768) * 255; // scaling to 0 to 255, rather than 0 to -32768 for analogWrite
							digitalWrite(in1, HIGH); // turn on
							digitalWrite(in2, LOW);
							analogWrite(enA, leftRight);
							digitalWrite(in3, LOW); // turn on
							digitalWrite(in4, HIGH);
							analogWrite(enB, leftRight);
							delay(10);
						}
					}
					if (Xbox.getButtonClick(UP, i))
					{
						Xbox.setLedOn(LED1, i);
						leds.set(255, 0, 0);
					}
					if (Xbox.getButtonClick(DOWN, i))
					{
						Xbox.setLedOn(LED4, i);
						leds.set(0, 255, 0);
					}
					if (Xbox.getButtonClick(LEFT, i))
					{
						Xbox.setLedOn(LED3, i);
						Serial.println(F("Left"));
						leds.set(0, 0, 255);
					}
					if (Xbox.getButtonClick(RIGHT, i))
					{
						Xbox.setLedOn(LED2, i);
						Serial.println(F("Right"));
						leds.set(255, 0, 255);
					}
					if (Xbox.getButtonClick(START, i))
					{
						Xbox.setLedMode(ALTERNATING, i);
						Serial.println(F("Start"));

					}
					if (Xbox.getButtonClick(BACK, i))
					{
						Xbox.setLedBlink(ALL, i);
						Serial.println(F("Back"));
					}
					if (Xbox.getButtonClick(L3, i))
						Serial.println(F("L3"));
					if (Xbox.getButtonClick(R3, i))
						Serial.println(F("R3"));

					if (Xbox.getButtonClick(L1, i))
						Serial.println(F("L1"));
					if (Xbox.getButtonClick(R1, i))
						Serial.println(F("R1"));
					if (Xbox.getButtonClick(XBOX, i))
					{
						Xbox.setLedMode(ROTATING, i);
						Serial.print(F("Xbox (Battery: "));
						Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
						Serial.println(F(")"));
					}
					if (Xbox.getButtonClick(SYNC, i))
					{
						Serial.println(F("Sync"));
						Xbox.disconnect(i);
					}
					if (Xbox.getButtonClick(A, i))
						Serial.println(F("A"));
					if (Xbox.getButtonClick(B, i))
						Serial.println(F("B"));
					if (Xbox.getButtonClick(X, i))
						Serial.println(F("X"));
					if (Xbox.getButtonClick(Y, i))
						Serial.println(F("Y"));
				}
				else
					return 0;
			}
			else if (manual == 1)
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
		}
	}
	else
	{
		return 0; //Serial.println("not connected to controller");
	}
}

int Control::getInput()
{
	int check;
	check = digitalRead(pwm1);
	if (check != 1)
		return 0;
	int newProgram;
	newProgram = pulseIn(pwm2, HIGH);
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