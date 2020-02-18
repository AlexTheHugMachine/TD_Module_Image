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
	renderer = nullptr;
}

Image::Image(int dimensionX, int dimensionY)
{
	assert(dimensionX > 0 && dimensionY > 0);
	dimx = dimensionX;
	dimy = dimensionY;
	tab = new Pixel[dimx * dimy];

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "SDL_Init error: " << SDL_GetError() << endl;
	}

	window = SDL_CreateWindow("Module Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == nullptr)
	{
		cerr << "SDL_CreapteWindow error : " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		cerr << "SDL_CreateRenderer error : " << SDL_GetError() << endl;
	}
}

Image::~Image()
{
	delete[] tab;
	tab = nullptr;
	dimx = dimy = 0;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit(); 
}

Pixel& Image::getPix(int x, int y) const
{
	return tab[y * dimx + x] ;
}

void Image::setPix(int x, int y, const Pixel& couleur)
{
	tab[y * dimx + x] = couleur;
}

void Image::dessinerRectangle(int Xmin, int Ymin, int Xmax, int Ymax, const Pixel& couleur)
{
	for (int i = Xmin; i <= Xmax; i++)
	{
		for (int j = Ymin; j <= Ymax; j++)
		{
			setPix(i, j, couleur);
		}
	}
}

void Image::effacer(const Pixel& couleur)
{
	dessinerRectangle(0, 0, dimx - 1, dimy - 1, couleur);
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
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
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
            getPix(x,y).setRouge(r);
            getPix(x,y).setVert(g);
            getPix(x,y).setBleu(b);
        }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole() const{
    cout << dimx << " " << dimy << endl;
    for(unsigned int y=0; y<dimy; ++y) {
        for(unsigned int x=0; x<dimx; ++x) {
            Pixel& pix = getPix(x,y);
            cout << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
        cout << endl;
    }
}

void Image::afficher() const
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
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		for (unsigned int i = 0; i < dimx; ++i)
		{
			for (unsigned int j = 0; j < dimy; ++j)
			{
				const Pixel p = tab[dimx * j + i];
				SDL_SetRenderDrawColor(renderer, p.getRouge(), p.getVert(), p.getBleu(), 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
		SDL_RenderPresent(renderer);
	}
}

void Image::testRegression()
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


	// Test dessinerRectangle

		bool isDrawRectValid = true;
		Pixel couleur(255, 255, 255);
		int x1 = 10, x2 = 20, y1 = 20, y2 = 30;
		dessinerRectangle(x1, y1, x2, y2, couleur);
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				if (!(tab[j * dimx + i] == couleur))
				{
					isDrawRectValid = false;
				}
			}
		}
		if (isDrawRectValid) cout << "dessinerRectangle is Valid" << endl << endl;
		else cout << "ERROR : dessinerRectangle doesn't work !!" << endl << endl;

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

	//Test effacer
		bool isEraseValid = true;
		Pixel er(46, 84, 234);
		effacer(er);
		for (unsigned int i = 0; i < dimx; i++) {
			for (unsigned int j = 0; j < dimy; j++) {
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
