#ifndef FONCTIONS_H_
#define FONCTIONS_H_
typedef struct 
{
int c;
int l;
}Casee ;
typedef struct 
{
SDL_Surface *img;
SDL_Surface *img_2;
SDL_Surface *img_3;
SDL_Surface *img_4;
SDL_Rect postion;
int vitesse;
}Personnem;
typedef struct
{
SDL_Surface *img;
SDL_Surface *img_2;
SDL_Surface *img_3;
SDL_Surface *img_4;
SDL_Rect postion;
}Ennemim;
typedef struct
{
SDL_Surface *img;
SDL_Rect postion;
}Backgroundm;
typedef struct
{
SDL_Surface *img_map;
SDL_Rect pos_map;
SDL_Surface *img_joueur;
SDL_Rect pos_joueur;
}minimapm;
typedef struct
{
SDL_Surface *img;
SDL_Rect postion;
int reponse;
}enigmem;
void affichertemp (int *temps,SDL_Surface *screen,SDL_Surface *fond,TTF_Font *police);
void initmap(minimapm *m); 
void afficherminimap(minimapm m,SDL_Surface *screen); 
SDL_Rect MAJMinimap (SDL_Rect posJoueur,int redemensionement);
void afficherminimap (minimapm m,SDL_Surface *screen);
Casee afficher_jeton(SDL_Surface *screen,SDL_Surface *rouge,SDL_Event event,int t[6][7]);
Casee IA (int t [6][7]);
void afficher_jaune (SDL_Surface *screen,SDL_Surface *jaune,Casee c);
int checkk (int t[7][7]);
#endif
