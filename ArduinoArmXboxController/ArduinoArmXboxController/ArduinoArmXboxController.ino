<<<<<<< HEAD
#include <XBOXRECV.h>
#include <Servo.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

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

bool stabilisationMode = false;
int movement = 10;
int timeDelay = 50;
int pin = 2;
int temp[10] = {};

// Defines FB and LR as float values for sending to the sabertooth.
float FB;
float LR;

void setup() {
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
        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500)  {

          LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
          FB = Xbox.getAnalogHat(LeftHatY, i);
          LR = LR * -1; // Converts the recieved value from controller to a value between 30 and 150 which is what the servos work off.
          LR = LR / 32768;
          LR = LR * 60;
          LR = LR + 90;
          motor2.write(LR); // Writes calculated value to servo.
          /*Serial.print(F("LeftHatX: ")); // Used for debugging.
            Serial.print(LR);
            Serial.print("\t");*/
          FB = FB * -1; // Same process, but for the forward backward movement.
          FB = FB / 32768;
          FB = FB * 60;
          FB = FB + 90;
          motor1.write(FB);
          /*Serial.print(F("LeftHatX: "));
            Serial.print(LR);
            Serial.print("\t");*/
        } else {
          motor1.write(90);
          motor2.write(90);
        }
        if (Xbox.getButtonClick(BACK, i)) {
          stabilisationMode = !stabilisationMode;
          Xbox.setLedOn(LED1, i);
          if (stabilisationMode == true) {
            Serial.print(stabilisationMode);
            servoDetach();
            myservo.write(40);
            myservo2.write(90);
            myservo3.write(90);
            myservo4.write(150);
            myservo5.write(150);
            myservo6.write(90);
            pin = 2;
            servoAttach();
          }
        }
        // these two selections allow the servo m
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
        } else if (Xbox.getButtonClick(R1, i)) {
          Serial.print(stabilisationMode);
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

        if (Xbox.getButtonClick(A, i)) {
          for (int i = 0; i < 6; i++) {
            servo.write(servo.read() - 1);
            delay(100);
          }
          Serial.println(myservo.read());
        }
        if (Xbox.getButtonClick(B, i)) {
          for (int i = 0; i < 6; i++) {
            servo.write(servo.read() + 1);
            delay(100);
          }
          Serial.write(servo.read());
        }
        if (Xbox.getButtonClick(X, i)) {
          if (stabilisationMode == true) {
            // anti clockwise
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
          } else {
            for (int i = 0; i < movement; i++) {
              servo.write(servo.read() - 1);
              delay(timeDelay);
            }
            Serial.println(myservo.read());
          }
          Serial.write(servo.read());
          //Serial.println(F("X"));
        }
        if (Xbox.getButtonClick(Y, i)) {
          if (stabilisationMode == true) {
            // clockwise
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
            } else {
            for (int i = 0; i < movement; i++) {
              servo.write(servo.read() + 1);
              delay(timeDelay);
            }

          }
          Serial.println(myservo.read());
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
=======
/*
  Example sketch for the Xbox Wireless Reciver library - developed by Kristian Lauszus
  It supports up to four controllers wirelessly
  For more information see the blog post: http://blog.tkjelectronics.dk/2012/12/xbox-360-receiver-added-to-the-usb-host-library/ or
  send me an e-mail:  kristianl@tkjelectronics.com
*/


#include <XBOXRECV.h>
#include <Servo.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

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

int pin = 2;
int temp[10] = {};

// Defines FB and LR as float values for later use.
float FB;
float LR;

void setup() {
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
        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500)  {

          LR = Xbox.getAnalogHat(LeftHatX, i); // Gets the values from the left analog stick and saves it to a variable.
          FB = Xbox.getAnalogHat(LeftHatY, i);
          LR = LR * -1; // Converts the recieved value from controller to a value between 30 and 150 which is what the servos work off.
          LR = LR / 32768;
          LR = LR * 60;
          LR = LR + 90;
          motor2.write(LR); // Writes calculated value to servo.
          Serial.print(F("LeftHatX: ")); // Used for debugging.
          Serial.print(LR);
          Serial.print("\t");
          FB = FB * -1; // Same process, but for the forward backward movement.
          FB = FB / 32768;
          FB = FB * 60;
          FB = FB + 90;
          motor1.write(FB);
          Serial.print(F("LeftHatX: "));
          Serial.print(LR);
          Serial.print("\t");
        } else {
          motor1.write(90);
          motor2.write(90);
        }

        if (Xbox.getButtonClick(L1, i)) {
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

          Serial.print(("L1: "));
          Serial.print(pin);
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
        } else if (Xbox.getButtonClick(R1, i)) {
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
          Serial.println(pin);
        }
        if (Xbox.getButtonClick(A, i)) {
         for (int i = 0; i < 10; i++) {
          servo.write(servo.read() - 1);
          delay(50);
        }
        }
        if (Xbox.getButtonClick(B, i))
        for (int i = 0; i < 10; i++) {
          servo.write(servo.read() + 1);
          delay(50);
        }
        if (Xbox.getButtonClick(X, i)) {
          for (int i = 0; i < 6; i++) {
            servo.write(servo.read() - 1);
            delay(100);
          }
          Serial.println(F("X"));
        }
        if (Xbox.getButtonClick(Y, i)) {
          for (int i = 0; i < 6; i++) {
            servo.write(servo.read() + 1);
            delay(100);
          }
          Serial.println(F("Y"));
        }
      }

    }
  }
}

>>>>>>> origin/master
