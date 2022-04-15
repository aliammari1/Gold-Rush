#include"header.h"
int main()
{
SDL_Surface *screen=NULL;
SDL_Surface *backg;
Personne p;
SDL_Event event;
int continuer=1;
Uint32 t_prev=0,dt=0;
if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)!=0)
{
printf("Erreur: %s\n",SDL_GetError());
return 1;
}
screen=SDL_SetVideoMode(833,542,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
backg=IMG_Load("background.jpg");
initPerso(&p);
while(continuer)
{
SDL_BlitSurface(backg,NULL,screen,NULL);
t_prev=SDL_GetTicks();
SDL_PollEvent(&event);
switch(event.type)
{
case SDL_QUIT:
continuer=0;
break;
case SDL_KEYDOWN:
switch(event.key.keysym.sym)
{
case SDLK_ESCAPE:
continuer=0;
break;
case SDLK_RIGHT:
p.vX+=0.01;
p.d=0;
p.direction=1;
break;
case SDLK_LEFT:
p.vX+=0.01;
p.d=1;
p.direction=3;
break;
case SDLK_UP:
p.up=1;
if(p.d==0)
p.direction=4;
if(p.d==1)
p.direction=5;
break;
}
break;
case SDL_KEYUP:
switch(event.key.keysym.sym)
{
case SDLK_RIGHT:
p.vX-=0.005;
p.direction=0;
break;
case SDLK_LEFT:
p.vX-=0.005;
p.direction=2;
break;
case SDLK_UP:
if(p.up==0)
{
if(p.d==0)
p.direction=0;
if(p.d==1)
p.direction=2;
}
break;
}
break;
}
p.vX-=0.001;
deplacerPerso(&p,dt);

if(p.up==1)
{
if((p.pos_relative.x)<=20)
saut(&p);
else
{
p.pos.y+=-15;
p.pos_relative.x=-20;
p.up=0;
}
}
printf("acc%f\n",p.vX);
printf("pos%d\n",p.pos.y);
animerPerso(&p);
afficherPerso(p,screen);
SDL_Flip(screen);
dt=SDL_GetTicks()-t_prev;
SDL_Delay(100);
}
SDL_Quit();
return 0;
}
