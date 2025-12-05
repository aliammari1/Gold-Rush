#include "core.h"
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

void initGameTimer(GameTimer *t)
{
    int test;
    t->startTime = SDL_GetTicks();
    t->minutes = 0;
    t->seconds = 0;
    test = initTimerDisplay(&t->display);
}
/**
 * @brief initialisation du temps de l'enigme.
 * @param t temps du jeu
 * @return Nothing
 */

void initPuzzleTimer(GameTimer *t)
{
    int test;
    t->startTime = 16000;
    t->minutes = 0;
    t->seconds = 0;
    test = initPuzzleDisplay(&t->display);
}
/**
 * @brief initialisation du texte du temps avec un couleur blanc et une position dans le screen x=850 et y=20.
 * @param T text du temps
 * @return Nothing
 */

int initTimerDisplay(TextDisplay *T)
{
    int testload;
    T->textColor.r = 255;
    T->textColor.g = 255;
    T->textColor.b = 255;

    strcpy(T->textSurface, "");
    T->textPosition.x = 850;
    T->textPosition.y = 20;
    testload = loadTimerFont(T, "assets/angelina.TTF");
    T->textSurface = NULL;
    return testload;
}
/**
 * @brief initialisation du texte du temps de l'enigme.
 * @param T text du temps de l'enigme
 * @return Nothing
 */
int initPuzzleDisplay(TextDisplay *T)
{
    int testload;
    T->textColor.r = 255;
    T->textColor.g = 255;
    T->textColor.b = 255;

    strcpy(T->textSurface, "");
    T->textPosition.x = 0;
    T->textPosition.y = 0;
    testload = loadTimerFont(T, "assets/angelina.TTF");
    T->textSurface = NULL;
    return testload;
}
/**
 * @brief charger le font du text du temps.
 * @param T text du temps
 * @param path le nom du font
 * @return Nothing
 */
int loadTimerFont(TextDisplay *T, char *path)
{
    /* TTF already initialized in main.c */
    T->font = TTF_OpenFont(path, 60);
    if (T->font == NULL)
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
void updateGameTime(GameTimer *T)
{
    int ts;
    Timer(&T->startTime);
    ts = T->startTime / 1000;
    T->minutes = ts / 60;
    T->seconds = ts % 60;
    
    /* Free previous surface to avoid memory leak */
    if (T->display.textSurface != NULL)
    {
        SDL_FreeSurface(T->display.textSurface);
    }
    
    if (T->minutes < 10 && T->seconds < 10)
        sprintf(T->display.textSurface, "*** time :0%d:0%d  ***", T->minutes, T->seconds);
    else if (T->minutes < 10 && T->seconds >= 10)
        sprintf(T->display.textSurface, "*** time :0%d:%d  ***", T->minutes, T->seconds);
    else if (T->minutes >= 10 && T->seconds < 10)
        sprintf(T->display.textSurface, "*** time :%d:0%d  ***", T->minutes, T->seconds);
    else
        sprintf(T->display.textSurface, "*** time :%d:%d  ***", T->minutes, T->seconds);

    T->display.textSurface = TTF_RenderText_Solid(T->display.font, T->display.textSurface, T->display.textColor);
}
/**
 * @brief update le temps du l'enigme.
 * @param T text du temps
 * @return Nothing
 */
void updatePuzzleTime(GameTimer *T)
{
    int ts;

    Timer(&T->startTime);
    ts = T->startTime / 1000;
    T->minutes = ts / 60;
    T->seconds = ts % 60;
    
    /* Free previous surface to avoid memory leak */
    if (T->display.textSurface != NULL)
    {
        SDL_FreeSurface(T->display.textSurface);
    }
    
    if (T->minutes < 10 && T->seconds < 10)
        sprintf(T->display.textSurface, "*** time :0%d:0%d  ***", T->minutes, T->seconds);
    else if (T->minutes < 10 && T->seconds >= 10)
        sprintf(T->display.textSurface, "*** time :0%d:%d  ***", T->minutes, T->seconds);
    else if (T->minutes >= 10 && T->seconds < 10)
        sprintf(T->display.textSurface, "*** time :%d:0%d  ***", T->minutes, T->seconds);
    else
        sprintf(T->display.textSurface, "*** time :%d:%d  ***", T->minutes, T->seconds);
    T->display.textSurface = TTF_RenderText_Solid(T->display.font, T->display.textSurface, T->display.textColor);
}
/**
 * @brief afficher le text du temps.
 * @param T text du temps
 * @param screen l'ecran
 * @return Nothing
 */
void renderTimer(GameTimer T, SDL_Surface *screen)
{
    SDL_BlitSurface(T.display.textSurface, NULL, screen, &(T.display.textPosition));
}
/**
 * @brief liberer le text du temsp.
 * @param T text du temps
 * @return Nothing
 */
void freeTimerDisplay(TextDisplay T)
{
    TTF_CloseFont(T.font);
    TTF_Quit();
}
