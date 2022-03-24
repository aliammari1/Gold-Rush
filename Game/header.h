#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>

typedef struct 
{
	SDL_Rect pos1;
	SDL_Rect pos2;
	SDL_Surface* img;
}image;


void initImage(image *im, float x, float y, char path[]);
typedef struct {
    SDL_Rect position;
    TTF_Font *font;
    SDL_Surface *surfaceTexte;
    SDL_Color textColor;
    char texte [50];
}text;

void initText(text *t);
void freeText(text A);
void displayText(text t,SDL_Surface *screen);
