#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
	int r, g, b;

public:
	Pixel();
	Pixel(int _r, int _g, int _b);

	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	void setRed(int _r);
	void setGreen(int _g);
	void setBlue(int _b);
};

#endif // !PIXEL_H

