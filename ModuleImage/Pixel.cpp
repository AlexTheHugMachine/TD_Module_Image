#include "Pixel.h"

Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

Pixel::Pixel(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
}

int Pixel::getRed() const
{
	return r;
}

int Pixel::getGreen() const
{
	return g;
}

int Pixel::getBlue() const
{
	return b;
}

void Pixel::setRed(int _r)
{
	r = _r;
}

void Pixel::setGreen(int _g)
{
	g = _g;
}

void Pixel::setBlue(int _b)
{
	b = _b;
}
