/*
 Name:		bridgeController.ino
 Created:	4/18/2018 1:55:48 PM
 Author:	harryomalley
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <EEPROM.h>
#define MOTOR_DIRECTION 0
#define MOTOR_STATUS 1
#define MOTOR_SPEED 2
int addr = 0; // Current address in the EEPROM
			  // connect motor controller pins to Arduino digital pins
// motor one
int enA = 16;
int in1 = 5;
int in2 = 4;
char inString[20], inChar, exitString[] = "exit";
int currentDirection, motorStatus, motorSpeed;

// Wifi Settings
const char* ssid = "Dodgy Wifi";
const char* password = "";
const char* mqtt_server = "192.168.1.5";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup()
{
	Serial.begin(9600);
	Serial.println("Setting up");
	// set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
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
	motorSpeed = 255;
	currentDirection = 1;
	motorStatus = 1;
	pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
	setup_wifi();
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);

}

void loop()
{
	if (!client.connected()) 
	{
		reconnect();
	}
	client.loop();
	motorRun();
	//long now = millis();
	//if (now - lastMsg > 2000) {
	//	lastMsg = now;
	//	++value;
	//	snprintf(msg, 75, "hello world #%ld", value);
	//	Serial.print("Publish message: ");
	//	Serial.println(msg);
	//	client.publish("Bridge", msg);
	//}
}

	/*int program;
	while (Serial.available() > 0)
	{
		program = Serial.parseInt();
		motor(program);
	}
	while (Serial.available() == 0)
	{
		motorRun();
	}*/

void motor(int program)
{
	Serial.println(motorStatus);
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
		return;
	}
	else
	{
		analogWrite(enA, 255);
		switch (currentDirection)
		{
		case 1: // right
			digitalWrite(in1, HIGH); // turn on
			digitalWrite(in2, LOW);
			break;
		case 2: // left
			digitalWrite(in1, LOW); // turn on 
			digitalWrite(in2, HIGH);
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
			Serial.println(motorSpeed);
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

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Create a random client ID
		String clientId = "ESP8266Client-";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect
		if (client.connect(clientId.c_str())) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish("BridgeOut", "hello world");
			// ... and resubscribe
			client.subscribe("Bridge");
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();

	// Switch on the LED if an 1 was received as first character
	if ((char)payload[0] == '0') 
	{
		digitalWrite(BUILTIN_LED, HIGH);   // Turn the LED on (Note that LOW is the voltage level
		motor(0);							  // but actually the LED is on; this is because
										  // it is acive low on the ESP-01)
	}
	else if ((char)payload[0] == '1')
	{
		digitalWrite(BUILTIN_LED, LOW);  // Turn the LED off by making the voltage HIGH
		motor(1);
	}
}
void setup_wifi() {

	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	randomSeed(micros());

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

/*

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.










void setup() {

}

void loop() {



*/