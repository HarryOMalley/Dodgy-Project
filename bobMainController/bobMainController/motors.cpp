#include "motors.h"

Motors::Motors()
{
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	setup();
}

Motors::~Motors()
{
}

void Motors::run(int program)
{
	switch (program)
	{
	case 0: // off
		motorOff();
		break;
	case 1: // on
		motorOn();
		break;
	case 2: // change direction
		motorReverse();
		break;
	case 3:
		setDirectionForwards();
		break;
	case 4:
		setDirectionBackwards();
		break;
	case 5:
		setSpeed();
		break;
	case 6:
		getStatus();
		break;
	case 7:
		rotate();
		break;
	case 8:
		break;
	case 9:
		break;
	default: // run the motors
		run();
		break;
	}
	program = 10; // change program to default to not run things twice
	Serial.flush();
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
		updateEEPROM();
	}
	else if (currentDirection == 2) // left
	{
		currentDirection = 1;
		updateEEPROM();
	}
}

void Motors::setDirectionForwards()
{
	currentDirection = 1;
	updateEEPROM();
}

void Motors::setDirectionBackwards()
{
	currentDirection = 2;
	updateEEPROM();
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
	updateEEPROM();
	Serial.println("Turned motor on");
	return;
}

void Motors::motorOff()
{
	motorStatus = 1;
	updateEEPROM();
	Serial.println("Turned motor off");
	return;
}

void Motors::setSpeed()
{
	Serial.println("Input Speed: ");
	while (true)
	{
		if (Serial.available())
		{
			motorSpeed = Serial.parseInt();
			break;
		}
	}
	updateEEPROM();
	Serial.println("Changed motor speed");
}

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
}

void Motors::updateEEPROM()
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
