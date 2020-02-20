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
	zoomLevel = 5;
	zoomIncrement = 10;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "SDL_Init error: " << SDL_GetError() << endl;
	}
	window = nullptr;
	renderer = nullptr;
	texture = nullptr;
}

Image::Image(int dimensionX, int dimensionY)
{
	assert(dimensionX > 0 && dimensionY > 0);
	dimx = dimensionX;
	dimy = dimensionY;
	tab = new Pixel[dimx * dimy];
	zoomLevel = 5;
	zoomIncrement = 10;


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
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

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dimx, dimy);
	if (texture == nullptr)
	{
		cerr << "SDL_CreateTexture error : " << SDL_GetError() << endl;
	}
}

Image::~Image()
{
	if(texture != nullptr) SDL_DestroyTexture(texture);
	if(renderer != nullptr) SDL_DestroyRenderer(renderer);
	if(window != nullptr) SDL_DestroyWindow(window);
	SDL_Quit(); 
	delete[] tab;
	tab = nullptr;
	dimx = dimy = 0;
}

Pixel& Image::getPix(int x, int y) const
{
	assert(x >= 0 && y >= 0);
	return tab[y * dimx + x] ;
}

void Image::setPix(int x, int y, const Pixel& couleur)
{
	assert(x >= 0 && y >= 0);
	assert(couleur.getRouge() >= 0 && couleur.getRouge() <= 255 &&
	couleur.getVert() >= 0 && couleur.getVert() <= 255 &&
	couleur.getBleu() >= 0 && couleur.getBleu() <= 255);

	tab[y * dimx + x] = couleur;
}

void Image::dessinerRectangle(int Xmin, int Ymin, int Xmax, int Ymax, const Pixel& couleur)
{
	assert(Xmin >= 0 && Ymin >= 0 && Xmax >= 0 && Ymax >= 0);
	assert(couleur.getRouge() >= 0 && couleur.getRouge() <= 255 &&
	couleur.getVert() >= 0 && couleur.getVert() <= 255 &&
	couleur.getBleu() >= 0 && couleur.getBleu() <= 255);
	
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
	assert(couleur.getRouge() >= 0 && couleur.getRouge() <= 255 &&
	couleur.getVert() >= 0 && couleur.getVert() <= 255 &&
	couleur.getBleu() >= 0 && couleur.getBleu() <= 255);

	dessinerRectangle(0, 0, dimx - 1, dimy - 1, couleur);
}

void Image::sauver(const string & filename) const 
{
	assert(!filename.empty());

    ofstream fichier(filename.c_str());
    assert(fichier.is_open());
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
            Pixel& pix = getPix(x, y);
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}


void Image::ouvrir(const string & filename) 
{
	assert(!filename.empty());

    ifstream fichier(filename.c_str());
    assert(fichier.is_open());

        unsigned int r,g,b;
        string mot;
        //dimx = dimy = 0;
        fichier >> mot >> dimx >> dimy >> mot;
        assert(dimx > 0 && dimy > 0);
        if (tab != NULL) delete[] tab;
        tab = new Pixel[dimx*dimy];
    for(unsigned int y=0; y<dimy; ++y)
        for(unsigned int x=0; x<dimx; ++x) {
            fichier >> r >> g >> b;
            getPix(x,y).setRouge((unsigned char)r);
            getPix(x,y).setVert((unsigned char)g);
            getPix(x,y).setBleu((unsigned char)b);
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

void Image::afficher()
{
	SDL_Event windowEvent;
	bool quit = false;

	while (!quit)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				quit = true;
			}
			if(windowEvent.type == SDL_KEYDOWN)
			{
				switch(windowEvent.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						if(texture != nullptr) SDL_DestroyTexture(texture);
						if(renderer != nullptr) SDL_DestroyRenderer(renderer);
						if(window != nullptr) SDL_DestroyWindow(window);
						SDL_Quit(); 
						quit = true;
						break;

					case SDL_SCANCODE_T:
						zoomLevel++;
						if(zoomLevel > 19) zoomLevel = 19;
						break;

					case SDL_SCANCODE_G:
						zoomLevel--;
						if(zoomLevel < 0) zoomLevel = 0;
						break;

					default:
						break;
				}
			}
		}
		
		if(quit) break;

		int col = 169;
		SDL_SetRenderDrawColor(renderer, col, col, col, 255);
		SDL_RenderClear(renderer);

		if(SDL_SetRenderTarget(renderer, texture) != 0)
		{
			cout<<"Erreur SDL_SetRenderTarget : "<< SDL_GetError() <<endl;
			exit(1);
		}
		for (unsigned int i = 0; i < dimx; ++i)
		{
			for (unsigned int j = 0; j < dimy; ++j)
			{
				const Pixel p = tab[dimx * j + i];
				SDL_SetRenderDrawColor(renderer, p.getRouge(), p.getVert(), p.getBleu(), 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
		SDL_SetRenderTarget(renderer, NULL);

		SDL_Rect r;
		r.x = 0;
		r.y = 0;
		r.w = dimx + zoomIncrement * zoomLevel;
		r.h = dimy + zoomIncrement * zoomLevel;

		if(r.w < (signed int) dimx) r.w = dimx;
		if(r.h < (signed int) dimy) r.h = dimy;
		if(r.w > WIDTH) r.w = WIDTH;
		if(r.h > HEIGHT) r.h = HEIGHT;

		r.x = (r.x-r.w/2) + WIDTH/2;
		r.y = (r.y-r.h/2) + HEIGHT/2;
		SDL_RenderCopy(renderer, texture, NULL, &r);
		
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
		cout << "Le test d'egalite de 2 Pixels marche" << endl << endl;

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
		if (isGetPixValid) cout << "getPix marche" << endl << endl;


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
		if (isDrawRectValid) cout << "dessinerRectangle marche" << endl << endl;
		else cout << "ERROR : dessinerRectangle doesn't work !!" << endl << endl;

	//Test setPix
		Pixel pInit(255, 255, 255);
		setPix(1, 1, pInit);

		if (pInit == tab[1*dimx + 1])
		{
			cout << "setPix marche" << endl << endl;
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
		if (isEraseValid) cout << "Effacer marche" << endl << endl;
		else cout << "ERROR : Effacer doesn't work !!" << endl << endl;

	}
	else // Pixel equality check failed...
	{
		cout << "ERROR : The Pixel equality check is not fonctional. The other tests therefore couldn't be completed" << endl;
	}
}
