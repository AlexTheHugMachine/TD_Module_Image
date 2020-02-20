============================ Module Image ==============================================


ATTENTION : Ce programme est uniquement prévu pour fonctionner sous linux


== Participants : ==
				
				LOUIS-ITTY Célian 			p1807560
				BONIS ALEXIS 				p1805132
				RAKOTOMALALA Lucas 			p1083588


== Description : ==


Ceci est une librairie permettant de gérer des images de manière basique.
On peut ainsi créer des images de taille variable à l'aide de rectangles colorés 
ou dessiner pixel par pixel.

On peut également afficher une image dans une fenêtre ou dans la console, 
enregistrer et ouvrir des images au format ppm (Portable Pixmap)


== Pour la compilation : ==


Pour pouvoir fonctionner, la librairie SDL2 doit être installée.

Dans le makefile, vérifier tout d'abord que le chemin d'inclusion de headers de SDL2 est valide pour votre ordinateur, ensuite que le compilateur est disponible sur votre machine, 
ou fournissez en un autre en changeant les constantes définies au début du ficher. 
Les autres options peuvent également être ajustées de la même manière.

La compilation se lance avec "make".


== Organisation du répertoire ==


src : contient le code source
obj : contient les fichiers objets crées à l'étape intermédiaire de la compilation
data : contient les données de l'application, nottamment les images données en exemple
doc : contient les données concernant la documentation
    \
      html : contient la documentation en elle-même au format html
bin : contient les exécutables
    \
      affichage : exemple d'affichage d'une image dans une fenêtre
    \
      exemple : exemple de manipulation et d'enregistrement/ouverture d'image
    \
      test : test des fonctionalités de manipulation d'images


