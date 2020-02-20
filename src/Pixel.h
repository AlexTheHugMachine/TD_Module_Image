#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
	unsigned char r, g, b;

public:
	/**
	* @brief
	* 
	*/
	Pixel();
	Pixel(unsigned char nr, unsigned char ng, unsigned char nb);

	unsigned char getRouge() const;
	unsigned char getVert() const;
	unsigned char getBleu() const;

	void setRouge(unsigned char nr);
	void setVert(unsigned char ng);
	void setBleu(unsigned char nb);

	bool operator== (const Pixel& other);
};

#endif // !PIXEL_H

