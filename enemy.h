#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

/**
 * Enemy System Function Declarations
 */

void initEnemy(Enemy *enemy);
void renderEnemy(Enemy enemy, SDL_Surface *screen);
void animateEnemy(Enemy *enemy);
void moveEnemy(Enemy *enemy);
void updateEnemyAI(Enemy *enemy, Player playerTarget);
void toggleDirection(Enemy *enemy);
int checkCollisionBB(SDL_Rect rect1, SDL_Rect rect2);

#endif /* ENEMY_H */
