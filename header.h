#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string.h>
#include <time.h>
#define VIT 5
#define MAX_VIT 10

// game
int integration();

typedef enum STATE STATE;
enum STATE
{
	WAITING,
	FOLLOWING
};

typedef struct
{
	SDL_Rect pos;			 /*!< postion de personnage par rapport le background. */
	SDL_Rect pos_relative;	 /*!< position de personnage par rapport une repere relatif. */
	SDL_Surface *img[6][12]; /*!< Tableau des images */
	float vX;				 /*!< acceleration. */
	int direction;			 /*!< direction et etat de l'image. */
	int frame;				 /*!< une sequence des images */
	int d;					 /*!< dernier direction Gauche ou Droite */
	int up;					 /*!< le personnage fait une saut ou non */
} Personne;

typedef struct
{
	SDL_Surface *textSurface; /*!<texte du temps en format image*/
	SDL_Rect positionText;	  /*!< position  de la texte du temps*/
	char txt[20];			  /*!< texte du temps en format texte*/
	SDL_Color couleurTxt;	  /*!< couleur de la texte*/
	TTF_Font *police;		  /*!< la police du texte*/
} Text;

/**
 * @struct Time
 * @brief struct for Time
 */

typedef struct
{
	int tempsdebut; /*!<temps du debut */
	int mm;			/*!< minute*/
	int ss;			/*!< second*/
	Text temps;		/*!< texte de temps*/

} Time;

typedef struct
{
	SDL_Surface *img;
	SDL_Rect pos;
} image;

typedef struct
{
	SDL_Surface *BgImg;
	SDL_Rect PositionBg;
	SDL_Rect camera;
	SDL_Rect pos_clouds;
	SDL_Surface *clouds;
} Background;

typedef struct
{
	int dir;		  /*!< direction de l ennemi si dir=0=droit si dir=1=gauche*/
	SDL_Rect pos1;	  /*!< position du l ennemi dans sur l ecran*/
	SDL_Rect pos2;	  /*!< position de l ennemi par rapport au spritesheet*/
	SDL_Surface *img; /*!< spritesheet ennemi*/
	STATE state;	  /*!< l etat de l ennemi*/
} Ennemi;

typedef struct
{
	SDL_Surface *map;		 /*!< image de minimap*/
	SDL_Rect pos_map;		 /*!< position de la minimap*/
	SDL_Surface *mini_perso; /*!< image du minipersonnage*/
	SDL_Rect perso_pos_map;	 /*!< position de la minipersonnage*/

} map;

typedef struct enigme
{
	char question[100];			  /*!< question en format de chaine de carectere*/
	char reponse1[100];			  /*!< reponse1 en format de chaine de carectere*/
	char reponse2[100];			  /*!< reponse2 en format de chaine de carectere*/
	char reponse3[100];			  /*!< reponse3 en format de chaine de carectere*/
	int reponse;				  /*!< numero de reponse correcte*/
	SDL_Surface *surfacequestion; /*!< question en format d'image*/

	SDL_Surface *surfacereponse1; /*!< reponse1 en format d'image*/

	SDL_Surface *surfacereponse2; /*!< reponse2 en format d'image*/

	SDL_Surface *surfacereponse3; /*!< reponse3 en format d'image*/

	SDL_Rect positionquestion; /*!< postion de question par rapport a l'ecran*/

	SDL_Rect positionreponse1; /*!< postion de reponse1 par rapport a l'ecran*/

	SDL_Rect positionreponse2; /*!< postion de reponse2 par rapport a l'ecran*/

	SDL_Rect positionreponse3; /*!< postion de reponse3 par rapport a l'ecran*/

} enigme;

// perso
void choisir_perso(int *n, SDL_Surface *screen);
void initPerso(Personne *p);
void initPerso2(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screen);
void deplacerPerso(Personne *p, Uint32 dt);
void animerPerso(Personne *p);
void saut(Personne *p);
// temps
void inittemps(Time *t);
void inittempsenig(Time *t);
void Timer(int *tempsdebut);
int initTexttime(Text *T);
int initTexttimeenig(Text *T);
int loadFonttime(Text *T, char *angelina);
void update_time(Time *T);
void update_timeenig(Time *T);
void displaytime(Time T, SDL_Surface *screen);
void freeTexttime(Text T);
// enemy
void initEnnemi(Ennemi *e);
void afficherEnnemi(Ennemi e, SDL_Surface *screen);
void animerEnnemi(Ennemi *e);
void deplacer(Ennemi *e);
int collisionBB(Personne p, Ennemi e);
void deplacerIA(Ennemi *e, Personne p);
// map
void initialiser_map(map *m, SDL_Surface *screen);
void perso_map(map *m, Personne *p);
void affiche_map(map *m, SDL_Surface *screen, Personne *p);
void sauvegarder(int score, char nomjoueur[], char nomfichier[]);
void meilleur(char nomfichier[], int score, char nomjoueur[]);
// enigme
void enigme_jeu();
void afficherenigme(enigme e, SDL_Surface *screen);
void init_enigmes(enigme *e);
void animer(enigme *e, SDL_Rect *pos_sprite, int j);
// background

