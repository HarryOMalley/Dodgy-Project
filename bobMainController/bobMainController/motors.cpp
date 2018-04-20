#include "motors.h"

IO::IO()
{

}

int IO::getInput()
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

int IO::getSpeed()
{
	int newSpeed;
	newSpeed = (pulseIn(pwm3, HIGH)) / 10;
	return newSpeed;
}

void IO::updateEEPROM(int motorSpeed, int motorStatus, int currentDirection)
{
	EEPROM.write(MOTOR_SPEED, motorSpeed);
	EEPROM.write(MOTOR_STATUS, motorStatus);
	EEPROM.write(MOTOR_DIRECTION, currentDirection);
}


Motors::Motors()
{
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	setup();
	//motorEncoders encoder(); // work out how to fix the encoder problem before attempting this
	//noInterrupts();
	IO io;
}

Motors::~Motors()
{
}

void Motors::run(int program)
{
	switch (program)
	{
	case 1: // off
		motorOff();
		break;
	case 2: // on
		motorOn();
		break;
	case 3: // change direction
		motorReverse();
		break;
	case 4:
		setDirection(0); // forwards
		break;
	case 5:
		setDirection(1); // backwards
		break;
	case 6:
		setSpeed();
		break;
	case 7:
		getStatus(); // get current speed etc.
		break;
	case 8:
		turn(1);
		break;
	case 9:
		break;
	case 10:
		break;
	default: // run the motors
		run();
		break;
	}
	return;
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

void Motors::setSpeed()
{
	motorSpeed = io.getSpeed();
	updateEEPROM(motorSpeed, motorStatus, currentDirection);
	Serial.println("Changed motor speed");
	Serial.println(motorSpeed);
}

//void Motors::setSpeed()
//{
//	Serial.println("Input Speed: ");
//	while (true)
//	{
//		if (Serial.available())
//		{
//			motorSpeed = Serial.parseInt();
//			break;
//		}
//	}
//	updateEEPROM(motorSpeed, motorStatus, currentDirection);
//	Serial.println("Changed motor speed");
//}

void Motors::rotate()
{
	int rotation;
	Serial.println("Input angle: ");
	while (true)
	{
		if (Serial.available())
		{
			rotation = Serial.parseInt();
			break;
		}
	}
	// INSERT CODE TO ROTATE A SPECIFIC AMOUNT USING ENCODERS
	Serial.println("Changed motor speed");
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


void Motors::turn(int direction)
{
	long rightReading, leftReading;
	int turning = 1;
	analogWrite(enA, 200);	// Temporarily change the speed
	analogWrite(enB, 200); 
	encoder.resetMotors(); // reset the encoders back to 0
	if (direction == 0)
	{
		while (turning == 1) 
		{
			rightReading, leftReading = encoder.readMotors(); // reading the current value
			if (leftReading < 300)
			{
				digitalWrite(in1, HIGH); // turn on
				digitalWrite(in2, LOW);
			}
			else
			{
				digitalWrite(in1, LOW); // turn off
				digitalWrite(in2, LOW);
			}
			if (rightReading < 300)
			{
				digitalWrite(in3, LOW); // turn on
				digitalWrite(in4, HIGH);
			}
			else
			{
				digitalWrite(in3, LOW); // turn off
				digitalWrite(in4, LOW);
			}
			if (leftReading && rightReading > 299)
			{
				turning = 0;
				break;
			}
			delay(1);
		}
	}
	else if (direction == 1)
	{
	
		while (turning == 1)
		{
			rightReading, leftReading = encoder.readMotors(); // reading the current value
			Serial.println(rightReading);
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
				break;
			}
			delay(1);
		}
	}
	else if (direction == 2) // 180
	{
		while (turning == 1)
		{
			rightReading, leftReading = encoder.readMotors(); // reading the current value
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
				break;
			}
			delay(1);
		}
	}
	Serial.println("Finished Turning");
}

void Motors::move(int direction)
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
		delay(1000);
		break;
	case 4: // turn left
		digitalWrite(in1, HIGH); // turn on 
		digitalWrite(in2, LOW);
		digitalWrite(in3, LOW); // turn on
		digitalWrite(in4, HIGH);
		delay(1000);
		break;
	}
}

void Motors::updateEEPROM(int motorSpeed, int motorStatus, int currentDirection)
{
	EEPROM.write(MOTOR_SPEED, motorSpeed);
	EEPROM.write(MOTOR_STATUS, motorStatus);
	EEPROM.write(MOTOR_DIRECTION, currentDirection);
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
