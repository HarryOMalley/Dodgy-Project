#include <EEPROM.h>
#include <Servo.h>

#define pin1 10
#define pin2 11
#define pwm1 7 // digital
#define pwm2 6
#define pwm3 5

bool SERVO_STATUS = false;

Servo right;
Servo left;// create servo object to control a servo
			   // twelve servo objects can be created on most boards

int angle = 0;    // variable to store the servo position

void setup()
{
	right.write(angle);
	left.write(180 - angle);
	Serial.begin(9600);
	right.attach(pin1);
	left.attach(pin2);// attaches the servo on pin 9 to the servo object
}

void loop()
{
	int program;
	program = getInput();
	if (Serial.available() > 0)
	{
		program = Serial.parseInt();
		Serial.println(program);
	}
	
	if (program != 0)
	{
		run(program);
	}
}

int run(int program)
{
	switch (program)
	{
	case 1: // set to off
		SERVO_STATUS = false; // ON
		break;
	case 2: // set to on
		SERVO_STATUS = true;
		break;
	case 3: // move to angle
		servoMove(getAngle());
		break;
	case 4: // attach servos
		servoAttach();
		break;
	case 5: // detach servos
		servoDetach();
		break;
	}
	return;
}

int getInput()
{
	int check, program;
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
		Serial.println(program);
		return program;
}

void servoMove(int newAngle)
{
	if (newAngle > 180 || newAngle < 0) // adding limits
		return;
	if (!SERVO_STATUS) //checking if servos should be off
	{
		Serial.println("Servo should be off");
		return;
	}
	if (newAngle > angle)
	{
		for (angle; angle <= newAngle; angle += 1) // goes from 0 degrees to 180 degrees
		{ 							  // in steps of 1 degree
			right.write(angle);
			left.write(180 - angle);// tell servo to go to position in variable 'pos'
			delay(100);                       // waits 15ms for the servo to reach the position
		}
		angle = newAngle;
	}
	else if (newAngle < angle)
	{
		for (angle; angle >= newAngle; angle -= 1) // goes from 0 degrees to 180 degrees
		{ 							  // in steps of 1 degree
			right.write(angle);
			left.write(180 - angle);// tell servo to go to position in variable 'pos'
			delay(100);                       // waits 15ms for the servo to reach the position
		}
		angle = newAngle;
	}
}

void servoUp(int newAngle)
{
	for (angle; angle <= newAngle; angle += 1) // goes from 0 degrees to 180 degrees
	{ 							  // in steps of 1 degree
		right.write(angle);
		left.write(180 - angle);// tell servo to go to position in variable 'pos'
		delay(50);                       // waits 15ms for the servo to reach the position
	}
}

void servoUp()
{
	int newAngle = getAngle();
	if (newAngle > angle)
	{
		for (angle; angle <= newAngle; angle += 1) // goes from 0 degrees to 180 degrees
		{ 							  // in steps of 1 degree
			right.write(angle);
			left.write(180 - angle);// tell servo to go to position in variable 'pos'
			delay(50);                       // waits 15ms for the servo to reach the position
		}
	}
}

void servoDown(int newAngle)
{
	for (angle; angle >= newAngle; angle -= 1) // goes from 0 degrees to 180 degrees
	{ 							  // in steps of 1 degree
		right.write(angle);
		left.write(180 - angle);// tell servo to go to position in variable 'pos'
		delay(50);                       // waits 15ms for the servo to reach the position
	}
}

void servoDown()
{
	int newAngle = getAngle();
	if (newAngle < angle)
	{
		for (angle; angle >= newAngle; angle -= 1) // goes from 0 degrees to 180 degrees
		{ 							  // in steps of 1 degree
			right.write(angle);
			left.write(180 - angle);// tell servo to go to position in variable 'pos'
			delay(50);                       // waits 15ms for the servo to reach the position
		}
	}
}

int getAngle()
{
	int newAngle;
	newAngle = (pulseIn(pwm3, HIGH)) / 10;
	newAngle -= 6; // fixing the error that is usually present
	//if (round(newAngle) > newAngle)
	//{
	//	newAngle = round(newAngle - 4);
	//}
	//else
	//	newAngle = round(newAngle);
	Serial.println(newAngle);
	return newAngle;
}

void servoDetach()
{
	right.detach();
	left.detach();
}

void servoAttach()
{
	right.attach(pin1);
	left.attach(pin2);
}

//void updateEEPROM(int motorSpeed, int motorStatus, int currentDirection)
//{
//	EEPROM.write(MOTOR_SPEED, motorSpeed);
//	EEPROM.write(SERVO_STATUS, motorStatus);
//	EEPROM.write(MOTOR_DIRECTION, currentDirection);
//}