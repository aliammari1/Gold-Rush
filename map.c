#include "header.h"
/**
 * @file map.c
 * @brief Testing Program.
 * @author C lahmar
 * @version 1
 * @date Apr 20, 2022
 *
 * Testing program for minimap
 *
 */
/**
 * @brief To initialize the map m.
 * @param m the map
 * @param screen the screen
 * @return Nothing
 */
void initialiser_map(map *m, SDL_Surface *screen)
{
	m->map = IMG_Load("mini_backgg.png");
	m->pos_map.x = 1000;
	m->pos_map.y = 100;
	m->mini_perso = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, 10, 10, 32, 0, 0, 0, 0);
	SDL_FillRect(m->mini_perso, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
	m->perso_pos_map.x = 0;
	m->perso_pos_map.y = 0;
}

/**
 * @brief To claculate the position of the mini-perso.
 * @param m the map
 * @param p the personnage
 * @return Nothing
 */
void perso_map(map *m, Personne *p)
{
	m->perso_pos_map.x = p->pos.x / 10 + m->pos_map.x;
	m->perso_pos_map.y = p->pos.y / 10 + 10 + m->pos_map.y;
}
/**
 * @brief afficher le minimap m dans le screen .
 * @param m le minimap
 * @param screen l'ecran
 * @param p the personnage
 * @return Nothing
 */

void affiche_map(map *m, SDL_Surface *screen, Personne *p)
{
	SDL_BlitSurface(m->map, NULL, screen, &m->pos_map);
	SDL_BlitSurface(m->mini_perso, NULL, screen, &m->perso_pos_map);
}

/**
 * @brief sauvegarder le nom et le score dans un fichier.
 * @param score le score
 * @param nomjoueur le nom du joueur
 * @param nomfichier le nom du fichier
 * @return Nothing
 */
void sauvegarder(int score, char nomjoueur[], char nomfichier[])
{
	FILE *f, *fnom;
	int id;
	char nom[255];
	f = fopen(nomfichier, "a+");
	fnom = fopen("testnom.txt", "a+");
	if (f == NULL)
	{
		printf("Erreur lors de l'ouverture d'un fichier");
	}
	if (fnom == NULL)
	{
		printf("Erreur lors de l'ouverture d'un fichier");
	}
	fprintf(f, "%d\n", score);
	while (fscanf(fnom, "%d %s\n", &id, nom) != EOF)
	{
		printf("%d \n", id);
	}
	fprintf(fnom, "%d %s\n", id + 1, nomjoueur);

	fclose(f);
	fclose(fnom);
}
/**
 * @brief trouve si le score est le meilleur (compare chaque score des joueur pour finalement trouve le meilleur score ) .
 * @param score le score
 * @param nomjoueur le nom du joueur
 * @param nomfichier le nom du fichier
 * @return Nothing--
 */
void meilleur(char nomfichier[], int score, char nomjoueur[])
{
	FILE *f, *fnom;
	char nom[255];
	int age;
	int id;
	char c;
	int t[50];
	int i = 0, s = 0;
	char *tnom[50];
	f = fopen("test.txt", "r");
	fnom = fopen("testnom.txt", "r");
	if (f == NULL)
	{
		printf("Erreur lors de l'ouverture d'un fichier");
		exit(1);
	}
	if (fnom == NULL)
	{
		printf("Erreur lors de l'ouverture d'un fichier");
		exit(1);
	}
	while (fscanf(f, "%d\n", &t[i]) == 1)
	{
		i++;
	}
	/*for(int j=0;j<i;j++)
		{printf("score : %d\n", t[j]);
	}*/
	int meilleur = t[0], d = 1;
	int x = 1;
	for (int h = 1; h < i; h++)
	{
		x++;
		if (t[h] > meilleur)
		{
			d = h + 1;
			meilleur = t[h];
		}
	}
	int z = 1;
	char nomjoueurmeilleur[4];

	while (fscanf(fnom, "%d %s\n", &id, nom) != EOF)
	{
		printf("%s\n", nom);

		if (id == d)
		{
			strcpy(nomjoueurmeilleur, nom);

			break;
		}
	}

	printf("meilleur score: %d", meilleur);

	printf("meilleur jeouer: %s", nomjoueurmeilleur);
	fclose(f);
	fclose(fnom);
}
