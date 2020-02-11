#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Pixel.h"
class Image
{
private:
	Pixel* tab;
	int dimx, dimy;

public:
	Image();
	Image(int _dimx, int _dimy);
	~Image();

	Pixel& getPix(int x, int y) const;
	void setPix(int x, int y, const Pixel& p);
	void drawRect(int xmin, int ymin, int xmax, int ymax, const Pixel& color);

	void erase(const Pixel& color);
	void display() const;
	void sauver(const std::string & filename) const;
	void ouvrir(const std::string & filename);
	void afficherConsole();

	void test();

};

#endif
