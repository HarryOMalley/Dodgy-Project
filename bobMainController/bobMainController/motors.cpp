#include "motors.h"

Motors::Motors()
{
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(pwm1, INPUT);
	pinMode(pwm2, INPUT);
	pinMode(pwm3, INPUT);
	setup();
}

Motors::~Motors()
{
}

void Motors::setup()
{
	currentDirection = EEPROM.read(MOTOR_DIRECTION);
	motorStatus = EEPROM.read(MOTOR_STATUS);
	motorSpeed = EEPROM.read(MOTOR_SPEED);
	if (currentDirection == 0)
	{
		currentDirection = 1;
		EEPROM.write(MOTOR_DIRECTION, currentDirection);
		Serial.println("Changed Motor Direction");
	}
	if (motorStatus == 0)
	{
		motorStatus = 1;
		EEPROM.write(MOTOR_STATUS, motorStatus);
		Serial.println("Changed Motor Status");
	}
	if (motorSpeed == 0)
	{
		motorSpeed = 100;
		EEPROM.write(MOTOR_SPEED, motorSpeed);
		Serial.println("Changed Motor Speed");
	}
	Serial.println("Current direction, status and speed are: ");
	Serial.println(currentDirection);
	Serial.println(motorStatus);
	Serial.println(motorSpeed);
}

void Motors::run()
{
	if (motorStatus == 1) // if motor is supposed to be off, keep off
	{
		digitalWrite(in1, LOW); // turn off
		digitalWrite(in2, LOW);
		digitalWrite(in3, LOW); // turn off
		digitalWrite(in4, LOW);
		return;
	}
	else
	{
		analogWrite(enA, motorSpeed);
		analogWrite(enB, motorSpeed);
		switch (currentDirection)
		{
		case 1: // forwards
			digitalWrite(in1, HIGH); // turn on
			digitalWrite(in2, LOW);
			digitalWrite(in3, HIGH); // turn on
			digitalWrite(in4, LOW);
			break;
		case 2: // backwards
			digitalWrite(in1, LOW); // turn on 
			digitalWrite(in2, HIGH);
			digitalWrite(in3, LOW); // turn on
			digitalWrite(in4, HIGH);
			break;
		default:
			// do nothing
			break;
		}
		delay(1);
		return;
	}
}

void Motors::motorReverse()
{
	if (currentDirection == 1) // right
	{
		currentDirection = 2;
		updateEEPROM(motorSpeed, motorStatus, currentDirection);
	}
	else if (currentDirection == 2) // left
	{
		currentDirection = 1;
		updateEEPROM(motorSpeed, motorStatus, currentDirection);
	}
}

void Motors::setDirection(int direction)
{
	if (direction == 0)
		currentDirection = 1;
	else
		currentDirection = 2;
	updateEEPROM(motorSpeed, motorStatus, currentDirection);
}

void Motors::motorOn()
{
	motorStatus = 2;
	updateEEPROM(motorSpeed, motorStatus, currentDirection);
	Serial.println("Turned motor on");
	return;
}

void Motors::motorOff()
{
	motorStatus = 1;
	updateEEPROM(motorSpeed, motorStatus, currentDirection);
	Serial.println("Turned motor off");
	return;
}

void Motors::setSpeed(int newSpeed)
{
	updateEEPROM(motorSpeed, motorStatus, currentDirection);
	Serial.println("Changed motor speed");
	Serial.println(motorSpeed);
}

