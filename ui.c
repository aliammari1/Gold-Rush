/* SPDX-License-Identifier: Zlib */
#include "core.h"

void initBackground(Background *background)
{
  static Mix_Music *music = NULL;

  background->displayPosition.x = 0;
  background->displayPosition.y = 0;

  background->camera.x = 0;
  background->camera.y = 0;
  background->camera.w = 1280;
  background->camera.h = 419;

  // image
  background->backgroundImage = IMG_Load("assets/background_projet.png");
  if (background->backgroundImage == NULL)
  {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
  }

  // Audio already initialized in main.c
  if (music != NULL)
  {
    Mix_FreeMusic(music);
  }
  music = Mix_LoadMUS("assets/musique.mp3");
  if (music != NULL)
  {
    Mix_PlayMusic(music, -1);
  }
  Mix_AllocateChannels(10);
  Mix_VolumeMusic(MIX_MAX_VOLUME);

  // clouds
  background->cloudImage = IMG_Load("assets/cloud.png");
  background->cloudPosition.x = -1280;
  background->cloudPosition.y = -150;
  background->cloudPosition.w = background->cloudImage->w;
  background->cloudPosition.h = background->cloudImage->h;
}

void renderBackground(Background *background, SDL_Surface *screen)
{
  SDL_BlitSurface(background->backgroundImage, &(background->camera), screen, &(background->displayPosition));
}

void freeBackground(Background *background)
{
  SDL_FreeSurface(background->backgroundImage);
}

void updateCamera(Background *background, bool inputs[], int movementStep)
{
  // Move right
  if (inputs[0])
  {
    background->camera.x += movementStep;
  }
  // Move left
  if (inputs[1])
  {
    background->camera.x -= movementStep;
    if (background->camera.x < 0)
    {
      background->camera.x = 0;
    }
  }
  // Move up
  if (inputs[2])
  {
    if (background->camera.y > 0)
      background->camera.y -= movementStep;
  }
  // Move down
  if (inputs[3])
  {
    if (background->camera.y < 838 - 336)
      background->camera.y += movementStep;
  }
}

void animateClouds(Background *background, SDL_Surface *screen)
{
  background->cloudPosition.x -= 10;
  background->cloudPosition.y = background->displayPosition.y - 130;
  if (background->cloudPosition.x == -5000)
    background->cloudPosition.x = -1000;
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
SDL_Color getPixelColor(SDL_Surface *surface, int x, int y)
{
  SDL_Color color;
  Uint32 col = 0;
  char *pPosition = (char *)surface->pixels;
  pPosition += (surface->pitch * y);
  pPosition += (surface->format->BytesPerPixel * x);
  memcpy(&col, pPosition, surface->format->BytesPerPixel);
  SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
  return (color);
}
int checkPixelCollision(Player *player, SDL_Surface *collisionMask)
{
  SDL_Color pixel1, pixel2;

  pixel1 = getPixelColor(collisionMask, player->position.x, player->position.y);
  pixel2 = getPixelColor(collisionMask, player->position.x, player->position.y);

  if ((pixel2.r == 0) && (pixel2.b == 0) && (pixel2.g == 0))
    return 1;
  else if ((pixel1.r == 0) && (pixel1.b == 0) && (pixel1.g == 0))
    return 2;
  else
    return 0;
}

// partage d'ecran
// init left half of the screen
void initSplitScreenLeft(Background *background, Player *player)
{
  background->displayPosition.x = 0;
  background->displayPosition.y = 0;
  background->displayPosition.w = 1280 / 2;
  background->displayPosition.h = 336;
  background->camera.x = player->position.x;
  background->camera.y = (336 - 336) / 2;
  background->camera.w = 1280 / 2;
  background->camera.h = 336;
  background->backgroundImage = IMG_Load("assets/bg.png");
  if (background->backgroundImage == NULL)
  {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
  }
}

// init right half of the screen
void initSplitScreenRight(Background *background, Player *player)
{
  background->displayPosition.x = 1280 / 2;
  background->displayPosition.y = 0;
  background->displayPosition.w = 1280 / 2;
  background->displayPosition.h = 336;

  background->camera.x = player->position.x;
  background->camera.y = 0;
  background->camera.w = 1280 / 2;
  background->camera.h = 336;
  background->backgroundImage = IMG_Load("assets/bg.png");
  if (background->backgroundImage == NULL)
  {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
  }
}

// render split screen
void renderSplitScreen(Background *background, SDL_Surface *screen)
{
  SDL_BlitSurface(background->backgroundImage, &(background->camera), screen, &(background->displayPosition));
}