void initBackground(Background *B);
void freeBackground(Background *B);
void afficherBack(Background *B, SDL_Surface *screen);
void scrolling(Background *B, bool b[], int pasmouv);
void animation_clouds(Background *B, SDL_Surface *screen);
// SDL_Color GetPixel(SDL_Surface *surface,int x,int y);

int collisionPP(Personne *p, SDL_Surface *Masque);
// collisionPP(SDL_Surface *calque,SDL_Surface *perso,SDL_Rect posperso,SDL_Rect posmap);
SDL_Color GetPixel(SDL_Surface *surface, int x, int y);

// tache blanche

// void initpartage(Background *B,Background *B1,Personne *p1,Personne*p2);

void initpartage1(Background *B, Personne *p);
void initpartage2(Background *B1, Personne *p);
void afficherpartage(Background *B, SDL_Surface *screen);
// menu
typedef struct
{
	SDL_Surface *img[2];
	SDL_Rect pos;
	int frame;
} button;
typedef struct
{
	SDL_Surface *img[3];
	SDL_Rect pos;
	int frame;
} back;
typedef struct
{
	SDL_Surface *img[11];
	SDL_Rect pos;
	int frame;
} logo;
typedef struct
{
	SDL_Rect pos;
	TTF_Font *font;
	SDL_Surface *surface_texte;
	SDL_Color textcolor;
	char texte[50];
} texte;
typedef struct
{
	Mix_Music *music;
	SDL_Rect pos;
	SDL_Surface *songpic;
	int num;
} song;
void init_image(image *images, int x, int y, char path[]);
void init_button_play(button *play);
void init_button_settings(button *settings);
void init_button_quit(button *quit);
void init_button_full_screen(button *full_screen);
void init_back(back *backg);
void init_logo(logo *logo);
void display_texte(texte text, SDL_Surface *screen);
void init_texte(texte *text);
void scrolling_menu_UP(button *play, button *settings, button *quit, int *n);
void scrolling_menu_DOWN(button *play, button *settings, button *quit, int *n);
void animation_back(back *backg);
void animation_logo(logo *logo);
void afficher_logo(logo logo, SDL_Surface *screen);
void afficher_image(image images, SDL_Surface *screen);
void afficher_button(button buttons, SDL_Surface *screen);
void afficher_back(back backg, SDL_Surface *screen);
void logo_music();
void back_music();
void init_back_music(song song[]);
void afficher_song(song song[], SDL_Surface *screen);
void play_music(song song[]);
// mini tache blanche
int minitache(void);
typedef struct
{
	int c;
	int l;
} Casee;
typedef struct
{
	SDL_Surface *img;
	SDL_Surface *img_2;
	SDL_Surface *img_3;
	SDL_Surface *img_4;
	SDL_Rect postion;
	int vitesse;
} Personnem;
typedef struct
{
	SDL_Surface *img;
	SDL_Surface *img_2;
	SDL_Surface *img_3;
	SDL_Surface *img_4;
	SDL_Rect postion;
} Ennemim;
typedef struct
{
	SDL_Surface *img;
	SDL_Rect postion;
} Backgroundm;
typedef struct
{
	SDL_Surface *img_map;
	SDL_Rect pos_map;
	SDL_Surface *img_joueur;
	SDL_Rect pos_joueur;
} minimapm;
typedef struct
{
	SDL_Surface *img;
	SDL_Rect postion;
	int reponse;
} enigmem;
void affichertemp(int *temps, SDL_Surface *screen, SDL_Surface *fond, TTF_Font *police);
void initmap(minimapm *m);
void afficherminimap(minimapm m, SDL_Surface *screen);
SDL_Rect MAJMinimap(SDL_Rect posJoueur, int redemensionement);
void afficherminimap(minimapm m, SDL_Surface *screen);
Casee afficher_jeton(SDL_Surface *screen, SDL_Surface *rouge, SDL_Event event, int t[6][7]);
Casee IA(int t[6][7]);
void afficher_jaune(SDL_Surface *screen, SDL_Surface *jaune, Casee c);
int checkk(int t[7][7]);
