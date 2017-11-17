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
Servo servo; // temp servo controll for switching between servos

int pin = 2;
int temp[10] = {};
float pos = 0;    // variable to store the servo position

void setup() {
	myservo.attach(2);		// attaches the servo owhat voltn pin 9 to the servo object
	myservo2.attach(3);
	myservo3.attach(4);
	myservo4.attach(5);
	myservo5.attach(6);
	myservo6.attach(7);
	temp[0] = myservo.read();
	temp[1] = myservo2.read();
	temp[2] = myservo3.read();
	temp[3] = myservo4.read();
	temp[4] = myservo5.read();
	temp[5] = myservo6.read();
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

				if (Xbox.getButtonClick(L1, i)) {
					int temp_ = servo.read();
					servo.detach();
					switch (pin) {
					case 2:
						myservo.attach(2);
						myservo.write(temp[0]);
						break;
					case 3:
						myservo2.attach(3);
						myservo2.write(temp[1]);
						break;
					case 4:
						myservo3.attach(4);
						myservo3.write(temp_);
						break;
					case 5:
						myservo4.attach(5);
						myservo4.write(temp_);
						break;
					case 6:
						myservo5.attach(6);
						myservo5.write(temp_);
						break;
					case 7:
						myservo6.attach(7);
						myservo6.write(temp_);
						break;
					default:
						break;
					}

					temp[0] = myservo.read();
					temp[1] = myservo2.read();
					temp[2] = myservo3.read();
					temp[3] = myservo4.read();
					temp[4] = myservo5.read();
					temp[5] = myservo6.read();
					if (pin > 2) {
						pin = pin - 1;
					}
					else {
						pin = 7;
					}

					Serial.print(F("L1: "));
					switch (pin) {
					case 2:
						myservo.detach();
						servo.attach(pin);
						servo.write(temp[0]);
						break;
					case 3:
						myservo2.detach();
						servo.attach(pin);
						servo.write(temp[1]);
						break;
					case 4:
						myservo3.detach();
						servo.attach(pin);
						servo.write(temp[2]);
						break;
					case 5:
						myservo4.detach();
						servo.attach(pin);
						servo.write(temp[3]);
						break;
					case 6:
						myservo5.detach();
						servo.attach(pin);
						servo.write(temp[4]);
						break;
					case 7:
						myservo6.detach();
						servo.attach(pin);
						servo.write(temp[5]);
						break;
					default:
						break;
					}
				}

				if (Xbox.getButtonClick(R1, i)) {
					int temp_ = servo.read();
					servo.detach();
					switch (pin) {
					case 2:
						myservo.attach(2);
						myservo.write(temp[0]);
						break;
					case 3:
						myservo2.attach(3);
						myservo2.write(temp[1]);
						break;
					case 4:
						myservo3.attach(4);
						myservo3.write(temp_);
						break;
					case 5:
						myservo4.attach(5);
						myservo4.write(temp_);
						break;
					case 6:
						myservo5.attach(6);
						myservo5.write(temp_);
						break;
					case 7:
						myservo6.attach(7);
						myservo6.write(temp_);
						break;
					default:
						break;
					}

					temp[0] = myservo.read();
					temp[1] = myservo2.read();
					temp[2] = myservo3.read();
					temp[3] = myservo4.read();
					temp[4] = myservo5.read();
					temp[5] = myservo6.read();
					if (pin < 7) {
						pin = pin + 1;
					}
					else {
						pin = 2;
					}
					Serial.println(F("R1"));
					switch (pin) {
					case 2:
						myservo.detach();
						servo.attach(pin);
						servo.write(temp[0]);
						break;
					case 3:
						myservo2.detach();
						servo.attach(pin);
						servo.write(temp[1]);
						break;
					case 4:
						myservo3.detach();
						servo.attach(pin);
						servo.write(temp[2]);
						break;
					case 5:
						myservo4.detach();
						servo.attach(pin);
						servo.write(temp[3]);
						break;
					case 6:
						myservo5.detach();
						servo.attach(pin);
						servo.write(temp[4]);
						break;
					case 7:
						myservo6.detach();
						servo.attach(pin);
						servo.write(temp[5]);
						break;
					default:
						break;
					}
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

				if (Xbox.getButtonClick(A, i)) {
					servo.write(servo.read() - 5);
					Serial.println(F("A"));
				}
				if (Xbox.getButtonClick(B, i))
					servo.write(servo.read() + 5);
				Serial.println(F("B"));
				if (Xbox.getButtonClick(X, i))
					Serial.println(F("X"));
				if (Xbox.getButtonClick(Y, i))
					Serial.println(F("Y"));
			}
		}
	}
}