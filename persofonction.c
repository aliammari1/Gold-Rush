#include "header.h"
/**
 * @file fonction.c
 * @brief testing Program
 * @author Ali
 * @version 1
 * @date Apr 18, 2022
 *
 * Testing program for moving Character
 *
 */
/**
 * @brief To initialize the Character .
 * @param p the Character(Personne)
 * @return Nothing
 */
void initPerso(Personne *p)
{
	int i, j;
	char nom_image[20];
	for (i = 0; i < 6; i++)
		for (j = 0; j < 12; j++)
		{
			sprintf(nom_image, "images/%d/%d.png", i, j);
			p->img[i][j] = IMG_Load(nom_image);
		}
	p->pos.x = 0;
	p->pos.y = 300;
	p->pos_relative.x = -20;
	p->pos_relative.y = 0;
	p->direction = 0;
	p->frame = 0;
	p->d = 0;
	p->vX = 1;
	p->up = 0;
}
void initPerso2(Personne *p)
{
	int i, j;
	char nom_image[20];
	for (i = 0; i < 6; i++)
		for (j = 0; j < 12; j++)
		{
			sprintf(nom_image, "images/%d/%d.png", i, j);
			p->img[i][j] = IMG_Load(nom_image);
		}
	p->pos.x = 200;
	p->pos.y = 300;
	p->pos_relative.x = -20;
	p->pos_relative.y = 0;
	p->direction = 0;
	p->frame = 0;
	p->d = 0;
	p->vX = 5;
	p->up = 0;
}
/**
 * @brief Show the Character in the screen .
 * @param p the Character(Personne)
 * @param screen the screen
 * @return Nothing
 */
void afficherPerso(Personne p, SDL_Surface *screen)
{
	SDL_BlitSurface(p.img[p.direction][p.frame], NULL, screen, &p.pos);
}
/**
 * @brief make the Character Move .
 * @param p the Character(Personne)
 * @param dt the time difference
 * @return Nothing
 */
void deplacerPerso(Personne *p, Uint32 dt)
{
	if (p->direction == 1)
		p->pos.x += 0.5 * (p->vX) * dt * dt + VIT * dt;
	if (p->direction == 3)
		p->pos.x -= 0.5 * (p->vX) * dt * dt + VIT * dt;
	if (p->vX >= MAX_VIT)
		p->vX = MAX_VIT;
}
/**
 * @brief Animate the Character .
 * @param p the Character(Personne)
 * @return Nothing
 */
void animerPerso(Personne *p)
{
	p->frame++;
	if ((p->pos_relative.x <= 0) && (p->pos_relative.x != -20))
		p->frame = 2;
	if (p->pos_relative.x > 0)
		p->frame = 6;
	if (p->frame >= 11)
		p->frame = 0;
}
/**
 * @brief make the character jump .
 * @param p the Character(Personne)
 * @return Nothing
 */
void saut(Personne *p)
{
	p->pos_relative.y = (-0.0375) * (p->pos_relative.x) * (p->pos_relative.x) + 15;
	(p->pos_relative.x)++;
	if (p->d == 1)
		p->pos.x -= 10;
	if (p->d == 0)
		p->pos.x += 10;
	if (p->pos_relative.x <= 0)
		p->pos.y -= p->pos_relative.y;
	else
		p->pos.y += p->pos_relative.y;
}
void choisir_perso(int *n, SDL_Surface *screen)
{
	printf("hi\n");
	int click = 1;
	SDL_Event event1;
	image p, p2;
	SDL_Surface *backg;
	p.img = IMG_Load("player.png");
	p2.img = IMG_Load("player2.png");
	backg = IMG_Load("background.jpg");
	p.pos.x = 0;
	p.pos.y = 100;
	p2.pos.x = 400;
	p2.pos.y = 100;
	while (click)
	{
		SDL_BlitSurface(backg, NULL, screen, NULL);
		SDL_BlitSurface(p.img, NULL, screen, &p.pos);
		SDL_BlitSurface(p2.img, NULL, screen, &p2.pos);
		SDL_Flip(screen);
		SDL_WaitEvent(&event1);
		switch (event1.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (event1.motion.x >= 0 && event1.motion.x <= 381 && event1.motion.y >= 100 && event1.motion.y <= 172)
			{
				*n = 1;
				click = 0;
			}
			if (event1.motion.x >= 400 && event1.motion.x <= 795 && event1.motion.y >= 100 && event1.motion.y <= 153)
			{
				*n = 2;
				click = 0;
			}
			break;
		}
	}
}
