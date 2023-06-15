#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
/**
* @struct text
* @brief struct for text
*/


typedef struct  {
    SDL_Surface* textSurface;/*!<texte du temps en format image*/
    SDL_Rect positionText;/*!< position  de la texte du temps*/
    char txt[20];/*!< texte du temps en format texte*/
    SDL_Color couleurTxt;/*!< couleur de la texte*/
    TTF_Font* police;/*!< la police du texte*/
}Text;

/**
* @struct Time
* @brief struct for Time
*/

typedef struct
{
    int tempsdebut;/*!<temps du debut */
    int mm; /*!< minute*/
    int ss;/*!< second*/
    Text temps;/*!< texte de temps*/
    
} Time;



void inittemps(Time *t);
void inittempsenig(Time *t);
void Timer(int *tempsdebut);
int initTexttime(Text* T);
int initTexttimeenig(Text* T);
int loadFonttime(Text* T, char* angelina);
void update_time(Time* T);
void update_timeenig(Time* T);
void displaytime(Time T,SDL_Surface *screen);
void freeTexttime(Text T);


#endif
