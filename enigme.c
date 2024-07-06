#include "header.h"

#include <time.h>

/**
 * @file enigme.c
 * @brief Testing Program.
 * @author yassine
 * @version 1
 * @date Apr 26, 2022
 *
 * Testing program for enigme *
 */

/**
 * @brief To initialize the enigme .
 * @param e the enigme
 * @return Nothing
 */

void init_enigmes(enigme *e)
{

    int nbligne = 0;

    char question[100];
    char reponse1[100];
    char reponse2[100];
    char reponse3[100];
    int reponse;

    FILE *f = NULL;
    f = fopen("assets/questionsans", "r"); // ouvrir
    if (f != NULL)
    {

        while (fscanf(f, "%s %s %s %s %d\n", question, reponse1, reponse2, reponse3, &reponse) != EOF)
        {
            nbligne++;
        }
        fclose(f);
    } ////tkharajlk nbr de lignes fl fichier
    // printf("%d",nbligne);

    srand(time(0));                    // nbr alea ytbdl kol mara
    int alea = rand() % (2 * nbligne); // taaatik nbr aleatoire

    int check = 0;

    /// gener nombre aleatoire

    f = fopen("assets/questionsans", "r");
    if (f != NULL)
    {

        while (fscanf(f, "%s %s %s %s %d\n", e->question, e->reponse1, e->reponse2, e->reponse3, &e->reponse) != EOF)
        {
            check++;
            if (check == alea)
            {
                break;
            }
        }
        fclose(f);
    }

    // lel affichage
    e->positionquestion.x = 180;
    e->positionquestion.y = 50;

    e->positionreponse1.x = 500;
    e->positionreponse1.y = 150;

    e->positionreponse2.x = 500;
    e->positionreponse2.y = 250;

    e->positionreponse3.x = 500;
    e->positionreponse3.y = 350;

    TTF_Font *police = NULL;
    police = TTF_OpenFont("assets/Trajan Pro.ttf", 30);

    TTF_Font *police1 = NULL;
    police1 = TTF_OpenFont("assets/Trajan Pro.ttf", 32);

    SDL_Color white = {0, 255, 255}; // black
    SDL_Color red = {0, 255, 255};

    e->surfacequestion = TTF_RenderText_Blended(police1, e->question, red);
    e->surfacereponse1 = TTF_RenderText_Blended(police, e->reponse1, white);
    e->surfacereponse2 = TTF_RenderText_Blended(police, e->reponse2, white);
    e->surfacereponse3 = TTF_RenderText_Blended(police, e->reponse3, white);
}

/**
 * @brief To animate the enigme .
 * @param e the enigme
 * @param pos_sprite the position of sprite
 * @param j direction
 * @return Nothing
 */
void animer(enigme *e, SDL_Rect *pos_sprite, int j)
{
    pos_sprite->x = j * pos_sprite->w;
}

/**
 * @brief To show the enigme on the screen
 * @param e the enigme
 * @param screen the screen
 * @return Nothing
 */

void afficherenigme(enigme e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.surfacequestion, NULL, screen, &e.positionquestion);
    SDL_BlitSurface(e.surfacereponse1, NULL, screen, &e.positionreponse1);
    SDL_BlitSurface(e.surfacereponse2, NULL, screen, &e.positionreponse2);
    SDL_BlitSurface(e.surfacereponse3, NULL, screen, &e.positionreponse3);
    SDL_Flip(screen);
}

/*

void sauvegarder(personne p,background b,char *nomfichier){

background b;
personne p ;

FILE *f=NULL;
f=fopen("chargement","w");
if(f!=NULL){
fprintf(f,"%s %s %s %d\n",b.img,b.scroll,b.position,p.position)
fclose(f);
}





}





int charger(personne *p,background *b,char *nomfichier){
FILE *f=NULL;
f=fopen("chargement","r");
if(f!=NULL){
fscanf(f,"%s %s %s %d\n",b.img,b.scroll,b.position,p.position)
fclose(f);
}
return 1;






}
*/
