/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/

#include <EEPROM.h>
#define MOTOR_DIRECTION 0
#define MOTOR_STATUS 1
#define MOTOR_SPEED 2
int addr = 0; // Current address in the EEPROM
			  // connect motor controller pins to Arduino digital pins

// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
char inString[20], inChar, exitString[] = "exit";
int currentDirection, motorStatus, motorSpeed;
void setup()
{
	// set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	Serial.begin(9600);
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

void loop()
{
	int program;
	while (Serial.available() > 0)
	{
		program = Serial.parseInt();
		motor(program);
	}
	while (Serial.available() == 0)
	{
		motorRun();
	}
}

void motor(int program)
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
		writeEEPROM(MOTOR_DIRECTION, 1);
		break;
	case 9:
		clearEEPROM();
	default: // run the motors
		motorRun();
		break;
	}
	program = 10; // change program to default to not run things twice
	Serial.flush();
}

void motorReverse()
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

void setDirectionForwards()
{
	currentDirection = 1;
	updateEEPROM();
}

void setDirectionBackwards()
{
	currentDirection = 2;
	updateEEPROM();
}

void getStatus()
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

void motorOn()
{
	motorStatus = 2;
	updateEEPROM();
	Serial.println("Turned motor on");
	return;
}

void motorOff()
{
	motorStatus = 1;
	updateEEPROM();
	Serial.println("Turned motor off");
	return;
}

void motorRun()
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
			digitalWrite(in3, HIGH); // turn on
			digitalWrite(in4, LOW);
			break;
		default:
			// do nothing
			break;
		}
		delay(1);
		return;
	}
}

void setSpeed()
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

void rotate()
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

void writeEEPROM(int location, int data)
{
	EEPROM.write(location, data);
}

void readEEPROM(int data)
{
	currentDirection = EEPROM.read(data);
}

void clearEEPROM()
{
	for (int i = 0; i < EEPROM.length(); i++)
	{
		EEPROM.write(i, 0);
	}
	Serial.println("Cleared EEPROM");
}

void updateEEPROM()
{
	EEPROM.write(MOTOR_SPEED, motorSpeed);
	EEPROM.write(MOTOR_STATUS, motorStatus);
	EEPROM.write(MOTOR_DIRECTION, currentDirection);
}
