#include "Image.h"
#include "assert.h"
#include <iostream>
#include <fstream>
#include <string.h>


using namespace std;

Image::Image()
{
	tab = nullptr;
	dimx = 0;
	dimy = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "SDL_Init error: " << SDL_GetError() << endl;
	}
	window = nullptr;
}

Image::Image(int _dimx, int _dimy)
{
	assert(_dimx > 0 && _dimy > 0);
	dimx = _dimx;
	dimy = _dimy;
	tab = new Pixel[dimx * dimy];

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "SDL_Init error: " << SDL_GetError() << endl;
	}
	window = SDL_CreateWindow("Module Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == nullptr)
	{
		cerr << "SDL_CreapteWindow error : " << SDL_GetError() << endl;
	}
}

Image::~Image()
{
	delete[] tab;
	tab = nullptr;
	dimx = dimy = 0;
	SDL_DestroyWindow(window);
	SDL_Quit(); 
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

void Image::sauver(const string & filename) const {
    ofstream fichier (filename.c_str());
    assert(fichier.is_open());
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
            Pixel& pix = getPix(x++,y);
            fichier << +pix.getRed() << " " << +pix.getGreen() << " " << +pix.getBlue() << " ";
        }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}

void Image::ouvrir(const string & filename) {
    ifstream fichier (filename.c_str());
    assert(fichier.is_open());
        char r,g,b;
        string mot;
        dimx = dimy = 0;
        fichier >> mot >> dimx >> dimy >> mot;
        assert(dimx > 0 && dimy > 0);
        if (tab != NULL) delete [] tab;
        tab = new Pixel [dimx*dimy];
    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
            fichier >> r >> b >> g;
            getPix(x,y).setRed(r);
            getPix(x,y).setGreen(g);
            getPix(x,y).setBlue(b);
        }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole(){
    cout << dimx << " " << dimy << endl;
    for(unsigned int y=0; y<dimy; ++y) {
        for(unsigned int x=0; x<dimx; ++x) {
            Pixel& pix = getPix(x,y);
            cout << +pix.getRed() << " " << +pix.getGreen() << " " << +pix.getBlue() << " ";
        }
        cout << endl;
    }
}

void Image::display() const
{
	SDL_Event windowEvent;

	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}
		}
	}
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


	// Test DrawRect

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
