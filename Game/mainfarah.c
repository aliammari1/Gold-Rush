#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include<SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "farah.h"

int main()
{
    Background B;
    Personne p;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen=NULL;
   
    screen = SDL_SetVideoMode(1280, 336, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_Surface * Masque = SDL_LoadBMP("backgroundmasque.bmp");
    if(screen==NULL)
    {
      printf("unable to set video mode: %s /n",SDL_GetError());
    }

    bool gamerunning = 1;
    const int FPS = 30;
    const int speed = 5;
    Uint32 start;
    int direction;
    int pasmouv=10;
    int co;

    initBackground(&B);
    initp(&p);

    bool b[4] = {0,0,0,0};
    while(gamerunning) {
        start = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    gamerunning = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP :
                            b[2]=1;
                            break;
                        case SDLK_RIGHT:
                            b[0] = 1;
                            break;
                        case SDLK_LEFT:
                            b[1] = 1;
                            break;
                        case SDLK_DOWN:
                            b[3]=1;
                            break;
                        case SDLK_ESCAPE:
                            gamerunning = 0;
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP :
                            b[2]=0;
                            break;
                        case SDLK_RIGHT:
                            b[0] = 0;
                            break;
                        case SDLK_LEFT:
                            b[1] = 0;
                            
                            
                            break;
                        case SDLK_DOWN:
                            b[3]=0;
                            break;

                    }
                    break;
            }
        }
        
        //perso
        afficherperso(&p,screen);
        SDL_Flip(screen);

        //backg
      
        scrolling(&B,b,pasmouv);
        afficherBack (&B,screen);
        animation_clouds(&B,screen);
        
        
        co=collisionPP(&p,Masque);

        if((co==1)||(co==2))

         gamerunning=0;
    

        SDL_Flip(screen);
        if(1000/FPS > SDL_GetTicks()-start)
        {
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
    }
    freeBackground(&B);
    SDL_Quit();
    return 0;
}
