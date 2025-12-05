#ifndef WORLD_H
#define WORLD_H

#include "types.h"
#include "config.h"

void initMinimap(Minimap *minimap, SDL_Surface *screen);
void updatePlayerOnMap(Minimap *minimap, Player *player);
void renderMinimap(Minimap *minimap, SDL_Surface *screen, Player *player);
void saveScore(int score, char playerName[], char filename[]);
void findBestScore(char filename[], int score, char playerName[]);

#endif /* WORLD_H */
