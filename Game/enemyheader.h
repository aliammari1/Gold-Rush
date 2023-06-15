#include <stdio.h>
#include <stdlib.h>
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include"SDL/SDL_mixer.h"

typedef enum STATE STATE;
enum STATE{WAITING,FOLLOWING};

/**
* @struct Personne
* @brief struct for Personnage
*/
/**
* @struct Ennemi
* @brief struct for Ennemi
*/

typedef struct 
{
	int dir;/*!< direction de l ennemi si dir=0=droit si dir=1=gauche*/
	SDL_Rect pos1;/*!< position du l ennemi dans sur l ecran*/
	SDL_Rect pos2;/*!< position de l ennemi par rapport au spritesheet*/
	SDL_Surface* img;/*!< spritesheet ennemi*/
	STATE state;/*!< l etat de l ennemi*/
}Ennemi;
typedef struct
{
	SDL_Rect pos;/*!< postion de personnage par rapport le background. */
	SDL_Rect pos_relative;/*!< position de personnage par rapport une repere relatif. */
	SDL_Surface *img[6][12];/*!< Tableau des images */
	float vX;/*!< acceleration. */
	int direction;/*!< direction et etat de l'image. */
	int frame;/*!< une sequence des images */
	int d;/*!< dernier direction Gauche ou Droite */
	int up;/*!< le personnage fait une saut ou non */
}Personne;

void initEnnemi(Ennemi*e);
void afficherEnnemi(Ennemi e, SDL_Surface * screen);
void animerEnnemi( Ennemi * e);
void deplacer( Ennemi * e);
int collisionBB( Personne p, Ennemi e);
void deplacerIA( Ennemi * e, Personne p);


