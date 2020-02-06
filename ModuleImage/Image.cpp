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
//Test of Pixel equality
	Pixel p1(255, 255, 255);
	Pixel p2(255, 255, 255);
	if (p1 == p2)
	{
		cout << "Pixel Equality check is valid!" << endl << endl;

		//Test of getPix

		bool isGetPixValid = true;
		Pixel& pix = getPix(3, 4);
		Pixel checkBefore = tab[4 * dimx + 3];
		if (!(checkBefore == pix))
		{
			cout << "ERROR : Pixel value not retured from getPix" << endl << endl;
			isGetPixValid = false;
		}
		Pixel checkAfter(255, 255, 255);
		pix = checkAfter;
		if (!(checkAfter == tab[4 * dimx + 3]))
		{
			cout << "ERROR : Pixel retured from getPix is not the original (not a reference)" << endl << endl;
			isGetPixValid = false;
		}
		if (isGetPixValid) cout << "getPix is Valid!!" << endl << endl;


		// Test rect

		Pixel couleur;
		drawRect(15, 20, 50, 75, couleur);
		for (int i = 15; i < 50; i++) {
			for (int j = 20; j < 75; j++) {

			}
		}
		//Test setPix
		Pixel pInit;
		Pixel pRef;
		pInit.setBlue(0);
		pInit.setGreen(0);
		pInit.setRed(0);
		setPix(1, 1, pInit);
		pRef.setBlue(0);
		pRef.setGreen(0);
		pRef.setRed(0);
		if (pRef.getBlue() == pInit.getBlue())
		{
			if (pRef.getGreen() == pInit.getGreen())
			{
				if (pRef.getRed() == pInit.getRed())
				{
					cout << "setPix est validee" << endl << endl;
				}
			}
		}
		else
		{
			cout << "setPix ne marche pas" << endl << endl;
		}
	}
	else // Pixel equality check failed...
	{
		cout << "ERROR : The Pixel equality check is not fonctional. The other tests therefore couldn't be completed" << endl;
	}
}
