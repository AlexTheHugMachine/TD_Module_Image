#include "Pixel.h"

Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

Pixel::Pixel(unsigned char nr, unsigned char ng, unsigned char nb)
{
	r = nr;
	g = ng;
	b = nb;
}

unsigned char Pixel::getRouge() const
{
	return r;
}

unsigned char Pixel::getVert() const
{
	return g;
}

unsigned char Pixel::getBleu() const
{
	return b;
}

void Pixel::setRouge(unsigned char nr)
{
	r = nr;
}

void Pixel::setVert(unsigned char ng)
{
	g = ng;
}

void Pixel::setBleu(unsigned char nb)
{
	b = nb;
}

bool Pixel::operator==(const Pixel& other)
{
	return r == other.getRouge() &&
		g == other.getVert() &&
		b == other.getBleu();
}