void Motors::rotate()
{
	int angle = getRotation();
	int direction = getRotationDirection();
	float rotationRatio = 1.5;
	int rightReading, leftReading, actualAngle, rotating = 1;

	Serial.println("Input angle: ");
	while (true)
	{
		if (Serial.available())
		{
			angle = Serial.parseInt();
			break;
		}
	}

	if (angle < 0)
	{
		angle = -angle; //converting to positive
	}
	actualAngle = angle * rotationRatio;
	if (direction == 0) // right
	{
		while (rotating == 1)
		{
			rightReading = motorRight.read();
			leftReading = motorLeft.read();
			if (leftReading < actualAngle)
			{
				digitalWrite(in1, HIGH); // turn on
				digitalWrite(in2, LOW);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (rightReading > -actualAngle)
			{
				digitalWrite(in3, LOW); // turn on
				digitalWrite(in4, HIGH);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if ((leftReading > actualAngle) && (rightReading < -actualAngle))
			{
				rotating = 0;
				Serial.println("Finished turning");
				return;
			}
		}
	}
	else if (direction == 1) // left
	{
		while (rotating == 1)
		{
			rightReading = motorRight.read();
			leftReading = motorLeft.read();
			if (leftReading < actualAngle)
			{
				digitalWrite(in1, LOW); // turn on
				digitalWrite(in2, HIGH);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (rightReading > -actualAngle)
			{
				digitalWrite(in3, HIGH); // turn on
				digitalWrite(in4, LOW);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if ((leftReading > actualAngle) && (rightReading < -actualAngle))
			{
				rotating = 0;
				Serial.println("Finished turning");
				return;
			}
		}
	}
	// INSERT CODE TO ROTATE A SPECIFIC AMOUNT USING ENCODERS
	Serial.println("Changed motor speed");
}

int Motors::getRotation()
{
	int rotation;
	rotation = (pulseIn(pwm3, HIGH)) / 10;
	return rotation;
}

int Motors::getRotationDirection()
{
	int direction;
	direction = digitalRead(pwm4);
	return direction;
}

void Motors::turn(int direction) // uncalibrated turning, right, left and 180
{
	long rightReading, leftReading;
	int turning = 1;
	analogWrite(enA, 80);	// temporarily change the speed
	analogWrite(enB, 80);
	resetMotors(); // reset the encoders back to 0
	if (direction == 0) // right
	{
		while (turning == 1)
		{
			rightReading = motorRight.read(); // reading the current value
			leftReading = motorLeft.read();
			//Serial.print(leftReading);
			//Serial.print("  :  ");
			//Serial.println(rightReading);
			if (leftReading > -600)
			{
				digitalWrite(in1, HIGH); // turn on
				digitalWrite(in2, LOW);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (rightReading < 600)
			{
				digitalWrite(in3, LOW); // turn on
				digitalWrite(in4, HIGH);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if ((leftReading > 599) && (rightReading < -599))
			{
				turning = 0;
				Serial.println("Finished turning");
				return;
			}
			delay(1);
		}
	}
	else if (direction == 1) // left
	{

		while (turning == 1)
		{
			rightReading, leftReading = readMotors(); // reading the current value
			//Serial.println(rightReading);
			if (leftReading < 300)
			{
				digitalWrite(in1, LOW); // turn on
				digitalWrite(in2, HIGH);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (rightReading < 300)
			{
				digitalWrite(in3, HIGH); // turn on
				digitalWrite(in4, LOW);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if (leftReading && rightReading > 299)
			{
				turning = 0;
				Serial.println("Finished turning");
				return;
			}
			delay(1);
		}
	}
	else if (direction == 2) // 180
	{
		while (turning == 1)
		{
			rightReading, leftReading = readMotors(); // reading the current value
			Serial.println(rightReading);
			if (leftReading < 600)
			{
				digitalWrite(in1, LOW); // turn on
				digitalWrite(in2, HIGH);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (rightReading < 600)
			{
				digitalWrite(in3, HIGH); // turn on
				digitalWrite(in4, LOW);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if (leftReading && rightReading > 299)
			{
				turning = 0;
				Serial.println("Finished turning");
				return;
			}
			delay(1);
		}
	}
	Serial.println("Finished Turning");
}

void Motors::move(int direction) // preprogrammed durations to turn, obsolete
{
	analogWrite(enA, motorSpeed);
	analogWrite(enB, motorSpeed);
	switch (direction)
	{
	case 1: // forwards for 1 second
		digitalWrite(in1, HIGH); // turn on
		digitalWrite(in2, LOW);
		digitalWrite(in3, HIGH); // turn on
		digitalWrite(in4, LOW);
		delay(1000);
		break;
	case 2: // backwards
		digitalWrite(in1, LOW); // turn on 
		digitalWrite(in2, HIGH);
		digitalWrite(in3, LOW); // turn on
		digitalWrite(in4, HIGH);
		delay(1000);
		break;
	case 3: //turn right
		digitalWrite(in1, LOW); // turn on 
		digitalWrite(in2, HIGH);
		digitalWrite(in3, HIGH); // turn on
		digitalWrite(in4, LOW);
		delay(600);
		break;
	case 4: // turn left
		digitalWrite(in1, HIGH); // turn on 
		digitalWrite(in2, LOW);
		digitalWrite(in3, LOW); // turn on
		digitalWrite(in4, HIGH);
		delay(600);
		break;
	}
}

void Motors::updateEEPROM(int motorSpeed, int motorStatus, int currentDirection)
{
	EEPROM.write(MOTOR_SPEED, motorSpeed);
	EEPROM.write(MOTOR_STATUS, motorStatus);
	EEPROM.write(MOTOR_DIRECTION, currentDirection);
}

long Motors::readMotors()
{
	long rightReading, leftReading;
	rightReading = motorRight.read();
	leftReading = motorLeft.read();
	return rightReading, leftReading;
}

void Motors::resetMotors()
{
	motorRight.write(0);
	motorLeft.write(0);
	Serial.println("Reset the motors");
}

void Motors::getStatus()
{
	Serial.print("Direction ");
	if (currentDirection == 1)
		Serial.println("forwards");
	else
		Serial.println("backwards");
	Serial.print("Status ");
	if (motorStatus == 1)
		Serial.println("off");
	else
		Serial.println("on");
	Serial.print("Speed");
	Serial.println(motorSpeed);
}

void writeEEPROM(int location, int data)
{
	EEPROM.write(location, data);
}

void readEEPROM(int data)
{
	int currentDirection = EEPROM.read(data);
}

void clearEEPROM()
{
	for (int i = 0; i < EEPROM.length(); i++)
	{
		EEPROM.write(i, 0);
	}
	Serial.println("Cleared EEPROM");
}
