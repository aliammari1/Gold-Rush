/* SPDX-License-Identifier: Zlib */
#ifndef CONNECT4_AI_H
#define CONNECT4_AI_H

/*
 * SDL-free Connect Four board logic and a depth-limited alpha-beta
 * (minimax) opponent. This translation unit intentionally has no SDL
 * dependency so the decision logic can be unit-tested on any machine
 * with only a C compiler.
 *
 * Board convention (matches the rest of the game):
 *   - board is int[C4_ROWS][C4_COLS]
 *   - 0 = empty, C4_HUMAN (1) = red/player, C4_CPU (2) = yellow/computer
 *   - row 0 is the TOP row, row (C4_ROWS-1) is the BOTTOM row; tokens
 *     fall to the lowest empty row in a column.
 */

#define C4_ROWS 6
#define C4_COLS 7
#define C4_EMPTY 0
#define C4_HUMAN 1
#define C4_CPU 2

/* Default search depth for the alpha-beta opponent. */
#define C4_DEFAULT_DEPTH 6

/* Returns 1 if the given column has at least one empty cell. */
int c4_column_playable(const int board[C4_ROWS][C4_COLS], int col);

/*
 * Drops a token of `player` into `col`, mutating the board.
 * Returns the row it landed in, or -1 if the column was full.
 */
int c4_drop(int board[C4_ROWS][C4_COLS], int col, int player);

/*
 * Returns the winner (C4_HUMAN or C4_CPU) if there is a 4-in-a-row
 * (horizontal, vertical, or either diagonal), otherwise 0.
 */
int c4_winner(const int board[C4_ROWS][C4_COLS]);

/* Returns 1 if no column is playable (board full). */
int c4_board_full(const int board[C4_ROWS][C4_COLS]);

/*
 * Chooses the best column for `player` using depth-limited alpha-beta
 * search. `depth` is the number of plies to look ahead (use
 * C4_DEFAULT_DEPTH for a strong default). Returns a playable column in
 * [0, C4_COLS), or -1 if the board is full.
 *
 * The board is not modified.
 */
int c4_best_move(const int board[C4_ROWS][C4_COLS], int player, int depth);

#endif /* CONNECT4_AI_H */
