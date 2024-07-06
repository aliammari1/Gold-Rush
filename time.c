#include "header.h"
/**
 * @file time.c
 * @brief Testing Program.
 * @author C lahmar
 * @version 1
 * @date Apr 20, 2022
 *
 * Testing program for minimap
 *
 */
/**
 * @brief compteur qui calcule le temps du debut de joueur par le ms.
 * @param tempsdebut debut de temps
 * @return Nothing
 */
void Timer(int *tempsdebut)
{

    if (SDL_GetTicks() - *tempsdebut >= 1000)
    {
        *tempsdebut = SDL_GetTicks();
    }
}
/**
 * @brief initialisation du temps .
 * @param t temps du jeu
 * @return Nothing
 */

void inittemps(Time *t)
{
    int test;
    t->tempsdebut = SDL_GetTicks();
    t->mm = 0;
    t->ss = 0;
    test = initTexttime(&t->temps);
}
/**
 * @brief initialisation du temps de l'enigme.
 * @param t temps du jeu
 * @return Nothing
 */

void inittempsenig(Time *t)
{
    int test;
    t->tempsdebut = 16000;
    t->mm = 0;
    t->ss = 0;
    test = initTexttimeenig(&t->temps);
}
/**
 * @brief initialisation du texte du temps avec un couleur blanc et une position dans le screen x=850 et y=20.
 * @param T text du temps
 * @return Nothing
 */

int initTexttime(Text *T)
{
    int testload;
    T->couleurTxt.r = 255;
    T->couleurTxt.g = 255;
    T->couleurTxt.b = 255;

    strcpy(T->txt, "");
    T->positionText.x = 850;
    T->positionText.y = 20;
    testload = loadFonttime(T, "angelina.TTF");
    T->textSurface = NULL;
    return testload;
}
/**
 * @brief initialisation du texte du temps de l'enigme.
 * @param T text du temps de l'enigme
 * @return Nothing
 */
int initTexttimeenig(Text *T)
{
    int testload;
    T->couleurTxt.r = 255;
    T->couleurTxt.g = 255;
    T->couleurTxt.b = 255;

    strcpy(T->txt, "");
    T->positionText.x = 0;
    T->positionText.y = 0;
    testload = loadFonttime(T, "angelina.TTF");
    T->textSurface = NULL;
    return testload;
}
/**
 * @brief charger le font du text du temps.
 * @param T text du temps
 * @param path le nom du font
 * @return Nothing
 */
int loadFonttime(Text *T, char *path)
{
    if (TTF_Init() == -1)
    {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return -1;
    }
    T->police = TTF_OpenFont(path, 60);
    if (T->police == NULL)
    {
        printf("Unable to load Font: %s\n", SDL_GetError());
        return (-1);
    }
    return (0);
}
/**
 * @brief update le temps du jeu.
 * @param T text du temps
 * @return Nothing
 */
void update_time(Time *T)
{
    int ts;
    Timer(&T->tempsdebut);
    ts = T->tempsdebut / 1000;
    T->mm = ts / 60;
    T->ss = ts % 60;
    if (T->mm < 10 && T->ss < 10)
        sprintf(T->temps.txt, "*** time :0%d:0%d  ***", T->mm, T->ss);
    else if (T->mm < 10 && T->ss > 10)
        sprintf(T->temps.txt, "*** time :0%d:%d  ***", T->mm, T->ss);
    else if (T->mm > 10 && T->ss < 10)
        sprintf(T->temps.txt, "*** time :%d:0%d  ***", T->mm, T->ss);

    T->temps.textSurface = TTF_RenderText_Solid(T->temps.police, T->temps.txt, T->temps.couleurTxt);
}
/**
 * @brief update le temps du l'enigme.
 * @param T text du temps
 * @return Nothing
 */
void update_timeenig(Time *T)
{
    int ts;

    Timer(&T->tempsdebut);
    ts = T->tempsdebut / 1000;
    T->mm = ts / 60;
    T->ss = ts % 60;
    if (T->mm < 10 && T->ss < 10)
        sprintf(T->temps.txt, "*** time :0%d:0%d  ***", T->mm, T->ss);
    else if (T->mm < 10 && T->ss > 10)
        sprintf(T->temps.txt, "*** time :0%d:%d  ***", T->mm, T->ss);
    else if (T->mm > 10 && T->ss < 10)
        sprintf(T->temps.txt, "*** time :%d:0%d  ***", T->mm, T->ss);
    else
        sprintf(T->temps.txt, "*** time :%d:%d  ***", T->mm, T->ss);
    T->temps.textSurface = TTF_RenderText_Solid(T->temps.police, T->temps.txt, T->temps.couleurTxt);
}
/**
 * @brief afficher le text du temps.
 * @param T text du temps
 * @param screen l'ecran
 * @return Nothing
 */
void displaytime(Time T, SDL_Surface *screen)
{
    SDL_BlitSurface(T.temps.textSurface, NULL, screen, &(T.temps.positionText));
}
/**
 * @brief liberer le text du temsp.
 * @param T text du temps
 * @return Nothing
 */
void freeTexttime(Text T)
{
    TTF_CloseFont(T.police);
    TTF_Quit();
}
