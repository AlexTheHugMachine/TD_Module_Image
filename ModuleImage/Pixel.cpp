#include "Pixel.h"

Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

Pixel::Pixel(unsigned char _r, unsigned char _g, unsigned char _b)
{
	r = _r;
	g = _g;
	b = _b;
}

unsigned char Pixel::getRed() const
{
	return r;
}

unsigned char Pixel::getGreen() const
{
	return g;
}

unsigned char Pixel::getBlue() const
{
	return b;
}

void Pixel::setRed(unsigned char _r)
{
	r = _r;
}

void Pixel::setGreen(unsigned char _g)
{
	g = _g;
}

void Pixel::setBlue(unsigned char _b)
{
	b = _b;
}

bool Pixel::operator==(const Pixel& other)
{
	return r == other.getRed() &&
		g == other.getGreen() &&
		b == other.getBlue();
}
