// 
// 
// 

#include "arm.h"

//arm::arm(int p1, int p2, int p3, int p4, int p5, int p6) {
arm::arm(){  /*
  s1 = p1;
  s2 = p2;
  s3 = p3;
  s4 = p4;
  s5 = p5;
  s6 = p6; 
  Serial.println("arm constr");*/
 // servoAttach();
}

int arm::servoRun(int program, int rotation) {
	if ((program == 6) && ((rotation == 0) || (rotation == 1))) {
		rotate(rotation);
		saveState(4);
	}
}

int arm::servoRun(int program) {
	if (program == 0) {
		return 0;
	}
	if (program == 1) {
    compactMode();
		saveState(program);
	}
	else if (program == 2) {
    stabMode();
  	saveState(program);
	}
	else if (program == 3) {
		flickSwitch();
		saveState(program);
	}
	else if (program == 4) {
		servoAttach();
		saveState(program);
	}
	else if (program == 5) {
    servoDetatch();
		saveState(program);
	} 
}

void arm::servoAttach() {
//  Serial.println("attach");
	delay(100);
	servo1.attach(s1);    // attaches the servo what voltn pin 9 to the servo object
	servo2.attach(s2);
	servo3.attach(s3);
	servo4.attach(s4);
	servo5.attach(s5);
	servo6.attach(s6);
}

void arm::servoDetatch() {
	delay(1000);
	servo1.detach();    // attaches the servo what voltn pin 9 to the servo object
	servo2.detach();
	servo3.detach();
	servo4.detach();
	servo5.detach();
	servo6.detach();
}

// three stages
// go back stop then slowly rest on the box and disable servos
void arm::compactMode() {
//  Serial.println("compact");
  servoAttach();
	servo1.write(90);
	servo2.write(180);
	servo3.write(30);
	delay(1500);
	servo4.write(40);
	for (int i = 0; i < 30; i++) {
		servo3.write(30 - i);
		delay(15);
	}
	servo3.write(0);
	servo4.write(20);
	servo5.write(90);
	servo6.write(90);
	servoDetatch();
}

// prepare servos for stabilisation
void arm::stabMode() {
  servoAttach();
	servo1.write(90);
	servo2.write(105);
	servo3.write(140);
	servo4.write(45);
	servo5.write(90);
	servo6.write(90);
	delay(100);
}

void arm::flickSwitch() {
  servoAttach();
  stabMode(); // shouldnt need this but maybe?
  delay(1000);
	servo3.write(90); // lifts arm up out of the knob
	delay(300);
	servo1.write(60);
	delay(500);
	servo2.write(70);// flick switch
	delay(200);
	servo2.write(80);
	delay(50);
	servo1.write(90); // return
	compactMode(); // prepare travelling mode
}

void arm::rotate(int rotation) {
  servoAttach();
	if (rotation == 0) { // cw
		servo6.write(90);
		servo5.write(5);
		delay(1000);
		servo6.write(70);
		delay(1000);
		servo5.write(90);
		delay(1000);
		servo6.write(5);
		delay(1000);
	}
	else if (rotation == 1) { // ccw
		servo6.write(90);
		servo5.write(90);
		delay(500);
		servo6.write(70);
		delay(1000);
		servo5.write(90);
		delay(500);
		servo6.write(90);
		delay(200);
	}
}

void arm::saveState(int program) {
	EEPROM.write(armState, program);
}
