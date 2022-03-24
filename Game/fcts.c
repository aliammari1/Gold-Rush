#include "header.h"


void initImage(image* im, float x, float y, char path[])
{
	im->img = IMG_Load(path);
	im->pos1.x = x;
	im->pos1.y = y;
	im->pos1.w = im->img->w;
	im->pos1.h = im->img->h;

}
void initText(text *A)
{
A->position.x=500;
A->position.y=300;

A->textColor.r=255;
A->textColor.g=255;
A->textColor.b=255;

A->font =TTF_OpenFont("MAtRixOiD.ttf",60);
}

void freeText(text A)
{
    SDL_FreeSurface(A.surfaceTexte);
}
void displayText(text t, SDL_Surface *screen)
{
t.surfaceTexte=TTF_RenderText_Blended(t.font,"WORK IN PROGRESS",t.textColor);
SDL_BlitSurface(t.surfaceTexte,NULL,screen,&t.position);
}
