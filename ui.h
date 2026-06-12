/* SPDX-License-Identifier: Zlib */
#ifndef UI_H
#define UI_H

#include "types.h"

/**
 * UI and Background System Function Declarations
 */

void initBackground(Background *background);
void freeBackground(Background *background);
void renderBackground(Background *background, SDL_Surface *screen);
void updateCamera(Background *background, bool inputKeys[], int moveStep);
void animateClouds(Background *background, SDL_Surface *screen);

int checkPixelCollision(Player *player, SDL_Surface *collisionMask);
SDL_Color getPixelColor(SDL_Surface *surface, int x, int y);

void initSplitScreenLeft(Background *background, Player *player);
void initSplitScreenRight(Background *background1, Player *player);
void renderSplitScreen(Background *background, SDL_Surface *screen);

#endif /* UI_H */
