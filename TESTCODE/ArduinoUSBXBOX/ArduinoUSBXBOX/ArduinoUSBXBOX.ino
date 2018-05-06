/*
Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
It supports up to four controllers wirelessly
For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
send me an e-mail:  kristianl@tkjelectronics.com
*/

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
long count = 0;
USB Usb;
XBOXRECV Xbox(&Usb);
float FB, LR;
// motor one
#define enA 10
#define in1 9
#define in2 8
// motor two
#define enB 5
#define in3 7
#define in4 6



void setup() {
	Serial.begin(9600);
#if !defined(__MIPSEL__)
	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
	if (Usb.Init() == -1) {
		Serial.print(F("\r\nOSC did not start"));
		while (1); //halt
	}
	Serial.print(F("\r\nXbox Wireless Receiver Library Started"));

	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	analogWrite(enA, 0);
	analogWrite(enB, 0);
	digitalWrite(in1, LOW); // turn off
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW); // turn off
	digitalWrite(in4, LOW);
}
void loop() {
	Usb.Task();
	if (Xbox.XboxReceiverConnected)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (Xbox.Xbox360Connected[i])
			{
				if (Xbox.getButtonPress(R2, i) > 10)
				{
					int speed = Xbox.getButtonPress(R2, i);
					digitalWrite(in1, HIGH); // turn on
					digitalWrite(in2, LOW);
					digitalWrite(in3, HIGH); // turn on
					digitalWrite(in4, LOW);
					analogWrite(enA, speed);
					analogWrite(enB, speed);
					delay(10);
				}
				else if (Xbox.getButtonPress(L2, i) > 10)
				{
					int speed = Xbox.getButtonPress(L2, i);
					digitalWrite(in1, LOW); // turn on
					digitalWrite(in2, HIGH);
					digitalWrite(in3, LOW); // turn on
					digitalWrite(in4, HIGH);
					analogWrite(enA, speed);
					analogWrite(enB, speed);
					delay(10);
				}
				else
				{
					digitalWrite(in1, LOW); // turn on
					digitalWrite(in2, LOW);
					digitalWrite(in3, LOW); // turn on
					digitalWrite(in4, LOW);
				}



				/*if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i))
				{
					Serial.print("L2: ");
					Serial.print(Xbox.getButtonPress(L2, i));
					Serial.print("\tR2: ");
					Serial.println(Xbox.getButtonPress(R2, i));
					Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
				}*/
				if ((Xbox.getAnalogHat(LeftHatX, i) > 8000 || Xbox.getAnalogHat(LeftHatX, i) < -8000))
				{
					LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
					//FB = Xbox.getAnalogHat(LeftHatY, i);
					float leftRight, forwardsBackwards;

					if (LR > 0) // right
					{

						leftRight = (LR / 32768) * 255; // scaling to 0 to 255, rather than 0 to -32768 for analogWrite
						digitalWrite(in1, LOW); // turn on
						digitalWrite(in2, HIGH);
						analogWrite(enA, leftRight);
						digitalWrite(in3, HIGH); // turn on
						digitalWrite(in4, LOW);
						analogWrite(enB, leftRight);
						delay(10);
					}
					else if (LR < 0) // right
					{

						leftRight = (-LR / 32768) * 255; // scaling to 0 to 255, rather than 0 to -32768 for analogWrite
						digitalWrite(in1, HIGH); // turn on
						digitalWrite(in2, LOW);
						analogWrite(enA, leftRight);
						digitalWrite(in3, LOW); // turn on
						digitalWrite(in4, HIGH);
						analogWrite(enB, leftRight);
						delay(10);

					}

						//if (leftRight < 128)
						//{
						//	digitalWrite(in1, HIGH); // turn on
						//	digitalWrite(in2, LOW);
						//	analogWrite(enA, 255 - 2*leftRight);
						//	digitalWrite(in3, HIGH); // turn on
						//	digitalWrite(in4, LOW);
						//	analogWrite(enB, leftRight);
						//}
						//else if (leftRight > 128)
						//{
						//	digitalWrite(in1, LOW); // turn on
						//	digitalWrite(in2, HIGH);
						//	analogWrite(enA, 2*leftRight - 255);
						//	digitalWrite(in3, HIGH); // turn on
						//	digitalWrite(in4, LOW);
						//	analogWrite(enB, leftRight);
						//}
			
				}
				//if (LR > 0) // forwards
				//{
				//	leftRight = (LR / 32768) * 255; // scaling to 0 to 255, rather than 0 to -32768 for analogWrite
				//	if (FB > 0)
				//	{
				//		forwardsBackwards = (FB / 32768) * 255;
				//		analogWrite(enA, leftRight);
				//		analogWrite(enB, forwardsBackwards);
				//		digitalWrite(in1, HIGH); // turn on
				//		digitalWrite(in2, LOW);
				//		digitalWrite(in3, HIGH); // turn on
				//		digitalWrite(in4, LOW);
				//		//Serial.println("updated speeds");
				//		delay(10);
						//if ((count % 20) == 0)
						//{

						//	Serial.print(F("lr: "));
						//	Serial.print(LR);
						//	Serial.print("\t");


						//	Serial.print(F("fb: "));
						//	Serial.print(FB);
						//	Serial.print("\t");	aq1QQA
						//	Serial.println(count);
						//	//Serial.println();
						//}

					//}
					//else if (FB < 0)
					//{
					//	forwardsBackwards = (FB / 32768) * 255;
					//	analogWrite(enA, leftRight);
					//	analogWrite(enB, forwardsBackwards);
					//	digitalWrite(in1, HIGH); // turn on
					//	digitalWrite(in2, LOW);
					//	digitalWrite(in3, HIGH); // turn on
					//	digitalWrite(in4, LOW);
					//	//Serial.println("updated speeds");
					//	delay(10);
					//	//if ((count % 20) == 0)
					//	//{

					//	//	Serial.print(F("lr: "));
					//	//	Serial.print(LR);
					//	//	Serial.print("\t");


					//	//	Serial.print(F("fb: "));
					//	//	Serial.print(FB);
					//	//	Serial.print("\t");	aq1QQA
					//	//	Serial.println(count);
					//	//	//Serial.println();
					//	//}

					//}
					//count++;
		//	}
		//}
		//else // backwards
		//{


			}
			else
			{
				//digitalWrite(in1, LOW); // turn off
				//digitalWrite(in2, LOW);
				//digitalWrite(in3, LOW); // turn off
				//digitalWrite(in4, LOW);
			}
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
				Serial.println(F("L1"));
			if (Xbox.getButtonClick(R1, i))
				Serial.println(F("R1"));
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
	else
	{
		//Serial.println("not connected to controller");
	}
}











