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
	unsigned int dimx, dimy;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Image();
	/*
	 * @brief
	 * Constructeur de la classe Image avec deux paramètres.
	 * @param
	 * Deux entiers dimensionX, qui représente la dimension de l'image sur l'axe x,
	 * et dimensionY, qui représente la dimension de l'image sur l'axe y.
	 * @warning
	 * Ne pas mettre un autre type qu'un nombre entier.
	 */
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
