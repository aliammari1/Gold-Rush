#ifndef map_H_INCLUDED
#define map_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

/**
 * @struct map
 * @brief struct for map
 */
typedef struct
{
	SDL_Surface *map;		 /*!< image de minimap*/
	SDL_Rect pos_map;		 /*!< position de la minimap*/
	SDL_Surface *mini_perso; /*!< image du minipersonnage*/
	SDL_Rect perso_pos_map;	 /*!< position de la minipersonnage*/

} map;
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
void initialiser_map(map *m, SDL_Surface *screen);
void perso_map(map *m, Personne *p);
void affiche_map(map *m, SDL_Surface *screen, Personne *p);
void sauvegarder(int score, char nomjoueur[], char nomfichier[]);
void meilleur(char nomfichier[], int score, char nomjoueur[]);

#endif
