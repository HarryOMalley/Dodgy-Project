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
	currentDirection = EEPROM.read(MOTOR_DIRECTION);
	motorStatus = EEPROM.read(MOTOR_STATUS);
	motorSpeed = EEPROM.read(MOTOR_SPEED);
	setup();
	motorEncoders encoders();
}

Motors::~Motors()
{
}

void Motors::setup()
{
	/*if ((currentDirection != 0) || (currentDirection != 1))
	{
		currentDirection = 1;
		EEPROM.write(MOTOR_DIRECTION, currentDirection);
		Serial.println("Changed Motor Direction");
	}
	if ((motorStatus != 0) || (motorStatus != 1))
	{
		motorStatus = 1;
		EEPROM.write(MOTOR_STATUS, motorStatus);
		Serial.println("Changed Motor Status");
	}*/
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
	motorSpeed = newSpeed;
	Serial.println("Changed motor speed");
	Serial.println(motorSpeed);
	updateEEPROM(motorSpeed, motorStatus, currentDirection);
}

void Motors::rotate(int direction)
{
	encoders.reset();
	analogWrite(enA, 120);
	analogWrite(enB, 120);
	float rotationRatio = 1.5; // NEED TO CALIBRATE
	int actualAngle, rotating = 1;
	readings readings; // struct of encoder readings that will be returned

	if (direction == 0) // right
	{
		while (rotating == 1)
		{
			readings = encoders.read();
			Serial.println(readings.right);
			Serial.println(readings.left);
			if (readings.left < 300) // work out what this should atually be
			{
				digitalWrite(in1, LOW); // turn on
				digitalWrite(in2, HIGH);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (readings.right > -300)
			{
				digitalWrite(in3, HIGH); // turn on
				digitalWrite(in4, LOW);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if ((readings.left > 300) && (readings.right < -300))
			{
				rotating = 0;
				Serial.println("Finished turning");
				return;
			}
			delay(10);
		}
	}
	else if (direction == 1) // left
	{
		while (rotating == 1)
		{
			readings = encoders.read();
			if (readings.left > -300)
			{
				digitalWrite(in1, HIGH); // turn on
				digitalWrite(in2, LOW);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (readings.right < 300)
			{
				digitalWrite(in3, LOW); // turn on
				digitalWrite(in4, HIGH);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if ((readings.left < -300) && (readings.right > 300))
			{
				rotating = 0;
				Serial.println("Finished turning");
				return;
			}
		}
	}
	Serial.println("rotated");
}

void Motors::rotate()
{
	encoders.reset();
	int angle = getRotation();
	int direction;
	float rotationRatio = 1.5; // NEED TO CALIBRATE
	int rightReading, leftReading, actualAngle, rotating = 1;
	// TEMPORARY FOR TESTING WITHOUT A PI
	Serial.println("Input angle: ");
	while (true)
	{
		if (Serial.available())
		{
			angle = Serial.parseInt();
			break;
		}
	}

	if (angle > 180)
	{
		angle -= 180; //converting to turn left instead
		direction = 1; // left
	}
	else
	{
		direction = 0; // right
	}

	actualAngle = angle * rotationRatio; // calculating the number of encoder pulses to turn

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
	Serial.println("rotated");
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

void Motors::updateEEPROM(int motorSpeed, int motorStatus, int currentDirection)
{
	EEPROM.write(MOTOR_SPEED, motorSpeed);
	EEPROM.write(MOTOR_STATUS, motorStatus);
	EEPROM.write(MOTOR_DIRECTION, currentDirection);
	Serial.println("Updated EEPROM");
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

//void Motors::calibrate(void)
//{
//	encoders.reset();
//	bool calibrating = true;
//	float currentTime, newTime, timeDelta, rightReading, leftReading, newRightReading, newLeftReading, rpmRight, rpmLeft;
//	analogWrite(enA, motorSpeedRight());
//	analogWrite(enB, motorSpeedLeft());
//	digitalWrite(in1, HIGH); // turn on
//	digitalWrite(in2, LOW);
//	digitalWrite(in3, HIGH); // turn on
//	digitalWrite(in4, LOW);
//	int count = 0;
//
//	while (calibrating == true)
//	{
//		int rightSpeed = motorSpeedRight();
//		int leftSpeed = motorSpeedLeft();
//		analogWrite(enA, rightSpeed);
//		analogWrite(enB, leftSpeed);
//		rightReading = motorRight.read();
//		leftReading = motorLeft.read();
//		currentTime = millis();
//		delay(10);
//		newRightReading = motorRight.read();
//		newLeftReading = motorLeft.read();
//		newTime = millis();
//		timeDelta = newTime - currentTime;
//		rpmRight = ((newRightReading - rightReading) / timeDelta) * 60000;
//		rpmLeft = ((newLeftReading - leftReading) / timeDelta) * 60000;
//		if (count > 20)
//		{
//			Serial.print("Speeds: ");
//			Serial.print(timeDelta);
//			Serial.print(" : ");
//			Serial.print(rpmRight);
//			Serial.print(" : ");
//			Serial.print(rpmLeft);
//			Serial.print(" : ");
//			Serial.print(rightSpeed);
//			Serial.print(" : ");
//			Serial.print(leftSpeed);
//			Serial.print(" : ");
//			Serial.println(rightMotorAnalogue);
//			count = 0;
//		}
//		if (rpmRight > (rpmLeft)) // adding a bit of allowance to not oscillate
//		{
//			if (leftMotorAnalogue < (252 - motorSpeed))
//			{
//				leftMotorAnalogue += 2;
//				if (rightMotorAnalogue > 0)
//					rightMotorAnalogue -= 2;
//			}
//			else
//			{
//				rightMotorAnalogue -= 2;
//			}
//
//		}
//		else if (rpmRight < (rpmLeft))
//		{
//			if (rightMotorAnalogue < (252 - motorSpeed))
//			{
//				rightMotorAnalogue += 2;
//				if (leftMotorAnalogue > 0)
//					leftMotorAnalogue -= 2;
//			}
//			else
//			{
//				leftMotorAnalogue -= 2;
//			}
//		}
//		count++;
//
//	}
//
//}

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

//void Motors::turn(int direction) // uncalibrated turning, right, left and 180 -- NOT USED
//{
//	long rightReading, leftReading;
//	int turning = 1;
//	analogWrite(enA, 80);	// temporarily change the speed
//	analogWrite(enB, 80);
//	resetMotors(); // reset the encoders back to 0
//	if (direction == 0) // right
//	{
//		while (turning == 1)
//		{
//			rightReading = motorRight.read(); // reading the current value
//			leftReading = motorLeft.read();
//			//Serial.print(leftReading);
//			//Serial.print("  :  ");
//			//Serial.println(rightReading);
//			if (leftReading > -600)
//			{
//				digitalWrite(in1, HIGH); // turn on
//				digitalWrite(in2, LOW);
//			}
//			else
//			{
//				digitalWrite(in1, LOW); // turn off
//				digitalWrite(in2, LOW);
//			}
//			if (rightReading < 600)
//			{
//				digitalWrite(in3, LOW); // turn on
//				digitalWrite(in4, HIGH);
//			}
//			else
//			{
//				digitalWrite(in3, LOW); // turn off
//				digitalWrite(in4, LOW);
//			}
//			if ((leftReading > 599) && (rightReading < -599))
//			{
//				turning = 0;
//				Serial.println("Finished turning");
//				return;
//			}
//			delay(1);
//		}
//	}
//	else if (direction == 1) // left
//	{
//
//		while (turning == 1)
//		{
//			rightReading, leftReading = readMotors(); // reading the current value
//			//Serial.println(rightReading);
//			if (leftReading < 300)
//			{
//				digitalWrite(in1, LOW); // turn on
//				digitalWrite(in2, HIGH);
//			}
//			else
//			{
//				digitalWrite(in1, LOW); // turn off
//				digitalWrite(in2, LOW);
//			}
//			if (rightReading < 300)
//			{
//				digitalWrite(in3, HIGH); // turn on
//				digitalWrite(in4, LOW);
//			}
//			else
//			{
//				digitalWrite(in3, LOW); // turn off
//				digitalWrite(in4, LOW);
//			}
//			if (leftReading && rightReading > 299)
//			{
//				turning = 0;
//				Serial.println("Finished turning");
//				return;
//			}
//			delay(1);
//		}
//	}
//	else if (direction == 2) // 180
//	{
//		while (turning == 1)
//		{
//			rightReading, leftReading = readMotors(); // reading the current value
//			Serial.println(rightReading);
//			if (leftReading < 600)
//			{
//				digitalWrite(in1, LOW); // turn on
//				digitalWrite(in2, HIGH);
//			}
//			else
//			{
//				digitalWrite(in1, LOW); // turn off
//				digitalWrite(in2, LOW);
//			}
//			if (rightReading < 600)
//			{
//				digitalWrite(in3, HIGH); // turn on
//				digitalWrite(in4, LOW);
//			}
//			else
//			{
//				digitalWrite(in3, LOW); // turn off
//				digitalWrite(in4, LOW);
//			}
//			if (leftReading && rightReading > 299)
//			{
//				turning = 0;
//				Serial.println("Finished turning");
//				return;
//			}
//			delay(1);
//		}
//	}
//	Serial.println("Finished Turning");
//}

//void Motors::move(int direction) // preprogrammed durations to turn, obsolete
//{
//	analogWrite(enA, motorSpeed);
//	analogWrite(enB, motorSpeed);
//	switch (direction)
//	{
//	case 1: // forwards for 1 second
//		digitalWrite(in1, HIGH); // turn on
//		digitalWrite(in2, LOW);
//		digitalWrite(in3, HIGH); // turn on
//		digitalWrite(in4, LOW);
//		delay(1000);
//		break;
//	case 2: // backwards
//		digitalWrite(in1, LOW); // turn on 
//		digitalWrite(in2, HIGH);
//		digitalWrite(in3, LOW); // turn on
//		digitalWrite(in4, HIGH);
//		delay(1000);
//		break;
//	case 3: //turn right
//		digitalWrite(in1, LOW); // turn on 
//		digitalWrite(in2, HIGH);
//		digitalWrite(in3, HIGH); // turn on
//		digitalWrite(in4, LOW);
//		delay(600);
//		break;
//	case 4: // turn left
//		digitalWrite(in1, HIGH); // turn on 
//		digitalWrite(in2, LOW);
//		digitalWrite(in3, LOW); // turn on
//		digitalWrite(in4, HIGH);
//		delay(600);
//		break;
//	}
//}