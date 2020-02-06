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
	drawRect(0, 0, dimx - 1, dimy - 1, color);
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

		bool isDrawRectValid = true;
		Pixel couleur(255, 255, 255);
		int x1 = 10, x2 = 20, y1 = 20, y2 = 30;
		drawRect(x1, y1, x2, y2, couleur);
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (!(tab[j * dimx + i] == couleur))
				{
					isDrawRectValid = false;
				}
			}
		}
		if (isDrawRectValid) cout << "DrawRect is Valid" << endl << endl;
		else cout << "ERROR : DrawRect doesn't work !!" << endl << endl;

	//Test setPix
		Pixel pInit(255, 255, 255);
		setPix(1, 1, pInit);
		
		if (pInit == tab[1*dimx + 1])
		{
			cout << "setPix est validee" << endl << endl;
		}
		else
		{
			cout << "setPix ne marche pas" << endl << endl;
		}
	//Test erase
		bool isEraseValid = true;
		Pixel er(46, 84, 234);
		erase(er);
		for (int i = 0; i < dimx; i++) {
			for (int j = 0; j < dimy; j++) {
				if (!(tab[j * dimx + i] == er))
				{
					isEraseValid = false;
				}
			}
		}
		if (isEraseValid) cout << "Erase is Valid" << endl << endl;
		else cout << "ERROR : Erase doesn't work !!" << endl << endl;

	}
	else // Pixel equality check failed...
	{
		cout << "ERROR : The Pixel equality check is not fonctional. The other tests therefore couldn't be completed" << endl;
	}
}
