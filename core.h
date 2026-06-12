/* SPDX-License-Identifier: Zlib */
#ifndef CORE_H
#define CORE_H

/* Include all game headers - single point of reference */
#include "config.h"
#include "types.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "ui.h"
#include "timer.h"
#include "world.h"
#include "puzzle.h"
#include "minigame.h"

/* Main game loop */
int game_loop(GameEngine *engine);

#endif /* CORE_H */
