#include "header.h"
/**
* @file fct.c
* @brief Testing Program.
* @author rayen
* @version 1
* @date Apr 21, 2022
*
* Testing program for the ennemy
*
*/

/**
* @brief To initialize the Ennemi .
* @param e the ennemi
* @return Nothing
*/
void initEnnemi(Ennemi*e)
{
	e->img = IMG_Load("e.png");
	e->pos1.x =300;
	e->pos1.y = 200;
	e->pos2.x=300;
	e->pos2.y=230;
	e->pos2.w=75;
	e->pos2.h=230;
	e->dir=0;
	e->state=FOLLOWING;
}
/**
* @brief To pin up the Ennemi on the screen .
* @param e the ennemi
* @param screen for the screen 
* @return Nothing
*/
void afficherEnnemi(Ennemi e, SDL_Surface * screen)
{

SDL_BlitSurface(e.img,&e.pos2,screen,&e.pos1);
SDL_Flip(screen);

}
/**
* @brief To animate the Ennemi .
* @param e the ennemi 
* @return Nothing
*/
void animerEnnemi( Ennemi * e)
{
e->pos2.y=(e->dir)*(e->pos2.h);
if(e->pos2.x==e->img->w-e->pos2.w)
{
e->pos2.x=0;
}else
{
e->pos2.x=e->pos2.x+e->pos2.w;
}

}
/**
* @brief To change an integer from 1 to 0 and from 0 to 1 .
* @param x random integer 
* @return integer
*/
int change_dirrec(int x)
{
if(x==0)
{x=1;
}else
x=0;

return(x);
}
/**
* @brief To keep the Ennemi moveing .
* @param e the ennemi
* @return Nothing
*/

void deplacer( Ennemi * e)
{
if((e->pos1.x>1200)||(e->pos1.x<10))
{
e->dir=change_dirrec(e->dir);
}
if(e->dir==0)
{
e->pos1.x+=5;
}else{
e->pos1.x-=5;
}
}

/**
* @brief To check if the ennemi and the personnage have bumped into each other if yes the fonction returns 1 if no it returns 0  .
* @param e the ennemi
* @param p for the personnage 
* @return integer
*/
int collisionBB( Personne p, Ennemi e)
{
int i;
if((p.pos.x+p.pos.w<e.pos1.x)||(p.pos.x>e.pos1.x+e.pos2.w)||(p.pos.y+p.pos.h<e.pos1.y)||(p.pos.y>e.pos1.y+e.pos2.h))
{
i=0;
}else
i=1;
return(i);
}

/**
* @brief To make the Ennemi move depending on it s state  .
* @param e the ennemi
* @param p personnage
* @return Nothing
*/
void deplacerIA( Ennemi * e,Personne p)
{

switch (e->state)
{
case WAITING:

animerEnnemi(e);
break;
case FOLLOWING:
if(e->pos1.x>p.pos.x)
e->dir=1;
else 
e->dir=0;
animerEnnemi(e);
deplacer(e);
	
	

break;

}


}
