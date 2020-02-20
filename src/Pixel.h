#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
private:
	unsigned char r, g, b;

public:
	/**
	* @brief
	* Constructeur par défaut de Pixel
	*/
	Pixel();

	/**
	* @brief
	* Constructeur de Pixel en le remplissant de couleur
	* @param
	* 3 entiers entre 0 et 255 (Rouge, Vert Bleu)
	*/
	Pixel(unsigned char nr, unsigned char ng, unsigned char nb);

	/**
	* @brief
	* Accesseur de la composante Rouge
	* @return
	* Retourne un entier entre 0 et 255
	*/
	unsigned char getRouge() const;

	/**
	* @brief
	* Accesseur de la composante Verte
	* @param
	* Rien
	* @return
	* Retourne un entier entre 0 et 255
	*/
	unsigned char getVert() const;

	/**
	* @brief
	* Accesseur de la composante Bleue
	* @param
	* Rien
	* @return
	* Retourne un entier entre 0 et 255
	*/
	unsigned char getBleu() const;


	/**
	* @brief
	* Mutateur de la composante Rouge
	* @param
	* Un entier entre 0 et 255
	*/
	void setRouge(unsigned char nr);
	
	/**
	* @brief
	* Mutateur de la composante Verte
	* @param
	* Un entier entre 0 et 255
	*/
	void setVert(unsigned char ng);

	/**
	* @brief
	* Mutateur de la composante Bleue
	* @param
	* Un entier entre 0 et 255
	*/
	void setBleu(unsigned char nb);

	/**
	* @brief
	* Test d'égalité entre deux Pixels
	* @param
	* 2 Pixels de chaque côté du ==
	* @return
	* booléen
	* @code
	* // p1 et p2 sont des Pixels avec toutes leurs valeurs initialisées
	* if(p1 == p2)
	* {  des choses... }
	* @endcode
	*/
	bool operator== (const Pixel& other);
};

#endif // !PIXEL_H

