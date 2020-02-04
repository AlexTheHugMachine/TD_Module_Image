#include "Pixel.h"

Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

Pixel::Pixel(char _r, char _g, char _b)
{
	r = _r;
	g = _g;
	b = _b;
}

char Pixel::getRed() const
{
	return r;
}

char Pixel::getGreen() const
{
	return g;
}

char Pixel::getBlue() const
{
	return b;
}

void Pixel::setRed(char _r)
{
	r = _r;
}

void Pixel::setGreen(char _g)
{
	g = _g;
}

void Pixel::setBlue(char _b)
{
	b = _b;
}
