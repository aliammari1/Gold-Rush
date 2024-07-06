#include "header.h"

/**
 * @file enigme_jeu.c
 * @brief Testing Program.
 * @author yassine
 * @version 1
 * @date Apr 26, 2022
 *
 * Testing program for enigme  *
 */

void enigme_jeu()
{

	int score = 140;
	char scorechar[100];
	TTF_Init();

	TTF_Font *police = NULL;

	TTF_Font *policee = NULL; /// police b taille asghr
	SDL_Color yellow = {255, 255, 0};
	SDL_Color red = {125, 0, 0};
	SDL_Color white = {0, 255, 255};			 ////black
	police = TTF_OpenFont("assets/Trajan Pro.ttf", 28); // l 20 hia l taille
	policee = TTF_OpenFont("assets/Trajan Pro.ttf", 30);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Chunk *soundbtn;
	soundbtn = Mix_LoadWAV("assets/mixkit-game-click-1114.wav");

	/// score

	SDL_Surface *surface_score = NULL;

	SDL_Color blue = {255, 255, 255};
	SDL_Color green = {0, 200, 0};

	surface_score = TTF_RenderText_Blended(police, "score :", blue);
	SDL_Rect position_score;

	position_score.x = 5;
	position_score.y = 5;

	////// you won /wrong
	SDL_Surface *surface_message = NULL;
	surface_message = TTF_RenderText_Blended(policee, "", green);
	SDL_Rect position_message;
	position_message.x = 770;
	position_message.y = 250;

	sprintf(scorechar, "%d", score);									   // convertir entier l chaine de charactere
	SDL_Surface *surface_total_score = NULL;							   // surface score
	surface_total_score = TTF_RenderText_Blended(police, scorechar, blue); // valeur fl blue taa score
	SDL_Rect position_total_score;
	////position taa score
	position_total_score.x = 120;
	position_total_score.y = 5;

	enigme e;

	SDL_Surface *screen = NULL; // creation d'une surface;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("erreur: %s \n", SDL_GetError());
	}

	///////creation d'une fentre (largeur,hauteur,resolution,flags);

	screen = SDL_SetVideoMode(1200, 639, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); /////////////largeur w h taa fenetre
	if (screen == NULL)
	{
		printf("unable to set video mode :%s", SDL_GetError());
	}

	/// position taa image teek
	SDL_Rect position; // variable qui a deux coordonnees x et y qui doivent etre initialisees
	position.x = 0;	   // en pixels
	position.y = 0;

	SDL_Surface *image = NULL;					// decalaration d'une surface nommee image
	image = IMG_Load("assets/background_projet1.png"); // load the image

	init_enigmes(&e); /// bhs taateha enigme e w traajaa l enigme meebi

	int cont = 1; // quitter

	SDL_Event event;

	int detect_sound = 0; // tet7arek bl souris

	int detect_reponse = 0; /// pour detecter reponse juste ou fausse

	//////////animation

	SDL_Surface *skull = NULL;

	skull = IMG_Load("assets/skulltest.png"); ////////////taswira taa animation

	SDL_Rect pos_sprite; ////position pr sprite

	SDL_Rect pos_screen; // pos sprite pr screen

	pos_sprite.x = 0;
	pos_sprite.y = 0;
	pos_sprite.w = 785 / 9;
	pos_sprite.h = 175 / 2;

	////affichage taa l position taa l animation
	pos_screen.x = 780;
	pos_screen.y = 280;

	while (cont == 1)
	{ // ki tenzel echap yokhrej w cont=0
		if (score <= 0)
			cont = 0; ////
		// affichage

		SDL_BlitSurface(image, NULL, screen, &position); /// tlasa9 image fou9 fenetre screen
		SDL_BlitSurface(surface_total_score, NULL, screen, &position_total_score);
		SDL_BlitSurface(surface_score, NULL, screen, &position_score);
		afficherenigme(e, screen);

		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			cont = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: // pour quitter
				cont = 0;
				break;

			case SDLK_a:
			{
				if (detect_reponse == 0)
				{
					if (e.reponse != 1)
					{
						score -= 20;
						init_enigmes(&e);				 // bsh ychargilk les questions taa sou1el li baad
						sprintf(scorechar, "%d", score); // actualiser chaine de character taa score
						surface_message = TTF_RenderText_Blended(policee, "Wrong!", red);
						surface_total_score = TTF_RenderText_Blended(police, scorechar, blue); // actualiser l score (ywali maktoub 120)

						pos_sprite.x = 0;
						pos_sprite.y = 0;

						/////animation
						for (int i = 0; i < 2; i++)
						{ // nbr de ligne fl matrice(matrcie)
							for (int j = 0; j < 9; j++)
							{
								SDL_Flip(screen);
								animer(&e, &pos_sprite, j); /// fct animer
								SDL_BlitSurface(skull, &pos_sprite, screen, &pos_screen);
								SDL_Flip(screen);
								SDL_Delay(100);
								SDL_BlitSurface(surface_message, NULL, screen, &position_message);
								SDL_Flip(screen);
							}

							pos_sprite.x = 0;
							pos_sprite.y += pos_sprite.h;
						}															////passer a la ligne suivante
						surface_message = TTF_RenderText_Blended(policee, "", red); /////bsh ki toufa l animation yna7i l msg taa wrong
					}

					else if (e.reponse == 1)
					{
						score += 20;
						init_enigmes(&e);
						sprintf(scorechar, "%d", score);
						surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
						detect_reponse = 1; // maaneha jewebt bes7i7
						surface_message = TTF_RenderText_Blended(policee, "You Won", green);
						SDL_Delay(300);
						cont = 0;
					}
				}
			}
			break;

			case SDLK_b:

			{
				if (detect_reponse == 0)
				{
					if (e.reponse != 2)
					{
						score -= 20;
						init_enigmes(&e);
						detect_reponse = 0;
						sprintf(scorechar, "%d", score);
						surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
						surface_message = TTF_RenderText_Blended(policee, "Wrong!", red);
						pos_sprite.x = 0;
						pos_sprite.y = 0;
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								SDL_Flip(screen);
								animer(&e, &pos_sprite, j);
								SDL_BlitSurface(skull, &pos_sprite, screen, &pos_screen);
								SDL_BlitSurface(surface_message, NULL, screen, &position_message);
								SDL_Flip(screen);
								SDL_Delay(100);
								SDL_Flip(screen);
							}
							pos_sprite.x = 0;
							pos_sprite.y += pos_sprite.h;
						}
						surface_message = TTF_RenderText_Blended(policee, "", red);
					}
					else if (e.reponse == 2)
					{
						score += 20;
						sprintf(scorechar, "%d", score);
						surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
						detect_reponse = 1;
						surface_message = TTF_RenderText_Blended(policee, "You Won", green);
						SDL_Delay(300);
						cont = 0;
					}
				}
			}
			break;

			case SDLK_c:
			{
				if (detect_reponse == 0)
				{
					if (e.reponse != 3)
					{ ////////////////lfar9 bin les case houni
						score -= 20;
						detect_reponse = 0;
						init_enigmes(&e);
						sprintf(scorechar, "%d", score);
						surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
						surface_message = TTF_RenderText_Blended(policee, "Wrong !", red);
						pos_sprite.x = 0;
						pos_sprite.y = 0;
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								SDL_Flip(screen);
								animer(&e, &pos_sprite, j);
								SDL_BlitSurface(skull, &pos_sprite, screen, &pos_screen);
								SDL_BlitSurface(surface_message, NULL, screen, &position_message);
								SDL_Flip(screen);
								SDL_Delay(100);
								SDL_Flip(screen);
							}
							pos_sprite.x = 0;
							pos_sprite.y += pos_sprite.h;
						}
						surface_message = TTF_RenderText_Blended(policee, "", red);
					}
					else if (e.reponse == 3)
					{
						score += 20;
						sprintf(scorechar, "%d", score);
						surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
						detect_reponse = 1;
						surface_message = TTF_RenderText_Blended(policee, "You Won", green);
						SDL_Delay(300);
						cont = 0;
					}
				}
			}
			break;
			}

		case SDL_MOUSEBUTTONDOWN:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:

			{
				if (event.button.x > 500 && event.button.x < 550 && event.button.y > 150 && event.button.y < 170) /// coordonne taa rep lowl
				{
					if (detect_reponse == 0)
					{
						if (e.reponse != 1)
						{
							score -= 20;
							init_enigmes(&e);
							detect_reponse = 0;
							sprintf(scorechar, "%d", score);
							surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
							surface_message = TTF_RenderText_Blended(policee, "Wrong!", red);
							pos_sprite.x = 0;
							pos_sprite.y = 0;
							for (int i = 0; i < 2; i++)
							{
								for (int j = 0; j < 9; j++)
								{
									SDL_Flip(screen);
									animer(&e, &pos_sprite, j);
									SDL_BlitSurface(skull, &pos_sprite, screen, &pos_screen);
									SDL_BlitSurface(surface_message, NULL, screen, &position_message);
									SDL_Flip(screen);
									SDL_Delay(100);
									SDL_Flip(screen);
								}
								pos_sprite.x = 0;
								pos_sprite.y += pos_sprite.h;
							}
							surface_message = TTF_RenderText_Blended(policee, "", red);
						}
						else if (e.reponse == 1)
						{
							score += 20;
							sprintf(scorechar, "%d", score);
							surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
							detect_reponse = 1;
							surface_message = TTF_RenderText_Blended(policee, "You Won", green);
							SDL_Delay(300);
							cont = 0;
						}
					}
				}

				else if (event.button.x > 500 && event.button.x < 550 && event.button.y > 250 && event.button.y < 270)
				{

					if (detect_reponse == 0)
					{
						if (e.reponse != 2)
						{
							score -= 20;
							init_enigmes(&e);
							detect_reponse = 0;
							sprintf(scorechar, "%d", score);
							surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
							surface_message = TTF_RenderText_Blended(policee, "Wrong!", red);
							pos_sprite.x = 0;
							pos_sprite.y = 0;
							for (int i = 0; i < 2; i++)
							{
								for (int j = 0; j < 9; j++)
								{
									SDL_Flip(screen);
									animer(&e, &pos_sprite, j);
									SDL_BlitSurface(skull, &pos_sprite, screen, &pos_screen);
									SDL_BlitSurface(surface_message, NULL, screen, &position_message);
									SDL_Flip(screen);
									SDL_Delay(100);
									SDL_Flip(screen);
								}
								pos_sprite.x = 0;
								pos_sprite.y += pos_sprite.h;
							}
							surface_message = TTF_RenderText_Blended(policee, "", red);
						}
						else if (e.reponse == 2)
						{
							score += 20;
							sprintf(scorechar, "%d", score);
							surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
							detect_reponse = 1;
							surface_message = TTF_RenderText_Blended(policee, "You Won", green);
							SDL_Delay(300);
							cont = 0;
						}
					}
				}

				else if (event.button.x > 500 && event.button.x < 550 && event.button.y > 350 && event.button.y < 370)
				{

					if (detect_reponse == 0)
					{
						if (e.reponse != 3)
						{
							score -= 20;
							init_enigmes(&e);
							detect_reponse = 0;
							sprintf(scorechar, "%d", score);
							surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
							surface_message = TTF_RenderText_Blended(policee, "Wrong!", red);
							pos_sprite.x = 0;
							pos_sprite.y = 0;
							for (int i = 0; i < 2; i++)
							{
								for (int j = 0; j < 9; j++)
								{
									SDL_Flip(screen);
									animer(&e, &pos_sprite, j);
									SDL_BlitSurface(skull, &pos_sprite, screen, &pos_screen);
									SDL_BlitSurface(surface_message, NULL, screen, &position_message);
									SDL_Flip(screen);
									SDL_Delay(100);
									SDL_Flip(screen);
								}
								pos_sprite.x = 0;
								pos_sprite.y += pos_sprite.h;
							}
							surface_message = TTF_RenderText_Blended(policee, "", red);
						}
						else if (e.reponse == 3)
						{
							score += 20;
							sprintf(scorechar, "%d", score);
							surface_total_score = TTF_RenderText_Blended(police, scorechar, blue);
							detect_reponse = 1;
							surface_message = TTF_RenderText_Blended(policee, "You Won", green);
							SDL_Delay(300);
							cont = 0;
						}
					}
				}

			} // case
			}
		}

		case SDL_MOUSEMOTION:
		{
			if (event.motion.x > 500 && event.motion.x < 550 && event.motion.y > 150 && event.motion.y < 170) // reponse 1
			{
				if (detect_sound == 0)
				{
					Mix_PlayChannel(-1, soundbtn, 0);
					detect_sound = 1;
					e.surfacereponse1 = TTF_RenderText_Blended(police, e.reponse1, yellow);
					e.surfacereponse2 = TTF_RenderText_Blended(police, e.reponse2, white);
					e.surfacereponse3 = TTF_RenderText_Blended(police, e.reponse3, white);
				}
			}

			else if (event.motion.x > 500 && event.motion.x < 550 && event.motion.y > 250 && event.motion.y < 270) // reponse2
			{
				if (detect_sound == 0)
				{
					Mix_PlayChannel(-1, soundbtn, 0);
					detect_sound = 1;
				}
				e.surfacereponse1 = TTF_RenderText_Blended(police, e.reponse1, white);
				e.surfacereponse2 = TTF_RenderText_Blended(police, e.reponse2, yellow);
				e.surfacereponse3 = TTF_RenderText_Blended(police, e.reponse3, white);
			}

			else if (event.motion.x > 500 && event.motion.x < 550 && event.motion.y > 350 && event.motion.y < 370)
			{
				if (detect_sound == 0)
				{
					Mix_PlayChannel(-1, soundbtn, 0);
					detect_sound = 1;
				}
				e.surfacereponse3 = TTF_RenderText_Blended(police, e.reponse3, yellow);
				e.surfacereponse1 = TTF_RenderText_Blended(police, e.reponse1, white);
				e.surfacereponse2 = TTF_RenderText_Blended(police, e.reponse2, white);
			}
			else
			{
				detect_sound = 0;
				e.surfacereponse3 = TTF_RenderText_Blended(police, e.reponse3, white);
				e.surfacereponse1 = TTF_RenderText_Blended(police, e.reponse1, white);
				e.surfacereponse2 = TTF_RenderText_Blended(police, e.reponse2, white);
			}
		}
		}

		SDL_Flip(screen);
		SDL_BlitSurface(surface_total_score, NULL, screen, &position_total_score); // postion mtaa score
		SDL_BlitSurface(surface_score, NULL, screen, &position_score);			   // position score char
		SDL_BlitSurface(surface_message, NULL, screen, &position_message);		   // position message (wrong you won )
		SDL_Flip(screen);
		SDL_Delay(20);
	}

	SDL_Quit();
}
