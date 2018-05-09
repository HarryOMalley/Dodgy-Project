//#include "armServos.h"
//
//armServos::armServos()
//{
//	right.attach(armServo1);
//	left.attach(armServo2);
//	right.write(50);
//	left.write(50);
//	rotation = 0;
//}
//
//armServos::~armServos()
//{
//}
//
//void armServos::up(int angle)
//{
//	if ((rotation + angle) < 180)
//	{
//		//rotation += angle;
//		//right.write(rotation);
//		//left.write(180 - rotation);
//		//Serial.print("rotating  ");
//		//Serial.println(rotation);
//		right.write(180);
//		left.write(0);
//		delay(100);
//	}
//}
//
//void armServos::down(int angle)
//{
//	if ((rotation - angle) > 0)
//	{
//		//rotation -= angle;
//		//right.write(rotation);
//		//left.write(180 - rotation);
//		//Serial.println("rotating");
//		right.write(180);
//		left.write(0);
//		delay(100);
//	}
//}
