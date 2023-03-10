#include "Image.h"

int main(int argc, char** argv)
{
	Image image(10, 10);

	Pixel black(0, 0, 0);
	Pixel green(0, 192, 0);
	Pixel cyan(128, 255, 255);

	image.effacer(black);
	image.dessinerRectangle(3, 0, 5, 2, green);
	image.dessinerRectangle(1, 4, 7, 4, green);
	image.dessinerRectangle(4, 3, 4, 6, green);
	image.dessinerRectangle(3, 6, 3, 9, green);
	image.dessinerRectangle(5, 6, 3, 9, green);
	image.setPix(1, 2, green);
	image.setPix(1, 3, green);
	image.setPix(7, 2, green);
	image.setPix(7, 3, green);
	image.setPix(2, 9, green);
	image.setPix(6, 9, green);
	image.setPix(3, 1, cyan);
	image.setPix(5, 1, cyan);

	image.afficher();

	return 0;
}
