#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
	char r, g, b;

public:
	Pixel();
	Pixel(char _r, char _g, char _b);

	char getRed() const;
	char getGreen() const;
	char getBlue() const;

	void setRed(char _r);
	void setGreen(char _g);
	void setBlue(char _b);
};

#endif // !PIXEL_H

