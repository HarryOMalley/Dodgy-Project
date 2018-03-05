#include<Wire.h>
#include<Servo.h>

Servo xServo, yServo;

const int MPU=0x68; 
const int xUower = 5000;
const int xLower = 1000;
const int yUpper = 5000;
const int yLower = 1000;

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  xServo.attach(8);
  yServo.attach(9);
  xServo.write(90);
  yServo.write(90);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  /*
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); */
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);  
  Serial.println(" ");
  delay(666);
  
  // balancing the platform
  if (GyX > xUower) { xServo.write(xServo.read() - 5); }
  else if (GyX < xLower) { xServo.write(xServo.read() + 5); }  
  if (GyY > yUpper) { yServo.write(yServo.read() - 5); } 
  else if (GyY < yLower) { yServo.write(yServo.read() + 5); }
  
}