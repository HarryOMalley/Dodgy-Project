/*
 Name:		bobMainController.ino
 Created:	4/18/2018 1:53:27 PM
 Author:	harryomalley
*/

#include <XBOXRECV.h>
#include <Servo.h>
#include <EEPROM.h>
#include "Control.h"


USB Usb;
XBOXRECV Xbox(&Usb);
Encoder motorRight(enc1, enc2);
Encoder motorLeft(enc3, enc4);
Control control;

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(115200);
#if !defined(__MIPSEL__)
	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
	}
#endif
	if (Usb.Init() == -1) {
		Serial.print(F("\r\nOSC did not start"));
		while (1);
		{
			
		}//halt
	}
	Serial.print(F("\r\nXbox Wireless Receiver Library Started"));

	control.setup();
	Serial.println("/n Finished initialising");
	
}

void loop()
{
	//while(1)
	//{
	//	digitalWrite(LED_BUILTIN, HIGH);
	//	delay(10);
	//	digitalWrite(LED_BUILTIN, LOW);
	//}
	Serial.println("test");
	Usb.Task();
	control.run();
}
