//
//
//
#include "control.h"

control::control()/*:  tri_track(2, 3, 4, 5, 6, 7)*/ {
  //Serial.println("control constr");  
  }
/*	motor1.attach(8); // Attaches a pin to a servo.
	motor2.attach(9);*/

void control::run()
{
  Serial.print(busy); // 1 or 0
  Serial.print("  ");
  Serial.println("manualprogram");

  if ((manualProgram == 0) && (busy)) {
    int newProgram = pulseIn(status, HIGH);
    int rotatcontroln = 1;//pulseIn(pwm2, High);
    int check = digitalRead(pwm3);
    //  Serial.println(newProgram);
    if (check != 0) {
      Serial.println("run from mqtt");
      if (newProgram > 500 && newProgram < 1500){ // compact
        tri_track.servoRun(1);
      } else if (newProgram > 1500 && newProgram < 2500) // stab
        tri_track.servoRun(2);
      else if (newProgram > 2500 && newProgram < 3500) // flick
        tri_track.servoRun(3);
      else if (newProgram > 3500 && newProgram < 4500) //
        tri_track.servoRun(4);
      else if (newProgram > 4500 && newProgram < 5500) //
        tri_track.servoRun(5);
      if (rotatcontroln == 0) {
        tri_track.servoRun(6, 0);
      } else if (rotatcontroln == 1) {
        tri_track.servoRun(6, 1);
      }
    }
  } else if (manualProgram != 0){
    if (manualProgram == 1) // compact
      tri_track.servoRun(1);
    if (manualProgram == 2) // stab
      tri_track.servoRun(2);
    if (manualProgram == 3) // flick
      tri_track.servoRun(3);
    manualProgram = 0;
  }
}
/*else if (newProgram > 6500 && newProgram < 7500)
	// gpcontrol send to pi program
  else if (newProgram > 7500 && newProgram < 8500)
	program = 8;
  else if (newProgram > 8500 && newProgram < 9500)
	program = 9;
  else
	return 0;*/

/*
int control::getSpeed()
{
  /*int newSpeed;
    newSpeed = (pulseIn(pwm3, HIGH)) / 10;
    return newSpeed;
}*/

// locatcontroln: where in eeprom
// save: what to save
/*void control::updateEEPROM(int locatcontroln, int save) {
  EEPROM.write(motorSpeed, save);
}*/
