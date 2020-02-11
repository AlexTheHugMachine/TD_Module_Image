#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
	unsigned char r, g, b;

public:
	Pixel();
	Pixel(unsigned char _r, unsigned char _g, unsigned char _b);

	unsigned char getRed() const;
	unsigned char getGreen() const;
	unsigned char getBlue() const;

	void setRed(unsigned char _r);
	void setGreen(unsigned char _g);
	void setBlue(unsigned char _b);

	bool operator== (const Pixel& other);
};

#endif // !PIXEL_H

