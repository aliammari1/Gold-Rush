#include "core.h"

/**
 * @brief Main game loop that delegates to state machine
 * @param engine The game engine
 * @return 0 on normal exit, 1 on error
 */
int game_loop(GameEngine *engine)
{
    if (engine == NULL) {
        printf("Error: game_loop called with NULL engine\n");
        return 1;
    }

    /* Initialize game objects for gameplay */
    initPlayer(&engine->player);
    if (engine->numPlayers == 2) {
        initPlayer2(&engine->player2);
    }
    initEnemy(&engine->enemy);
    initBackground(&engine->background);
    initMinimap(&engine->minimap, engine->screen);
    initGameTimer(&engine->gameTimer);

    /* Game loop - process all gameplay-related states */
    Uint32 frameStart = 0;
    Uint32 frameTime = 0;

    engine->currentState = STATE_GAMEPLAY;

    while ((engine->currentState == STATE_GAMEPLAY || engine->currentState == STATE_PAUSE) && engine->isRunning) {
        frameStart = SDL_GetTicks();

        /* Handle input events */
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            GameEngine_HandleInput(engine, &event);

            if (event.type == SDL_QUIT) {
                engine->isRunning = 0;
                break;
            }

            /* Game-specific input handling */
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    GameEngine_SetState(engine, STATE_MENU);
                    break;
                case SDLK_p:
                    if (engine->currentState == STATE_GAMEPLAY) {
                        GameEngine_SetState(engine, STATE_PAUSE);
                    } else if (engine->currentState == STATE_PAUSE) {
                        GameEngine_SetState(engine, STATE_GAMEPLAY);
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        /* Update game logic based on state */
        if (engine->currentState == STATE_GAMEPLAY) {
            /* Update player movement */
            if (engine->inputKeyRight) {
                engine->player.velocityX += PLAYER_ACCELERATION;
                engine->player.lastDirection = 0;
                engine->player.direction = DIR_MOVING_RIGHT;
            }

            if (engine->inputKeyLeft) {
                engine->player.velocityX -= PLAYER_ACCELERATION;
                engine->player.lastDirection = 1;
                engine->player.direction = DIR_MOVING_LEFT;
            }

            if (engine->inputKeyUp && !engine->player.isJumping) {
                engine->player.isJumping = 1;
                engine->player.direction = (engine->player.lastDirection == 0) ? DIR_JUMP_RIGHT : DIR_JUMP_LEFT;
            }

            /* Update player physics */
            movePlayer(&engine->player, FRAME_TIME_MS);
            if (engine->numPlayers == 2) {
                movePlayer(&engine->player2, FRAME_TIME_MS);
            }

            /* Update enemy AI */
            updateEnemyAI(&engine->enemy, engine->player);

            /* Handle jumping */
            if (engine->player.isJumping) {
                if (engine->player.relativePosition.x <= 20) {
                    jump(&engine->player);
                } else {
                    engine->player.isJumping = 0;
                    engine->player.relativePosition.x = -20;
                }
            }

            /* Update animations */
            animatePlayer(&engine->player);
            if (engine->numPlayers == 2) {
                animatePlayer(&engine->player2);
            }
            animateEnemy(&engine->enemy);

            /* Update minimap */
            updatePlayerOnMap(&engine->minimap, &engine->player);
            updateGameTime(&engine->gameTimer);
        }

        /* Render frame - different rendering for gameplay vs pause */
        if (engine->currentState == STATE_GAMEPLAY) {
            /* Render game gameplay elements */
            renderBackground(&engine->background, engine->screen);
            animateClouds(&engine->background, engine->screen);
            renderPlayer(engine->player, engine->screen);
            if (engine->numPlayers == 2) {
                renderPlayer(engine->player2, engine->screen);
            }
            renderEnemy(engine->enemy, engine->screen);
            renderMinimap(&engine->minimap, engine->screen, &engine->player);
            renderTimer(engine->gameTimer, engine->screen);
        } else if (engine->currentState == STATE_PAUSE) {
            /* Render game with pause overlay */
            renderBackground(&engine->background, engine->screen);
            renderPlayer(engine->player, engine->screen);
            if (engine->numPlayers == 2) {
                renderPlayer(engine->player2, engine->screen);
            }
            renderEnemy(engine->enemy, engine->screen);
            
            /* Render pause overlay */
            SDL_FillRect(engine->screen, NULL, SDL_MapRGB(engine->screen->format, 0, 0, 0));
            /* Pause text would be rendered here */
        }

        SDL_Flip(engine->screen);

        /* Frame rate limiting */
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_TIME_MS) {
            SDL_Delay(FRAME_TIME_MS - frameTime);
        }
    }

    /* Cleanup gameplay resources */
    freeBackground(&engine->background);

    return 0;
}
