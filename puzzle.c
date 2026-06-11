/* SPDX-License-Identifier: Zlib */
#include "core.h"

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
 * @brief To initialize the puzzle.
 * @param puzzle the Puzzle structure
 * @return Nothing
 */

void initPuzzle(Puzzle *puzzle)
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

        while (fscanf(f, "%s %s %s %s %d\n", question, reponse1, reponse2, reponse3, &reponse) != EOF)
        {
            check++;
            if (check == alea)
            {
                break;
            }
        }
        fclose(f);
    }

    /* Store question and answers in puzzle structure */
    strncpy(puzzle->questionText, question, sizeof(puzzle->questionText) - 1);
    strncpy(puzzle->answer1, reponse1, sizeof(puzzle->answer1) - 1);
    strncpy(puzzle->answer2, reponse2, sizeof(puzzle->answer2) - 1);
    strncpy(puzzle->answer3, reponse3, sizeof(puzzle->answer3) - 1);
    puzzle->correctAnswer = reponse;

    /* Set display positions */
    puzzle->questionPosition.x = 180;
    puzzle->questionPosition.y = 50;

    puzzle->answer1Position.x = 500;
    puzzle->answer1Position.y = 150;

    puzzle->answer2Position.x = 500;
    puzzle->answer2Position.y = 250;

    puzzle->answer3Position.x = 500;
    puzzle->answer3Position.y = 350;

    TTF_Font *police = NULL;
    police = TTF_OpenFont("assets/Trajan Pro.ttf", 30);

    TTF_Font *police1 = NULL;
    police1 = TTF_OpenFont("assets/Trajan Pro.ttf", 32);

    SDL_Color white = {0, 255, 255}; /* black */
    SDL_Color red = {0, 255, 255};

    puzzle->questionSurface = TTF_RenderText_Blended(police1, question, red);
    puzzle->answer1Surface = TTF_RenderText_Blended(police, reponse1, white);
    puzzle->answer2Surface = TTF_RenderText_Blended(police, reponse2, white);
    puzzle->answer3Surface = TTF_RenderText_Blended(police, reponse3, white);
}

/**
 * @brief To animate the enigme .
 * @param e the enigme
 * @param pos_sprite the position of sprite
 * @param j direction
 * @return Nothing
 */
void animatePuzzle(Puzzle *puzzle, SDL_Rect *spritePos, int frameIdx)
{
    spritePos->x = frameIdx * spritePos->w;
}

/**
 * @brief To show the enigme on the screen
 * @param e the enigme
 * @param screen the screen
 * @return Nothing
 */

void renderPuzzle(Puzzle puzzle, SDL_Surface *screen)
{
    SDL_BlitSurface(puzzle.questionSurface, NULL, screen, &puzzle.questionPosition);
    SDL_BlitSurface(puzzle.answer1Surface, NULL, screen, &puzzle.answer1Position);
    SDL_BlitSurface(puzzle.answer2Surface, NULL, screen, &puzzle.answer2Position);
    SDL_BlitSurface(puzzle.answer3Surface, NULL, screen, &puzzle.answer3Position);
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
