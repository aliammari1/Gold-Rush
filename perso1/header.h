#include <stdio.h>
#include <stdlib.h>
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"
#include"SDL/SDL_mixer.h"
#define VIT 5
#define MAX_VIT 10
typedef struct
{
	SDL_Rect pos;
	SDL_Rect pos_relative;
	SDL_Surface *img[6][12];
	float vX,vY;
	int direction,frame,d,up;
}Personne;
void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface * screen);
void deplacerPerso(Personne *p,Uint32 dt);
void animerPerso(Personne* p);
void saut(Personne* p);
