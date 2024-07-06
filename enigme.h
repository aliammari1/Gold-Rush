#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
/**
 * @file enigme.h
 * @brief Testing Program.
 * @author yassine
 * @version 1
 * @date Apr 26, 2022
 *
 * Testing program for enigme  *
 */

/**
 * @struct enigme
 * @brief struct for enigme
 */

typedef struct enigme
{
    char question[100];           /*!< question en format de chaine de carectere*/
    char reponse1[100];           /*!< reponse1 en format de chaine de carectere*/
    char reponse2[100];           /*!< reponse2 en format de chaine de carectere*/
    char reponse3[100];           /*!< reponse3 en format de chaine de carectere*/
    int reponse;                  /*!< numero de reponse correcte*/
    SDL_Surface *surfacequestion; /*!< question en format d'image*/

    SDL_Surface *surfacereponse1; /*!< reponse1 en format d'image*/

    SDL_Surface *surfacereponse2; /*!< reponse2 en format d'image*/

    SDL_Surface *surfacereponse3; /*!< reponse3 en format d'image*/

    SDL_Rect positionquestion; /*!< postion de question par rapport a l'ecran*/

    SDL_Rect positionreponse1; /*!< postion de reponse1 par rapport a l'ecran*/

    SDL_Rect positionreponse2; /*!< postion de reponse2 par rapport a l'ecran*/

    SDL_Rect positionreponse3; /*!< postion de reponse3 par rapport a l'ecran*/

} enigme;
int enigme_jeu();
void afficherenigme(enigme e, SDL_Surface *screen);
void init_enigmes(enigme *e);
void animer(enigme *e, SDL_Rect *pos_sprite, int j);

// int charger(personne *p,background *b,char *nomfichier);
// void sauvegarder(personne p,background b,char *nomfichier);
