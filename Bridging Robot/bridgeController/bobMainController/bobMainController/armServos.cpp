#include "armServos.h"



armServos::armServos()
{
	right.attach(9);
	left.attach(10);
}


armServos::~armServos()
{
}

void armServos::up(int angle)
{
	rotation += angle;
	right.write(rotation);
	left.write(180 - rotation);
}

void armServos::down(int angle)
{
	rotation -= angle;
	right.write(rotation);
	left.write(180 - rotation);
}
