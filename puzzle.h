/* SPDX-License-Identifier: Zlib */
#ifndef PUZZLE_H
#define PUZZLE_H

#include "types.h"
#include "config.h"

void runPuzzleGame(void);
void renderPuzzle(Puzzle puzzle, SDL_Surface *screen);
void initPuzzle(Puzzle *puzzle);
void animatePuzzle(Puzzle *puzzle, SDL_Rect *spritePos, int frame);

#endif /* PUZZLE_H */
