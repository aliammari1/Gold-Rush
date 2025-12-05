#include "core.h"
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
 * @brief Initialize the player character with sprites
 * @param player the Player structure
 * @return Nothing
 */
void initPlayer(Player *player)
{
	int directionIdx, frameIdx;
	char imagePath[20];
	for (directionIdx = 0; directionIdx < 6; directionIdx++)
		for (frameIdx = 0; frameIdx < 12; frameIdx++)
		{
			sprintf(imagePath, "assets/images/%d/%d.png", directionIdx, frameIdx);
			player->sprites[directionIdx][frameIdx] = IMG_Load(imagePath);
		}
	player->position.x = 0;
	player->position.y = 300;
	player->relativePosition.x = -20;
	player->relativePosition.y = 0;
	player->direction = 0;
	player->currentFrame = 0;
	player->lastDirection = 0;
	player->velocityX = 1;
	player->isJumping = 0;
}
void initPlayer2(Player *player)
{
	int directionIdx, frameIdx;
	char imagePath[20];
	for (directionIdx = 0; directionIdx < 6; directionIdx++)
		for (frameIdx = 0; frameIdx < 12; frameIdx++)
		{
			sprintf(imagePath, "assets/images/%d/%d.png", directionIdx, frameIdx);
			player->sprites[directionIdx][frameIdx] = IMG_Load(imagePath);
		}
	player->position.x = 200;
	player->position.y = 300;
	player->relativePosition.x = -20;
	player->relativePosition.y = 0;
	player->direction = 0;
	player->currentFrame = 0;
	player->lastDirection = 0;
	player->velocityX = 5;
	player->isJumping = 0;
}
/**
 * @brief Render the player character on screen
 * @param player the Player structure
 * @param screen the display surface
 * @return Nothing
 */
void renderPlayer(Player player, SDL_Surface *screen)
{
	SDL_BlitSurface(player.sprites[player.direction][player.currentFrame], NULL, screen, &player.position);
}
/**
 * @brief Move the player character based on velocity and direction
 * @param player the Player structure
 * @param deltaTime the elapsed time in milliseconds
 * @return Nothing
 */
void movePlayer(Player *player, Uint32 deltaTime)
{
	if (player->direction == 1)
		player->position.x += 0.5 * (player->velocityX) * deltaTime * deltaTime + PLAYER_BASE_VELOCITY * deltaTime;
	if (player->direction == 3)
		player->position.x -= 0.5 * (player->velocityX) * deltaTime * deltaTime + PLAYER_BASE_VELOCITY * deltaTime;
	if (player->velocityX >= PLAYER_MAX_VELOCITY)
		player->velocityX = PLAYER_MAX_VELOCITY;
}
/**
 * @brief Animate the player character through sprite frames
 * @param player the Player structure
 * @return Nothing
 */
void animatePlayer(Player *player)
{
	player->currentFrame++;
	if ((player->relativePosition.x <= 0) && (player->relativePosition.x != -20))
		player->currentFrame = 2;
	if (player->relativePosition.x > 0)
		player->currentFrame = 6;
	if (player->currentFrame >= 11)
		player->currentFrame = 0;
}
/**
 * @brief Execute a jump movement for the player character
 * @param player the Player structure
 * @return Nothing
 */
void jump(Player *player)
{
	player->relativePosition.y = (-0.0375) * (player->relativePosition.x) * (player->relativePosition.x) + 15;
	(player->relativePosition.x)++;
	if (player->lastDirection == 1)
		player->position.x -= 10;
	if (player->lastDirection == 0)
		player->position.x += 10;
	if (player->relativePosition.x <= 0)
		player->position.y -= player->relativePosition.y;
	else
		player->position.y += player->relativePosition.y;
}
void selectPlayer(int *playerNumber, SDL_Surface *screen)
{
	printf("Player selection started\n");
	int isSelecting = 1;
	SDL_Event event;
	SDL_Surface *player1Image, *player2Image;
	SDL_Surface *background;
	SDL_Rect player1Pos, player2Pos;
	
	/* Initialize default value */
	*playerNumber = 1;
	
	/* Load images */
	player1Image = IMG_Load("assets/player.png");
	player2Image = IMG_Load("assets/player2.png");
	background = IMG_Load("assets/background.jpg");
	
	/* Check if images loaded successfully */
	if (player1Image == NULL || player2Image == NULL || background == NULL) {
		printf("Warning: Failed to load player selection images\n");
		return;
	}
	
	/* Set positions */
	player1Pos.x = 0;
	player1Pos.y = 100;
	player2Pos.x = 400;
	player2Pos.y = 100;
	
	/* Player selection loop */
	while (isSelecting) {
		SDL_BlitSurface(background, NULL, screen, NULL);
		SDL_BlitSurface(player1Image, NULL, screen, &player1Pos);
		SDL_BlitSurface(player2Image, NULL, screen, &player2Pos);
		SDL_Flip(screen);
		
		if (SDL_WaitEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				/* Exit game if window closed */
				exit(0);
				break;
				
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					/* Check if player 1 clicked */
					if (event.button.x >= 0 && event.button.x <= 381 && 
						event.button.y >= 100 && event.button.y <= 172) {
						*playerNumber = 1;
						isSelecting = 0;
						printf("Player 1 selected\n");
					}
					/* Check if player 2 clicked */
					else if (event.button.x >= 400 && event.button.x <= 795 && 
							 event.button.y >= 100 && event.button.y <= 153) {
						*playerNumber = 2;
						isSelecting = 0;
						printf("Player 2 selected\n");
					}
				}
				break;
				
			case SDL_KEYDOWN:
				/* Allow keyboard selection */
				if (event.key.keysym.sym == SDLK_1) {
					*playerNumber = 1;
					isSelecting = 0;
					printf("Player 1 selected (keyboard)\n");
				} else if (event.key.keysym.sym == SDLK_2) {
					*playerNumber = 2;
					isSelecting = 0;
					printf("Player 2 selected (keyboard)\n");
				}
				break;
				
			default:
				break;
			}
		}
	}
	
	/* Cleanup */
	if (player1Image != NULL) {
		SDL_FreeSurface(player1Image);
	}
	if (player2Image != NULL) {
		SDL_FreeSurface(player2Image);
	}
	if (background != NULL) {
		SDL_FreeSurface(background);
	}
}
