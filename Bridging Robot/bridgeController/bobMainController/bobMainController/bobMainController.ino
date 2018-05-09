/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/

#include <Servo.h>
#include <EEPROM.h>
#include "Control.h"

Encoder motorRight(enc1, enc2);
Encoder motorLeft(enc3, enc4);
Control control;

void setup()
{
	Serial.begin(9600);
#if !defined(__MIPSEL__)
	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
	}
#endif
	Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
	Serial.println("/n Finished initialising");
	control.setup();	
}

void loop()
{
	control.run();
}
