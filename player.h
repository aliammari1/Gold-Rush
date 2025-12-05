#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/**
 * Player System Function Declarations
 */

void selectPlayer(int *playerNum, SDL_Surface *screen);
void initPlayer(Player *player);
void initPlayer2(Player *player);
void renderPlayer(Player player, SDL_Surface *screen);
void movePlayer(Player *player, Uint32 deltaTime);
void animatePlayer(Player *player);
void jump(Player *player);

#endif /* PLAYER_H */
