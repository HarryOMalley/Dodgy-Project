#include "LEDS.h"

LEDS::LEDS()
{
}

LEDS::~LEDS()
{
}

void LEDS::setup()
{
	ledstrip = Adafruit_NeoPixel(NUM_LEDS, LEDPIN, NEO_GRB + NEO_KHZ800);
	ledstrip.begin();
	ledstrip.setBrightness(50);
	for (int n = 0; n < NUM_LEDS; n++)
	{
		ledstrip.setPixelColor(n, 255, 255, 255);
	}
	ledstrip.show();
}

void LEDS::set(int r, int g, int b)
{
	for (int n = 0; n < NUM_LEDS; n++)
	{
		ledstrip.setPixelColor(n, r, g, b);

	}
	ledstrip.show();
}

void LEDS::brightness(int brightness)
{
	ledstrip.setBrightness(brightness);
	ledstrip.show();
}
