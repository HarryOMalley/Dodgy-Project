/* Encoder Library - TwoKnobs Example
* http://www.pjrc.com/teensy/td_libs_Encoder.html
*
* This example code is in the public domain.
*/

#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(5, 6);
Encoder knobRight(7, 8);
//   avoid using pins with LEDs attached

void setup() {
	Serial.begin(9600);
	Serial.println("TwoKnobs Encoder Test:");
}

long positionLeft = -999;
long positionRight = -999;

void loop() {
	long newLeft, newRight;
	newLeft = knobLeft.read();
	newRight = knobRight.read();
	if (newLeft != positionLeft || newRight != positionRight) {
		Serial.print("Left = ");
		Serial.print(newLeft);
		Serial.print(", Right = ");
		Serial.print(newRight);
		Serial.println();
		positionLeft = newLeft;
		positionRight = newRight;
	}
	// if a character is sent from the serial monitor,
	// reset both back to zero.
	if (Serial.available()) {
		Serial.read();
		Serial.println("Reset both knobs to zero");
		knobLeft.write(0);
		knobRight.write(0);
	}
}

















//#define ClockPinRight 2 // Must be pin 2 or 3
//#define ClockPinLeft 3 // Must be pin 2 or 3
//#define DataPinRight 9 // can be any other pin
//#define DataPinLeft 10
//// can be any other pin
//// My Encoder has 400 Clock pulses per revolution
//// note that 150000.0 = (60 seonds * 1000000 microseconds)microseconds in a minute / 400 pulses in 1 revolution)
//// change the math to get the proper multiplier for RPM for your encoder
//#define Multiplier 400000.0 // don't forget a decimal place to make this number a floating point number 400000 for 150 pulses per rotation
//volatile long EncoderCounterRight = 0;
//volatile long EncoderCounterLeft = 0;
//volatile float SpeedInRPMRight = 0;
//volatile float SpeedInRPMLeft = 0;
//
//void onPin2CHANGECallBackFunction(uint32_t Time, uint32_t PinsChanged, uint32_t Pins) {
//	static uint32_t lTime; // Saved Last Time of Last Pulse
//	uint32_t cTime; // Current Time
//	cTime = micros(); // Store the time for RPM Calculations
//	int32_t dTime; // Delt in timec
//
//				   // Encoder Code
//	bool DataPinValRight = digitalRead(DataPinRight);
//	// We know pin 2 just went high to trigger the interrupt
//	// depending on direction the data pin will either be high or low
//	EncoderCounterRight += (DataPinValRight) ? 1 : -1; // Should we step up or down?
//	// End Encoder Code
//	// calculate the DeltaT between pulses
//	dTime = cTime - lTime;
//	lTime = cTime;
//	SpeedInRPMRight = Multiplier / ((DataPinValRight) ? dTime : (-1 * dTime)); // Calculate the RPM Switch DeltaT to either positive or negative to represent Forward or reverse RPM
//}
//void onPin3CHANGECallBackFunction(uint32_t Time, uint32_t PinsChanged, uint32_t Pins) {
//	static uint32_t lTime; // Saved Last Time of Last Pulse
//	uint32_t cTime; // Current Time
//	cTime = micros(); // Store the time for RPM Calculations
//	int32_t dTime; // Delt in timec
//
//				   // Encoder Code
//	bool DataPinValRight = digitalRead(DataPinRight);
//	bool DataPinValLeft = digitalRead(DataPinLeft);
//	// We know pin 2 just went high to trigger the interrupt
//	// depending on direction the data pin will either be high or low
//	EncoderCounterRight += (DataPinValRight) ? 1 : -1; // Should we step up or down?
//	EncoderCounterLeft += (DataPinValLeft) ? 1 : -1;
//	// End Encoder Code
//	// calculate the DeltaT between pulses
//	dTime = cTime - lTime;
//	lTime = cTime;
//	SpeedInRPMRight = Multiplier / ((DataPinValRight) ? dTime : (-1 * dTime)); // Calculate the RPM Switch DeltaT to either positive or negative to represent Forward or reverse RPM
//	SpeedInRPMLeft = Multiplier / ((DataPinValRight) ? dTime : (-1 * dTime)); // Calculate the RPM Switch DeltaT to either positive or negative to represent Forward or reverse RPM
//
//}
//void setup() {
//	Serial.begin(115200); //115200
//						  // put your setup code here, to run once:
//	pinMode(ClockPinRight, INPUT);
//	pinMode(ClockPinLeft, INPUT);
//	pinMode(DataPinRight, INPUT);
//	pinMode(DataPinLeft, INPUT);
//	attachInterrupt(0, onPin2CHANGECallBackFunction2, RISING);
//	attachInterrupt(1, onPin2CHANGECallBackFunction3, RISING);
//}
//
//void loop() {
//	long CounterRight, CounterLeft;
//	float SpeedRight, SpeedLeft;
//	noInterrupts();
//	// Because when the interrupt occurs the EncoderCounter and SpeedInRPM could be interrupted while they
//	// are being used we need to say hold for a split second while we copy these values down. This doesn't keep the
//	// interrupt from occurring it just slightly delays it while we maneuver values.
//	// if we don't do this we could be interrupted in the middle of copying a value and the result get a corrupted value.
//	CounterRight = EncoderCounterRight;
//	CounterLeft = EncoderCounterLeft;
//	SpeedRight = SpeedInRPMRight;
//	SpeedLeft = SpeedInRPMLeft;
//	interrupts();
//
//	// use the speed and counter values for whatever you need to do.
//}