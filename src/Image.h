#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Pixel.h"
#include <SDL.h>

const int WIDTH = 200, HEIGHT = 200;
class Image
{
private:
	Pixel* tab;
	unsigned int dimx, dimy;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	unsigned int zoomIncrement;
	int zoomLevel;

public:
	/**
	 * @brief
	 * Constructeur par défaut de la classe Image
	 * @warning
	 * L'image crée à une taille nulle
	 */

	Image();
	/**
	 * @brief
	 * Constructeur de la classe Image avec deux paramètres.
	 * @param
	 * Deux entiers dimensionX, qui représente la dimension de l'image sur l'axe x,
	 * et dimensionY, qui représente la dimension de l'image sur l'axe y.
	 * @warning
	 * Ne pas mettre un autre type qu'un nombre entier.
	 */
	 
	Image(int dimensionX, int dimensionY);
	
	/**
	 * @brief
	 * Destructeur de la classe Image
	 */
	~Image();

	/**
	 * @brief
	 * Accesseur d'un  pixel de l'image
	 * @param
	 * x et y coordonées entières du Pixel de l'image
	 * @return
	 * Référence au Pixel original de l'image
	 * @warning
	 * La valeur du pixel dans l'image peut ainsi être changée par une utilisation pas assez rigoureuse
	 */
	Pixel& getPix(int x, int y) const;
	/**
	 * @brief
	 * Mutateur d'un pixel de l'image
	 * @param
	 * x et y coordonnées entières, pixel stockant une couleur
	 */
	void setPix(int x, int y, const Pixel& couleur);
	/**
	 * @brief
	 * Dessine un rectangle sur l'image
	 * @param
	 * Coordonnées des 2 points haut/gauche et bas/droite, couleur
	 */
	void dessinerRectangle(int Xmin, int Ymin, int Xmax, int Ymax, const Pixel& color);

	/**
	 * @brief
	 * Efface le contenu de l'image en la remplissant de couleur
	 * @param
	 * Couleur
	 */
	void effacer(const Pixel& couleur);

	/**
	 * @brief
	 * Afficher l'image avec SDL2
	 * @param
	 * Rien
	 */
	void afficher();

	/**
	 * @brief
	 * Sauvegarde l'image au format ppm
	 * @param
	 * Chemin de la sauvegarde
	 */
	void sauver(const std::string & filename) const;

	/**
	 * @brief
	 * Ouvrir une image de format ppm
	 * @param
	 * Chemin de l'image
	 */
	void ouvrir(const std::string & filename);

	/**
	 * @brief
	 * Afficher l'image dans la console
	 * @param
	 * Rien
	 */
	void afficherConsole() const;

	/**
	 * @brief
	 * Teste les fonctionalités des fonctions de manipulation de l'image
	 * @param
	 * Rien
	 */
	void testRegression();

};

#endif
