#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
	int r, g, b;

public:
	Pixel();
	Pixel(char _r, char _g, char _b);

	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	void setRed(char _r);
	void setGreen(char _g);
	void setBlue(char _b);
};

#endif // !PIXEL_H

