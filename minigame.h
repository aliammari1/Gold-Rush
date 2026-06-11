/* SPDX-License-Identifier: Zlib */
#ifndef MINIGAME_H
#define MINIGAME_H

#include "types.h"
#include "config.h"

/**
 * @enum ConnectFourOpponent
 * @brief Selects which AI drives the yellow (CPU) tokens.
 */
typedef enum {
    CONNECT_FOUR_HEURISTIC = 0, /*!< Original rule-based opponent */
    CONNECT_FOUR_MINIMAX        /*!< Depth-limited alpha-beta opponent */
} ConnectFourOpponent;

/* Default board entry point (heuristic opponent; preserves old behaviour). */
int runConnectFourGame(void);

/* Run Connect Four against a selectable opponent ('vs CPU' modes). */
int runConnectFourGameMode(ConnectFourOpponent opponent);

GameCell dropToken(SDL_Surface *screen, SDL_Surface *redToken, SDL_Event event, int board[GAME_BOARD_ROWS][GAME_BOARD_COLS]);
GameCell computerMove(int board[GAME_BOARD_ROWS][GAME_BOARD_COLS]);

/* Picks the CPU move via depth-limited alpha-beta minimax. */
GameCell computerMoveMinimax(int board[GAME_BOARD_ROWS][GAME_BOARD_COLS]);

void renderYellowToken(SDL_Surface *screen, SDL_Surface *yellowToken, GameCell cell);
int checkWinCondition(int board[GAME_BOARD_ROWS][GAME_BOARD_COLS]);

#endif /* MINIGAME_H */
