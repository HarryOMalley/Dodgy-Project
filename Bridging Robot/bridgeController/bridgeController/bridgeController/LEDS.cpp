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
		ledstrip.setPixelColor(n, 0, 255, 0);
	}
	ledstrip.show();
	delay(1000);
}

void LEDS::set(int r, int g, int b)
{
	for (int n = 0; n < NUM_LEDS; n++)
	{
		ledstrip.setPixelColor(n, r, g, b);
	}
	ledstrip.show();
	delay(100);
}

void LEDS::brightness(int brightness)
{
	ledstrip.setBrightness(brightness);
	ledstrip.show();
}
