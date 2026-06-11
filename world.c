/* SPDX-License-Identifier: Zlib */
#include "core.h"
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
 * @brief To initialize the Minimap minimap.
 * @param m the map
 * @param screen the screen
 * @return Nothing
 */
void initMinimap(Minimap *minimap, SDL_Surface *screen)
{
	minimap->minimapImage = IMG_Load("assets/mini_backgg.png");
	minimap->minimapPosition.x = 1000;
	minimap->minimapPosition.y = 100;
	minimap->playerIndicator = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, 10, 10, 32, 0, 0, 0, 0);
	SDL_FillRect(minimap->playerIndicator, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
	minimap->playerMapPosition.x = 0;
	minimap->playerMapPosition.y = 0;
}

/**
 * @brief To claculate the position of the mini-perso.
 * @param m the map
 * @param p the personnage
 * @return Nothing
 */
void updatePlayerOnMap(Minimap *minimap, Player *player)
{
	minimap->playerMapPosition.x = player->position.x / 10 + minimap->minimapPosition.x;
	minimap->playerMapPosition.y = player->position.y / 10 + 10 + minimap->minimapPosition.y;
}
/**
 * @brief afficher le miniMinimap minimap dans le screen .
 * @param m le minimap
 * @param screen l'ecran
 * @param p the personnage
 * @return Nothing
 */

void renderMinimap(Minimap *minimap, SDL_Surface *screen, Player *player)
{
	SDL_BlitSurface(minimap->minimapImage, NULL, screen, &minimap->minimapPosition);
	SDL_BlitSurface(minimap->playerIndicator, NULL, screen, &minimap->playerMapPosition);
}

/**
 * @brief sauvegarder le nom et le score dans un fichier.
 * @param score le score
 * @param nomjoueur le nom du joueur
 * @param nomfichier le nom du fichier
 * @return Nothing
 */
void saveScore(int score, char nomjoueur[], char nomfichier[])
{
	FILE *f, *fnom;
	int id;
	char nom[255];
	id = 0;
	f = fopen(nomfichier, "a+");
	if (f == NULL)
	{
		printf("Erreur lors de l'ouverture d'un fichier");
		return;
	}
	fnom = fopen("assets/testnom.txt", "a+");
	if (fnom == NULL)
	{
		printf("Erreur lors de l'ouverture d'un fichier");
		fclose(f);
		return;
	}
	fprintf(f, "%d\n", score);
	while (fscanf(fnom, "%d %254s\n", &id, nom) != EOF)
	{
		printf("%d \n", id);
	}
	/* Reposition before writing: a read followed by a write on the same
	 * stream without an intervening positioning call is undefined. */
	fseek(fnom, 0, SEEK_END);
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
void findBestScore(char nomfichier[], int score, char nomjoueur[])
{
	FILE *f, *fnom;
	char nom[255];
	int age;
	int id;
	char c;
	int t[50];
	int i = 0, s = 0;
	char *tnom[50];
	f = fopen("assets/test.txt", "r");
	fnom = fopen("assets/testnom.txt", "r");
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
	for (int h = 1; h < i; h++)
	{
		if (t[h] > meilleur)
		{
			d = h + 1;
			meilleur = t[h];
		}
	}
	char nomjoueurmeilleur[256] = "";  /* Increased buffer size to prevent overflow */

	while (fscanf(fnom, "%d %254s\n", &id, nom) != EOF)
	{
		printf("%s\n", nom);

		if (id == d)
		{
			strncpy(nomjoueurmeilleur, nom, sizeof(nomjoueurmeilleur) - 1);
			nomjoueurmeilleur[sizeof(nomjoueurmeilleur) - 1] = '\0';

			break;
		}
	}

	printf("meilleur score: %d\n", meilleur);

	printf("meilleur joueur: %s\n", nomjoueurmeilleur);
	fclose(f);
	fclose(fnom);
}
