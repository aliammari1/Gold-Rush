#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "farah.h"




void initBackground(Background *B)
{
  Mix_Music *music;

  B->PositionBg.x=0;
  B->PositionBg.y=0;

  

  B->camera.x=0;
  B->camera.y=0;
  B->camera.w = 1280;
  B->camera.h = 336;

 //image
  B->BgImg= IMG_Load("background projet.png"); //load mta3 el background
  if (B->BgImg == NULL)
  {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
  }

  

  //son
  if(SDL_Init(SDL_INIT_AUDIO)==-1)
  {
    printf("SDL_Init: %s\n", SDL_GetError());
  }
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)==-1)
  {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
  }
  music=Mix_LoadMUS("musique.mp3"); //el song eli fel jeux
  Mix_PlayMusic(music, -1);
  Mix_AllocateChannels(10);
  Mix_VolumeMusic(MIX_MAX_VOLUME);


   //clouds
   B->clouds = IMG_Load("cloud.png"); // annimation clouds mate5demech :D
   B->pos_clouds.x=-1280;
   B->pos_clouds.y=-150;
   B->pos_clouds.w=B->clouds->w;
   B->pos_clouds.h=B->clouds->h;

  }

void afficherBack (Background *B,SDL_Surface *screen)
{

  SDL_BlitSurface(B->BgImg,&(B->camera),screen,&(B->PositionBg));
  
}

void freeBackground(Background *B)
{
	SDL_FreeSurface(B->BgImg);
}



void scrolling(Background *B, bool b[],int pasmouv)
{
  //const int speed=5;
  if (b[0]) //right
  {
    
    //if(B->camera.x <2048-1280)
      B->camera.x += pasmouv;
    

   
  }
  if(b[1]) //left
  {
    
   
      B->camera.x -= pasmouv;
    

    if(B->camera.x  <= 0)
    {
      B->camera.x  = 0;
 
    }
  }
  if(b[2]) //up
  
  
  {
   if(B->camera.y>0) 
    B->camera.y  -= pasmouv;
   
    
    
  }
  if(b[3]) //down
  {
    if(B->camera.y<838-336)
    B->camera.y  += pasmouv;
    
  }
}


void animation_clouds(Background *B,SDL_Surface *screen) //animation clouds mate5demech hehe
{//k taswira tji bech toufa n3awdouha melowel
B->pos_clouds.x-=10;
B->pos_clouds.y=B->PositionBg.y-130;
if(B->pos_clouds.x==-5000) 
B->pos_clouds.x=-1000;
}


/*SDL_Color GetPixel(SDL_Surface *surface,int x,int y)
{
	SDL_Color color ;
	Uint32 col = 0 ;

	
	char* pPosition = ( char* ) surface->pixels ;

	
	pPosition += ( surface->pitch * y ) ;

	
	pPosition += ( surface->format->BytesPerPixel * x ) ;

	
	memcpy ( &col , pPosition , surface->format->BytesPerPixel ) ;

	
	SDL_GetRGB ( col , surface->format , &color.r , &color.g , &color.b ) ;
	return ( color ) ;
}

int collisionPP( Personne p, SDL_Surface * Masque)
{
SDL_Color col;

col=GetPixel(Masque,p.poscreen.x+100,p.poscreen.y+220);

  printf("%d    %d   /////////// \n",p.poscreen.x,p.poscreen.y+220 );
  printf("%d    %d   %d\n",col.r,col.b,col.g );

if ((col.r==0)&&(col.b==0)&&(col.g==0))
  return 1;//obstacle

else
return 0;


}*/
SDL_Color GetPixel(SDL_Surface *surface,int x,int y)
{
	SDL_Color color ;
	Uint32 col = 0 ;
	char* pPosition = ( char* ) surface->pixels ;
	pPosition += ( surface->pitch * y ) ;
	pPosition += ( surface->format->BytesPerPixel * x ) ;
	memcpy ( &col , pPosition , surface->format->BytesPerPixel ) ;
	SDL_GetRGB ( col , surface->format , &color.r , &color.g , &color.b ) ;
	return ( color ) ;
}
int collisionPP(Personne *p,SDL_Surface *Masque)
{
  SDL_Color col2,col22;

	col2=GetPixel(Masque,p->pos.x,p->pos.y);
	col22=GetPixel(Masque,p->pos.x,p->pos.y);

	if ((col22.r==0)&&(col22.b==0)&&(col22.g==0))
  	 return 1;
	else if ((col2.r==0)&&(col2.b==0)&&(col2.g==0))
 	 return 2;
	else
	 return 0;
  printf("%d    %d   /////////// \n",p->pos.x,p->pos.y );
  printf("%d    %d   %d\n",col2.r,col2.b,col2.g );
  printf("%d    %d   /////////// \n",p->pos.x,p->pos.y );
  printf("%d    %d   %d\n",col22.r,col22.b,col22.g );
}

//partage d'ecran
//init left half of the screen
void initpartage1(Background *B,Personne *p)
{
  B->PositionBg.x=0;
  B->PositionBg.y=0;
  B->PositionBg.w=1280/2;  
  B->PositionBg.h=336;
  B->camera.x=p->pos.x; //nrmlment 0 ama pos perso eli 3al issar deja yebda 0
  B->camera.y=(336-336)/2; //(imagebackground.h-screen.h)/2
  B->camera.w = 1280/2;  //screen.w/2   ye5ou chtar el ecran
  B->camera.h = 336;    //screen.h  3ordh el screen
B->BgImg= IMG_Load("bg.png");
  if (B->BgImg == NULL)
  {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
  }



}

//init right half of the screen
void initpartage2(Background *B1,Personne *p)
{
  B1->PositionBg.x=1280/2;
  B1->PositionBg.y=0;
  B1->PositionBg.w=1280/2;
  B1->PositionBg.h=336;


  

  B1->camera.x=p->pos.x-p->posinit.x;  //posinit fel struct te5ou awel position yebda biha el perso eli 3al imin
  B1->camera.y=0;
  B1->camera.w = 1280/2;  //screen.w/2   ye5ou chtar el ecran
  B1->camera.h = 336;     //screen.h 3ordh el ecran .... el tab eli tet7al lel affichage
B1->BgImg= IMG_Load("bg.png");
  if (B1->BgImg == NULL)
  {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
  }
}

//affichage
void afficherpartage(Background *B,SDL_Surface *screen)
{
SDL_BlitSurface(B->BgImg,&(B->camera),screen,&(B->PositionBg));
}



