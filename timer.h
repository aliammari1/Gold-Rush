/* SPDX-License-Identifier: Zlib */
#ifndef TIMER_H
#define TIMER_H

#include "types.h"

/**
 * Timer and Game Time Function Declarations
 */

void initGameTimer(GameTimer *timer);
void initPuzzleTimer(GameTimer *timer);
void updateTimerTick(int *startTime);
int initTimerDisplay(TextDisplay *display);
int initPuzzleDisplay(TextDisplay *display);
int loadTimerFont(TextDisplay *display, char *fontPath);
void updateGameTime(GameTimer *timer);
void updatePuzzleTime(GameTimer *timer);
void renderTimer(GameTimer timer, SDL_Surface *screen);
void freeTimerDisplay(TextDisplay display);

#endif /* TIMER_H */
