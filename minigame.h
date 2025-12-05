#ifndef MINIGAME_H
#define MINIGAME_H

#include "types.h"
#include "config.h"

int runConnectFourGame(void);
GameCell dropToken(SDL_Surface *screen, SDL_Surface *redToken, SDL_Event event, int board[GAME_BOARD_ROWS][GAME_BOARD_COLS]);
GameCell computerMove(int board[GAME_BOARD_ROWS][GAME_BOARD_COLS]);
void renderYellowToken(SDL_Surface *screen, SDL_Surface *yellowToken, GameCell cell);
int checkWinCondition(int board[GAME_BOARD_ROWS][GAME_BOARD_COLS]);

#endif /* MINIGAME_H */
