/* SPDX-License-Identifier: Zlib */
#include "core.h"
/**
 * @file fct.c
 * @brief Testing Program.
 * @author rayen
 * @version 1
 * @date Apr 21, 2022
 *
 * Testing program for the ennemy
 *
 */

/**
 * @brief Initialize an enemy character
 * @param enemy the Enemy structure
 * @return Nothing
 */
void initEnemy(Enemy *enemy)
{
	enemy->spriteSheet = IMG_Load("assets/e.png");
	enemy->screenPosition.x = 300;
	enemy->screenPosition.y = 200;
	enemy->spritePosition.x = 300;
	enemy->spritePosition.y = 230;
	enemy->spritePosition.w = 75;
	enemy->spritePosition.h = 230;
	enemy->direction = 0;
	enemy->state = ENEMY_FOLLOWING;
}
/**
 * @brief Render the enemy character on screen
 * @param enemy the Enemy structure
 * @param screen the display surface
 * @return Nothing
 */
void renderEnemy(Enemy enemy, SDL_Surface *screen)
{
	SDL_BlitSurface(enemy.spriteSheet, &enemy.spritePosition, screen, &enemy.screenPosition);
	SDL_Flip(screen);
}
/**
 * @brief Animate the enemy character through frames
 * @param enemy the Enemy structure
 * @return Nothing
 */
void animateEnemy(Enemy *enemy)
{
	enemy->spritePosition.y = (enemy->direction) * (enemy->spritePosition.h);
	if (enemy->spritePosition.x == enemy->spriteSheet->w - enemy->spritePosition.w)
	{
		enemy->spritePosition.x = 0;
	}
	else
	{
		enemy->spritePosition.x = enemy->spritePosition.x + enemy->spritePosition.w;
	}
}
/**
 * @brief Toggle direction for an enemy
 * @param enemy the Enemy structure
 * @return Nothing
 */
void toggleDirection(Enemy *enemy)
{
	if (enemy->direction == 0)
	{
		enemy->direction = 1;
	}
	else
		enemy->direction = 0;
}
/**
 * @brief Move the enemy within the game world
 * @param enemy the Enemy structure
 * @return Nothing
 */
void moveEnemy(Enemy *enemy)
{
	if ((enemy->screenPosition.x > 1200) || (enemy->screenPosition.x < 10))
	{
		toggleDirection(enemy);
	}
	if (enemy->direction == 0)
	{
		enemy->screenPosition.x += 5;
	}
	else
	{
		enemy->screenPosition.x -= 5;
	}
}

/**
 * @brief Check bounding box collision between two rectangles
 * @param rect1 the first rectangle
 * @param rect2 the second rectangle
 * @return 1 if collision, 0 if no collision
 */
int checkCollisionBB(SDL_Rect rect1, SDL_Rect rect2)
{
	int result;
	if ((rect1.x + rect1.w < rect2.x) || (rect1.x > rect2.x + rect2.w) || (rect1.y + rect1.h < rect2.y) || (rect1.y > rect2.y + rect2.h))
	{
		result = 0;
	}
	else
		result = 1;
	return (result);
}

/**
 * @brief Update enemy movement based on AI state
 * @param enemy the Enemy structure
 * @param player the Player structure
 * @return Nothing
 */
void updateEnemyAI(Enemy *enemy, Player player)
{
	switch (enemy->state)
	{
	case ENEMY_WAITING:
		animateEnemy(enemy);
		break;
	case ENEMY_FOLLOWING:
		if (enemy->screenPosition.x > player.position.x)
			enemy->direction = 1;
		else
			enemy->direction = 0;
		animateEnemy(enemy);
		moveEnemy(enemy);
		break;
	}
}
