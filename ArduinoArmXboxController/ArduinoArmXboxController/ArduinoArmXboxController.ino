/*
Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
It supports up to four controllers wirelessly
For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
send me an e-mail:  kristianl@tkjelectronics.com
*/

#include <XBOXRECV.h>
#include <Servo.h>
Servo leftServo;
Servo rightServo;
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

// Servos

Servo myservo;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;		// twelve servo objects can be created on most boards
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;

float pos = 0;    // variable to store the servo position

void setup() {
	myservo.attach(2);		// attaches the servo owhat voltn pin 9 to the servo object
	myservo2.attach(3);
	myservo3.attach(4);
	myservo4.attach(5);
	myservo5.attach(6);
	myservo6.attach(7);
	myservo7.attach(8);
	myservo8.attach(9);

	Serial.begin(115200);
#if !defined(__MIPSEL__)
	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
	if (Usb.Init() == -1) {
		Serial.print(F("\r\nOSC did not start"));
		while (1); //halt
	}
	Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}
void loop() {
	Usb.Task();
	if (Xbox.XboxReceiverConnected) {
		for (uint8_t i = 0; i < 4; i++) {
			if (Xbox.Xbox360Connected[i]) {
				float leftStickY = Xbox.getAnalogHat(LeftHatY);
				float leftStickX = Xbox.getAnalogHat(LeftHatX);
				float rightStickX = Xbox.getAnalogHat(RightHatX); // Right stick is currently unused
				float rightStickY = Xbox.getAnalogHat(RightHatY);

				float leftRight = ((leftStickX / 32768) * 180);	// Calculation to scale the measurements to go between 30 - 150
				float forwardBack = ((leftStickY / 32768) * 180); // Multiplying by -1 to reverse the direction of the motors

				//myservo.write(leftRight);
				//myservo2.write(forwardBack);
				//delay(100);


				if (Xbox.getButtonClick(UP, i)) {
					Xbox.setLedOn(LED1, i);
					Serial.println(F("Up"));
				}
				if (Xbox.getButtonClick(DOWN, i)) {
					Xbox.setLedOn(LED4, i);
					Serial.println(F("Down"));
				}
				if (Xbox.getButtonClick(LEFT, i)) {
					Xbox.setLedOn(LED3, i);
					Serial.println(F("Left"));
				}
				if (Xbox.getButtonClick(RIGHT, i)) {
					Xbox.setLedOn(LED2, i);
					Serial.println(F("Right"));
				}

				if (Xbox.getButtonClick(START, i)) {
					Xbox.setLedMode(ALTERNATING, i);
					Serial.println(F("Start"));
				}
				if (Xbox.getButtonClick(BACK, i)) {
					Xbox.setLedBlink(ALL, i);
					Serial.println(F("Back"));
				}
				if (Xbox.getButtonClick(L3, i))
					Serial.println(F("L3"));
				if (Xbox.getButtonClick(R3, i))
					Serial.println(F("R3"));

				if (Xbox.getButtonClick(L1, i))
				{
					Serial.print(F("L1: "));
					myservo2.write(180);
					delay(1000);
					Serial.println(myservo.read());
				}

				if (Xbox.getButtonClick(R1, i))
				{
					Serial.println(F("R1"));
					myservo2.write(0);
					delay(1000);
					Serial.println(myservo.read());
				}
					if (Xbox.getButtonClick(XBOX, i)) {
					Xbox.setLedMode(ROTATING, i);
					Serial.print(F("Xbox (Battery: "));
					Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
					Serial.println(F(")"));
				}
				if (Xbox.getButtonClick(SYNC, i)) {
					Serial.println(F("Sync"));
					Xbox.disconnect(i);
				}

				if (Xbox.getButtonClick(A, i))
					Serial.println(F("A"));
				if (Xbox.getButtonClick(B, i))
					Serial.println(F("B"));
				if (Xbox.getButtonClick(X, i))
					Serial.println(F("X"));
				if (Xbox.getButtonClick(Y, i))
					Serial.println(F("Y"));



			}
		}
	}
}