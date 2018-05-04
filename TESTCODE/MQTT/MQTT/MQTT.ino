#include <Encoder.h>
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
Encoder encoder(2, 3);
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
	if ((currentDirection != 1) && currentDirection != 2)
	{
		currentDirection = 1;
		EEPROM.write(MOTOR_DIRECTION, currentDirection);
		Serial.println("Changed Motor Direction");
	}
	if ((motorStatus != 1) && (motorStatus != 2))
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
long position;
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
		long newposition = encoder.read();
		if ((newposition - position > 100))
		{
			position = newposition;
			Serial.println(position);
		}
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
		setDirectionRight();
		break;
	case 4:
		setDirectionLeft();
		break;
	case 5:
		setSpeed();
		break;
	case 6:
		getStatus();
		break;
	case 7:
		readEEPROM(MOTOR_DIRECTION);
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

void setDirectionRight()
{
	currentDirection = 1;
	updateEEPROM();
}

void setDirectionLeft()
{
	currentDirection = 2;
	updateEEPROM();
}

void getStatus()
{
	Serial.print("Direction ");
	if (currentDirection == 1)
		Serial.println("right");
	else
		Serial.println("left");
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
	Serial.print("Current direction is: ");
	Serial.println(currentDirection);
	//if (currentDirection == 1) // right
	//{
	//	digitalWrite(in1, HIGH); // turn on
	//	digitalWrite(in2, LOW);
	//}
	//else if (currentDirection == 2) // left
	//{
	//	digitalWrite(in1, LOW); // turn on 
	//	digitalWrite(in2, HIGH);
	//}
	//delayMicroseconds(1);
	motorStatus = 2;
	updateEEPROM();
	Serial.println("Turned motor on");
	return;
}

void motorOff()
{
	//digitalWrite(in1, LOW); // turn off
	//digitalWrite(in2, LOW);
	//delayMicroseconds(1);
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
		case 1: // right
			digitalWrite(in1, HIGH); // turn on
			digitalWrite(in2, LOW);
			digitalWrite(in3, LOW); // turn on
			digitalWrite(in4, HIGH);
			break;
		case 2: // left
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
	int wait = 0;
	Serial.println("Input Speed: ");
	while (wait == 0)
	{
		if (Serial.available())
		{
			motorSpeed = Serial.parseInt();
			Serial.println(motorSpeed);
			wait = 1;
			break;
		}
	}
	updateEEPROM();
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