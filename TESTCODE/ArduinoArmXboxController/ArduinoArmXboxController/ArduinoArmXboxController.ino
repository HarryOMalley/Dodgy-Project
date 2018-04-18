#include <XBOXRECV.h>
#include <Servo.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

// pins used for ultrasonic sensors
#define trigPin 51
#define echoPin 53

#define neutral 90
#define LRboard 20
#define FBboard 20

// Defines all the servos and usb devices.
USB Usb;
XBOXRECV Xbox(&Usb);

Servo motor1;
Servo motor2;

//Servos
Servo myservo;
Servo myservo2;
Servo myservo3;    // twelve servo objects can be created on most boards
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo servo; // temp servo controll for switching between servos

// global variables
bool withinRange = false; // is the tritrack the correct distance from the stabilisation board
int movement = 10; // default angle of rotation
int timeDelay = 50; // default time of rotation per degree
int pin = 2; // initial servo to control
int temp[10] = {}; // stores values of servo angles when not being controlled

// Defines FB and LR as float values for sending to the sabertooth.
float FB;
float LR;

void setup() {
  Serial.begin(9600);

  motor1.attach(8); // Attaches a pin to a servo.
  motor2.attach(9);

  servo.attach(2);    // attaches the servo owhat voltn pin 9 to the servo object
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(6);
  myservo6.attach(7);
  temp[0] = servo.read();
  temp[1] = myservo2.read();
  temp[2] = myservo3.read();
  temp[3] = myservo4.read();
  temp[4] = myservo5.read();
  temp[5] = myservo6.read();
  // setup the ultrasonic sensor
  /* pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  */
  // does not work with the ultra sonic sensors
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
  bool stabilisationMode = false;
  // Serial.println(F("T--O--P")); // was used in debugging
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500)  {
          LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
          FB = Xbox.getAnalogHat(LeftHatY, i);
          LR = LR * -1; // Converts the recieved value from controller to a value between 30 and 150 which is what the servos work off.
          LR = LR / 32768;
          LR = LR * 60;
          LR = LR + 90;
          /*Serial.print(F("LeftHatX: ")); // Used for debugging.
            Serial.print(LR);
            Serial.print("\t");*/
          FB = FB * -1; // Same process, but for the forward backward movement.
          FB = FB / 32768;
          FB = FB * 60;
          FB = FB + 90;
          /*Serial.print(F("LeftHatX: "));
            Serial.print(LR);
            Serial.print("\t");*/
          drive(LR, FB);
        } else {
          motor1.write(neutral); // dont turn the motors if nothing from analogue or deadzone
          motor2.write(neutral);
        }

        //      enter or leave stabilisation mode
        if (Xbox.getButtonClick(BACK, i)) {
          stabilisationMode = !stabilisationMode; // enable / disable the stabilisation mode
          if (stabilisationMode == true)  { // set up servos and distance of tri-track for stabilisation mode
            servoDetach();
            myservo.write(40);
            myservo2.write(90);
            myservo3.write(90);
            myservo4.write(150);
            myservo5.write(150);
            myservo6.write(90);
            pin = 2;
            servoAttach();
            Serial.println(withinRange);
            // code does not want to enter this subroutine, not sure why
            stabilisationPosition();
            Serial.println(withinRange);
          }
        }

        // if the stabilisation is started and the button is pressed it will toggle the switch
        // then return to its original stabilisation position
        if (Xbox.getButtonClick(START, i)) {
          if (stabilisationMode == true)  {
            myservo4.write(130); // lifts arm up out of the knob
            delay(500);
            myservo6.write(50); // rotates arm to the switch
            delay(100);
            myservo4.write(150); // flicks switch
            delay(100);
            myservo4.write(130); // raises arm
            myservo6.write(90);
            delay(500);
            myservo4.write(150); // returns arm to original position
          }
        }
/*   
 *    this code was used to change angle of rotation when using buttons
        // adjusting by how much the servos will rotate in degrees
        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          if (movement < 50) {
            movement = movement + 5;
            Serial.print(F("Up: "));
            Serial.println(movement);
            timeDelay = 500 / movement; // takes 500 miliseconds per movment
          }
        }
        
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.print(F("Down: "));
          if (movement > 5) {
            movement = movement - 5;
            timeDelay = 500 / movement; // takes 500 miliseconds per movment
          }
          Serial.println(movement);
        }
*/
        // switches to the servo to the left of current servo
        if (Xbox.getButtonClick(L1, i)) {
          servoDetach();
          if (stabilisationMode == true) {
            pin = 2;
          } else {
            if (pin > 2) {
              pin = pin - 1;
            }
            else {
              pin = 7;
            }
          }
          servoAttach();
          Serial.print(("L1: "));
          Serial.println(pin);
        } else if (Xbox.getButtonClick(R1, i)) {  // switches to the servo to the right of current servo
          Serial.println(stabilisationMode);
          servoDetach();
          if (stabilisationMode == true) {
            pin = 3;
          } else {
            if (pin < 7) {
              pin = pin + 1;
            }
            else {
              pin = 2;
            }
          }
          servoAttach();
          Serial.print(F("R1: "));
          Serial.println(pin);
        }
        // moves the servos by -5 degrees
        if (Xbox.getButtonPress(R2, i)) {
          // moves servos by "movement" degrees over ~500ms
          servo.write(servo.read() + 1);
          delay(10);
        }
        // moves the servos by +5 degrees
        if (Xbox.getButtonPress(L2, i)) {
          servo.write(servo.read() - 1);
          delay(10);
        }


        if (Xbox.getButtonClick(X, i)) {
          if (stabilisationMode == true) {
            // anti clockwise rotation of the knob
            servoDetach();
            myservo2.write(0);
            myservo.write(5);
            delay(500);
            myservo.write(70);
            delay(1000);
            myservo2.write(90);
            delay(500);
            myservo.write(5);
            delay(200);
            servoAttach();
          }
          //Serial.write(servo.read());
          //Serial.println(F("X"));
        }
        if (Xbox.getButtonClick(Y, i)) {
          if (stabilisationMode == true) {
            // clockwise rotation of the knob
            servoDetach();
            myservo2.write(90);
            myservo.write(5);
            delay(500);
            myservo.write(70);
            delay(1000);
            myservo2.write(0);
            delay(500);
            myservo.write(5);
            delay(200);
            servoAttach();
          }
          //Serial.println(myservo.read());
          //Serial.println(F("Y"));
        }
      }

    }
  }
}

void servoDetach() {
  int temp_ = servo.read();
  servo.detach();
  switch (pin) {
    case 2:
      myservo.attach(2);
      myservo.write(temp_);
      break;
    case 3:
      myservo2.attach(3);
      myservo2.write(temp_);
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
}

void servoAttach() {
  temp[0] = myservo.read();
  temp[1] = myservo2.read();
  temp[2] = myservo3.read();
  temp[3] = myservo4.read();
  temp[4] = myservo5.read();
  temp[5] = myservo6.read();
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

void drive(float LeftRight, float FrontBack) {
  motor2.write(LeftRight); // Writes value to sabtertooth to drive motors
  motor1.write(FrontBack);
}


void stabilisationPosition() {
  float distance, duration;
  while (withinRange == false) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    return (distance = (duration / 2) / 29.1);
    if (distance > 12.00) {
      Serial.println("Too far!");
      drive(neutral, neutral - FBboard);
    } else if (distance <= 10.00) {
      Serial.println("Too close!");
      drive(neutral, neutral + FBboard);
    } else {
      Serial.println(F("Target Reached"));
      drive(neutral, neutral);
      withinRange = true;
    }
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
}
