#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "header.h"
int minitache(void)
{


TTF_Init();
TTF_Font *police = NULL;
police = TTF_OpenFont("alger.TTF",90);
SDL_Color couleur = {52,201,36};
SDL_Color couleur_r= {187,11,11};
SDL_Color couleur_n = {0,0,0};
SDL_Surface *fond_n;
SDL_Rect pos_n;
pos_n.x=480;
pos_n.y=400;
int check=0;
Casee c,c_o;
int T[6][7];
int done=1,j,i,nb_coups=0;
SDL_Surface *screen;
SDL_Surface *fond;
SDL_Surface *jaune;
SDL_Surface *rouge;
SDL_Rect pos_ecran;
SDL_Rect pos_rouge;
SDL_Rect pos;
SDL_Surface *j_g;
SDL_Surface *pc_g;
SDL_Surface *gameover;
j_g= TTF_RenderText_Blended(police,"YOU WON",couleur);
pc_g= TTF_RenderText_Blended(police,"YOU LOST",couleur_r);
gameover= TTF_RenderText_Blended(police,"Game Over",couleur_n);
pos.x=500;
pos.y=400;
SDL_Event event;
fond=IMG_Load("puissance.png");
fond_n=IMG_Load("fond.png");
jaune=IMG_Load("jaune.png");
rouge=IMG_Load("rouge.png");
pos_ecran.x=150;
pos_ecran.y=0;
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
screen=SDL_SetVideoMode(1250,800,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
SDL_BlitSurface(fond,NULL,screen,&pos_ecran);
SDL_Flip(screen);
for (i=0;i<6;i++)
{
for (j=0;j<7;j++)
T[i][j]=0;
}
while (done==1)
{
while (SDL_PollEvent(&event))
{
switch (event.type)
{
case SDL_MOUSEBUTTONUP:
if ((check==0)&&(nb_coups<21))
{c=afficher_jeton(screen,rouge,event,T);
T[c.l][c.c]=1;
nb_coups++;
check=checkk(T);
if (nb_coups==21)
{SDL_BlitSurface(fond_n,NULL,screen,&pos_n);
SDL_Flip(screen);
SDL_BlitSurface(gameover,NULL,screen,&pos);
SDL_Flip(screen);
}
if (check==1)
{SDL_BlitSurface(fond_n,NULL,screen,&pos_n);
SDL_Flip(screen);
SDL_BlitSurface(j_g,NULL,screen,&pos);
SDL_Flip(screen);}
if (check==2)
{SDL_BlitSurface(fond_n,NULL,screen,&pos_n);
SDL_Flip(screen);
SDL_BlitSurface(pc_g,NULL,screen,&pos);
SDL_Flip(screen);}
if ((nb_coups<22)&&(check==0))
{c_o=IA(T);
T[c_o.l][c_o.c]=2;
afficher_jaune (screen,jaune,c_o);
check=checkk(T);
if (nb_coups==21)
{SDL_BlitSurface(fond_n,NULL,screen,&pos_n);
SDL_Flip(screen);
SDL_BlitSurface(gameover,NULL,screen,&pos);
SDL_Flip(screen);
}
if (check==1)
{SDL_BlitSurface(fond_n,NULL,screen,&pos_n);
SDL_Flip(screen);
SDL_BlitSurface(j_g,NULL,screen,&pos);
SDL_Flip(screen);}
if (check==2)
{SDL_BlitSurface(fond_n,NULL,screen,&pos_n);
SDL_Flip(screen);
SDL_BlitSurface(pc_g,NULL,screen,&pos);
SDL_Flip(screen);}}}
break;
case SDL_QUIT :
done=0;

case SDL_KEYDOWN :
if (event.key.keysym.sym==SDLK_r)
{
done=0;}
break;
break;
}}}
return 0;}
