// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
char inString[20], inChar, exitString[] = "exit";
int program;
void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  analogWrite(enA, 255);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    delay(20);
  }
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    delay(20);
  }
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
//int getInput(void)
//{
//
//  byte index = 0;
//  Serial.flush(); //flush all previous received and transmitted data
//  resetString(inString);
//  while (!Serial.available()); // hang program until a byte is received notice the ; after the while()
//  {}
//
//  for (int i = 0; i < 19; i++)
//  {
//    inChar = Serial.read(); // Read a character
//    inString[index] = inChar; // Store it
//    index++;
//    inString[index] = '\0'; // Null terminate the string
//    /*Serial.println(inChar);
//      Serial.print("I received: ");
//      Serial.println(inString);*/
//    delay(10);
//    if (Serial.available() == 0)
//      break;
//  }
//  return inString;
//}
//void resetString(String x)
//{
//  memset(&x, 0, sizeof(x)); // Clears all data in a Char String
//}

void loop()
{
  while (Serial.available() > 0)
  {
    program = Serial.parseInt();
  }
  while (Serial.available() == 0)
  {
    if (program == 1)
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      delay(1);
    }
    else if (program == 2)
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      delay(1);
    }
    else if (program == 0)
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      delay(1);
    }
  }

  //    switch (program)
  //    {
  //      case 0:
  //        digitalWrite(in1, LOW);
  //        digitalWrite(in2, HIGH);
  //        delay(100);
  //      case 1:
  //        digitalWrite(in1, HIGH);
  //        digitalWrite(in2, LOW);
  //        delay(100);
  //      case 2:
  //        digitalWrite(in1, LOW);
  //        digitalWrite(in2, LOW);
  //        delay(100);
  //    }

}


