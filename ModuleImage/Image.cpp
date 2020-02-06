#include "Image.h"
#include "assert.h"
#include <iostream>

using namespace std;

Image::Image()
{
	tab = nullptr;
	dimx = 0;
	dimy = 0;
}

Image::Image(int _dimx, int _dimy)
{
	assert(_dimx > 0 && _dimy > 0);
	dimx = _dimx;
	dimy = _dimy;
	tab = new Pixel[dimx * dimy];
}

Image::~Image()
{
	delete[] tab;
	tab = nullptr;
	dimx = dimy = 0;
}

Pixel& Image::getPix(int x, int y) const
{
	//working????
	return tab[y * dimx + x] ;
}

void Image::setPix(int x, int y, const Pixel& p)
{
	tab[y * dimx + x] = p;
}

void Image::drawRect(int xmin, int ymin, int xmax, int ymax, const Pixel& color)
{
	for (int i = xmin; i <= xmax; i++)
	{
		for (int j = ymin; j <= ymax; j++)
		{
			setPix(i, j, color);
		}
	}
}

void Image::erase(const Pixel& color)
{
	drawRect(0, 0, dimx, dimy, color);
}

void Image::test()
{
	//Test of getPix
	Pixel p = Pixel(255, 255, 255); 
	getPix(3, 4) = p;
	Pixel check = tab[4 * dimx + 3];
	int red = check.getRed();
	cout << red << endl;


	int a = 1;
	int &b = a;

}
