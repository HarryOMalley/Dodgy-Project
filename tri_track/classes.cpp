//
//
//

#include "classes.h"

IO::IO()/*:  tri_track(2, 3, 4, 5, 6, 7)*/ {
  //Serial.println("io constr");  
  }
/*	motor1.attach(8); // Attaches a pin to a servo.
	motor2.attach(9);*/

void IO::run()
{
  int newProgram = pulseIn(status, HIGH);
  int rotation = 1;//pulseIn(pwm2, High);
  int check = digitalRead(pwm3);
  Serial.println(check);
//  Serial.println(newProgram);
  
  if (check != 0) {
    if (newProgram > 500 && newProgram < 1500){ // compact
      tri_track.servoRun(3);
    } else if (newProgram > 1500 && newProgram < 2500) // stab
      tri_track.servoRun(2);
    else if (newProgram > 2500 && newProgram < 3500) // flick
      tri_track.servoRun(3);
    else if (newProgram > 3500 && newProgram < 4500) //
      tri_track.servoRun(4);
    else if (newProgram > 4500 && newProgram < 5500) //
      tri_track.servoRun(5);
    if (rotation == 0) {
      tri_track.servoRun(6, 0);
    } else if (rotation == 1) {
      tri_track.servoRun(6, 1);
    }
  }
}
/*else if (newProgram > 6500 && newProgram < 7500)
	// gpio send to pi program
  else if (newProgram > 7500 && newProgram < 8500)
	program = 8;
  else if (newProgram > 8500 && newProgram < 9500)
	program = 9;
  else
	return 0;*/

/*
int IO::getSpeed()
{
  /*int newSpeed;
    newSpeed = (pulseIn(pwm3, HIGH)) / 10;
    return newSpeed;
}*/

// location: where in eeprom
// save: what to save
/*void IO::updateEEPROM(int location, int save) {
  EEPROM.write(motorSpeed, save);
}*/
