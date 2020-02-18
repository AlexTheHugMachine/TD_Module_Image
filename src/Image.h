#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Pixel.h"
#include <SDL.h>

const int WIDTH = 800, HEIGHT = 600;
class Image
{
private:
	Pixel* tab;
	int dimx, dimy;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Image();
	Image(int dimensionX, int dimensionY);
	~Image();

	Pixel& getPix(int x, int y) const;
	void setPix(int x, int y, const Pixel& couleur);
	void dessinerRectangle(int Xmin, int Ymin, int Xmax, int Ymax, const Pixel& color);

	void effacer(const Pixel& couleur);
	void afficher() const;
	void sauver(const std::string & filename) const;
	void ouvrir(const std::string & filename);
	void afficherConsole() const;

	void testRegression();

};

#endif