///*
//Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
//It supports up to four controllers wirelessly
//For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
//send me an e-mail:  kristianl@tkjelectronics.com
//*/
//
//#include <XBOXRECV.h>
//#include <Servo.h>
//Servo leftServo;
//Servo rightServo;
//// Satisfy the IDE, which needs to see the include statment in the ino too.
//#ifdef dobogusinclude
//#include <spi4teensy3.h>
//#endif
//#include <SPI.h>
//
//USB Usb;
//XBOXRECV Xbox(&Usb);
//
//int count = 0;
//
//void setup() {
//	leftServo.attach(5);
//	rightServo.attach(6);
//
//	Serial.begin(115200);
//#if !defined(__MIPSEL__)
//	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
//#endif
//	if (Usb.Init() == -1) {
//		Serial.print(F("\r\nOSC did not start"));
//		while (1); //halt
//	}
//	Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
//}
//void loop()
//{
//	Usb.Task();
//	if (Xbox.XboxReceiverConnected) 
//	{
//		for (uint8_t i = 0; i < 4; i++) 
//		{
//			if (Xbox.Xbox360Connected[i])
//			{
//				if ((Xbox.getAnalogHat(LeftHatX, i) > 8000 || Xbox.getAnalogHat(LeftHatX, i) < -8000 || Xbox.getAnalogHat(LeftHatY, i) > 8000 || Xbox.getAnalogHat(LeftHatY, i) < -8000))
//				{
//					int LR = Xbox.getAnalogHat(LeftHatY, i); // Gets the values from the left analog stick and saves it to a variable.
//					int FB = Xbox.getAnalogHat(LeftHatX, i);
//					LR = LR * -1; // Converts the recieved value from controller to a value between 30 and 150 which is what the servos work off.
//					LR = LR / 32768;
//					LR = LR * 60;
//					LR = LR + 90;
//					/*Serial.print(F("LeftHatX: ")); // Used for debugging.
//					Serial.print(LR);
//					Serial.print("\t");*/
//					FB = FB * -1; // Same process, but for the forward backward movement.
//					FB = FB / 32768;
//					FB = FB * 60;
//					FB = FB + 90;
//					if (count % 20 == 0)
//					{
//						Serial.println(FB);
//						Serial.println(LR);
//					}
//					//drive(LR, FB);
//				}
//				else 
//				{
//					//drive(neutral, neutral); // dont turn the motors if nothing from analogue or deadzone
//				}
//				//          Serial.print(motor1.read());
//				//          Serial.print("  ");
//				//          Serial.println(motor2.read());
//				//if (Xbox.getButtonClick(X, i)) { // compact
//				//	io.manualProgram = 1;
//				//	io.run();
//				//}
//				//if (Xbox.getButtonClick(A, i)) { // stabmode
//				//	io.manualProgram = 2;
//				//	io.run();
//				//}
//				//if (Xbox.getButtonClick(B, i)) { // flick
//				//	io.manualProgram = 3;
//				//	io.run();
//				//}
//			}
//		}
//
//
//		//if (Xbox.XboxReceiverConnected) {
//		//	for (uint8_t i = 0; i < 4; i++) {
//		//		if (Xbox.Xbox360Connected[i]) {
//		//			float leftStickY = Xbox.getAnalogHat(LeftHatY);
//		//			float leftStickX = Xbox.getAnalogHat(LeftHatX);
//		//			float rightStickX = Xbox.getAnalogHat(RightHatX); // Right stick is currently unused
//		//			float rightStickY = Xbox.getAnalogHat(RightHatY);
//		//			
//		//			float leftRight = ((leftStickX*-1 / 32768) * 60) + 90;	// Calculation to scale the measurements to go between 30 - 150
//		//			float forwardBack = ((leftStickY*-1 / 32768) * 60) + 90; // Multiplying by -1 to reverse the direction of the motors
//
//		//			leftServo.write(forwardBack);
//		//			rightServo.write(leftRight);
//
//
//
//		//			if (Xbox.getButtonClick(UP, i)) {
//		//				Xbox.setLedOn(LED1, i);
//		//				Serial.println(F("Up"));
//		//			}
//		//			if (Xbox.getButtonClick(DOWN, i)) {
//		//				Xbox.setLedOn(LED4, i);
//		//				Serial.println(F("Down"));
//		//			}
//		//			if (Xbox.getButtonClick(LEFT, i)) {
//		//				Xbox.setLedOn(LED3, i);
//		//				Serial.println(F("Left"));
//		//			}
//		//			if (Xbox.getButtonClick(RIGHT, i)) {
//		//				Xbox.setLedOn(LED2, i);
//		//				Serial.println(F("Right"));
//		//			}
//
//		//			if (Xbox.getButtonClick(START, i)) {
//		//				Xbox.setLedMode(ALTERNATING, i);
//		//				Serial.println(F("Start"));
//		//			}
//		//			if (Xbox.getButtonClick(BACK, i)) {
//		//				Xbox.setLedBlink(ALL, i);
//		//				Serial.println(F("Back"));
//		//			}
//		//			if (Xbox.getButtonClick(L3, i))
//		//				Serial.println(F("L3"));
//		//			if (Xbox.getButtonClick(R3, i))
//		//				Serial.println(F("R3"));
//
//		//			if (Xbox.getButtonClick(L1, i))
//		//				Serial.println(F("L1"));
//		//			if (Xbox.getButtonClick(R1, i))
//		//				Serial.println(F("R1"));
//		//			if (Xbox.getButtonClick(XBOX, i)) {
//		//				Xbox.setLedMode(ROTATING, i);
//		//				Serial.print(F("Xbox (Battery: "));
//		//				Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
//		//				Serial.println(F(")"));
//		//			}
//		//			if (Xbox.getButtonClick(SYNC, i)) {
//		//				Serial.println(F("Sync"));
//		//				Xbox.disconnect(i);
//		//			}
//
//		//			if (Xbox.getButtonClick(A, i))
//		//				Serial.println(F("A"));
//		//			if (Xbox.getButtonClick(B, i))
//		//				Serial.println(F("B"));
//		//			if (Xbox.getButtonClick(X, i))
//		//				Serial.println(F("X"));
//		//			if (Xbox.getButtonClick(Y, i))
//		//				Serial.println(F("Y"));
//
//
//
//		//		}
//		//	}
//		//}
//	}
//}





//}
//if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) {
//	if ((count % 20) == 0)
//	{
//		if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500)
//		{
//			Serial.print(F("LeftHatX: "));
//			Serial.print(Xbox.getAnalogHat(LeftHatX, i));
//			Serial.print("\t");
//		}
//		if (Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500)
//		{
//			Serial.print(F("LeftHatY: "));
//			Serial.print(Xbox.getAnalogHat(LeftHatY, i));
//			Serial.print("\t");
//		}
//		Serial.println();
//	}
//	count++;
//	//if (Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500)
//	//{
//	//	Serial.print(F("RightHatX: "));
//	//	Serial.print(Xbox.getAnalogHat(RightHatX, i));
//	//	Serial.print("\t");
//	//}
//	//if (Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500)
//	//{
//	//	Serial.print(F("RightHatY: "));
//	//	Serial.print(Xbox.getAnalogHat(RightHatY, i));
//	//}
//	//Serial.println();
//}