#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "config.h"

class LEDS
{
public:
	LEDS();
	~LEDS();
	void setup();
	void set(int, int, int);
	void brightness(int);
	Adafruit_NeoPixel ledstrip;
};
