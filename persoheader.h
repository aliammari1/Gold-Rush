#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#define VIT 5
#define MAX_VIT 10
/**
 * @struct Personne
 * @brief struct for Personnage
 */
typedef struct
{
	SDL_Rect pos;			 /*!< postion de personnage par rapport le background. */
	SDL_Rect pos_relative;	 /*!< position de personnage par rapport une repere relatif. */
	SDL_Surface *img[6][12]; /*!< Tableau des images */
	float vX;				 /*!< acceleration. */
	int direction;			 /*!< direction et etat de l'image. */
	int frame;				 /*!< une sequence des images */
	int d;					 /*!< dernier direction Gauche ou Droite */
	int up;					 /*!< le personnage fait une saut ou non */
} Personne;
typedef struct
{
	SDL_Surface *img;
	SDL_Rect pos;
} image;
void choisir_perso(int *n, SDL_Surface *screen);
void initPerso(Personne *p);
void initPerso2(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screen);
void deplacerPerso(Personne *p, Uint32 dt);
void animerPerso(Personne *p);
void saut(Personne *p);
