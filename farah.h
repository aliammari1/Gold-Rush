#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

typedef struct
{
  SDL_Surface *BgImg;
  SDL_Rect PositionBg;
  SDL_Rect camera;
  SDL_Rect pos_clouds;
  SDL_Surface *clouds;
} Background;

void initBackground(Background *B);
void freeBackground(Background *B);
void afficherBack(Background *B, SDL_Surface *screen);
void scrolling(Background *B, bool b[], int pasmouv);
void animation_clouds(Background *B, SDL_Surface *screen);
// SDL_Color GetPixel(SDL_Surface *surface,int x,int y);

int collisionPP(Personne *p, SDL_Surface *Masque);
// collisionPP(SDL_Surface *calque,SDL_Surface *perso,SDL_Rect posperso,SDL_Rect posmap);
SDL_Color GetPixel(SDL_Surface *surface, int x, int y);

// tache blanche

// void initpartage(Background *B,Background *B1,Personne *p1,Personne*p2);

void initpartage1(Background *B, Personne *p);
void initpartage2(Background *B1, Personne *p);
void afficherpartage(Background *B, SDL_Surface *screen);

#endif
