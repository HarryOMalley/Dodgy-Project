#include <Servo.h>
#include <stdio.h>

#define wallpin 3
#define floorpin 2

int gap_found = 0;
// motor control defaults
#define neutral 90
#define LRboard 20
#define FBboard 20

Servo motor1;
Servo motor2;

// arm servos
Servo myservo;
Servo myservo2;
Servo myservo3;    // twelve servo objects can be created on most boards
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo servo; // temp servo controll for switching between servos

void setup() {
  motor1.attach(8); // Attaches a pin to a servo.
  motor2.attach(9);
  pinMode(floorpin,INPUT); // floor
  pinMode(wallpin,INPUT); // wall
  Serial.begin(9600); // starting serial communication
  attachInterrupt(digitalPinToInterrupt(floorpin),nofloor,RISING);
  attachInterrupt(digitalPinToInterrupt(wallpin),wallFound,RISING);
  drive(neutral,neutral);
}
  
void loop() {
}

void wallFound(){
    drive(neutral,neutral); // stop motors
    Serial.print("W"); // send the data g for gap
}

void nofloor(){
    // stop motors
    drive(neutral,neutral);
    Serial.print("F");   // send the data g for gap
}

void drive(float LeftRight, float FrontBack) {
  motor2.write(LeftRight); // Writes value to sabtertooth to drive motors
  motor1.write(FrontBack);
}

// begin rotation of knob
void stabMode(){
  // servoDetach();
  myservo.write(40);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(150);
  myservo5.write(150);
  myservo6.write(90);
  //  pin = 2;
  //  servoAttach();  
  // while not close to panel{
  //detachInterrupt();
  while(digitalRead(wallpin) == LOW){
    drive(neutral, neutral - FBboard);
  }
  // while not stable{
  // pi input for rotation direction
//  }
  flickSwitch();
}

// push switch down for stab panel
void flickSwitch(){
  myservo2.write(90);
  delay(300);
  myservo4.write(130); // lifts arm up out of the knob
  delay(500);
  myservo6.write(50); // rotates arm to the switch
  delay(200);
  myservo4.write(150); // flicks switch
  delay(100);
  myservo4.write(130); // raises arm
  delay(50);
  myservo6.write(90);
  delay(500);
  myservo4.write(150); // returns arm to original position
}

