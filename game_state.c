#include "game_state.h"
#include "config.h"
#include <string.h>

/**
 * @brief Initialize a game engine
 * @return Pointer to new GameEngine or NULL
 */
GameEngine* GameEngine_Create(void)
{
    GameEngine *engine = (GameEngine *)malloc(sizeof(GameEngine));
    if (engine == NULL) {
        return NULL;
    }

    /* Initialize state */
    engine->currentState = STATE_MENU;
    engine->previousState = STATE_MENU;
    engine->menuSelection = MENU_PLAY;
    engine->numPlayers = 1;
    engine->playerScore = 0;
    engine->isRunning = 1;
    engine->shouldFullscreen = 0;

    /* Initialize input state */
    engine->inputKeyRight = false;
    engine->inputKeyLeft = false;
    engine->inputKeyUp = false;
    engine->inputKeyDown = false;
    engine->mouseX = 0;
    engine->mouseY = 0;
    engine->mouseLeftClicked = false;

    /* Create screen surface */
    engine->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, 
                                       SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (engine->screen == NULL) {
        printf("Failed to create screen: %s\n", SDL_GetError());
        free(engine);
        return NULL;
    }

    SDL_WM_SetCaption("Game Project", NULL);

    /* Load collision mask */
    engine->collisionMask = SDL_LoadBMP("assets/backgroundmasque.bmp");
    if (engine->collisionMask == NULL) {
        printf("Warning: Could not load collision mask\n");
    }

    /* Initialize game objects */
    memset(&engine->player, 0, sizeof(Player));
    memset(&engine->player2, 0, sizeof(Player));
    memset(&engine->enemy, 0, sizeof(Enemy));
    memset(&engine->background, 0, sizeof(Background));
    memset(&engine->minimap, 0, sizeof(Minimap));
    memset(&engine->gameTimer, 0, sizeof(GameTimer));
    memset(&engine->puzzleTimer, 0, sizeof(GameTimer));
    memset(&engine->currentPuzzle, 0, sizeof(Puzzle));

    /* Initialize UI elements */
    memset(&engine->buttonPlay, 0, sizeof(MenuButton));
    memset(&engine->buttonSettings, 0, sizeof(MenuButton));
    memset(&engine->buttonQuit, 0, sizeof(MenuButton));
    memset(&engine->menuBg, 0, sizeof(MenuBackground));
    memset(&engine->menuLogo, 0, sizeof(MenuLogo));
    memset(&engine->menuText, 0, sizeof(MenuText));
    memset(&engine->backgroundMusic, 0, sizeof(engine->backgroundMusic));
    engine->clickSound = NULL;

    return engine;
}

/**
 * @brief Destroy a game engine and free resources
 * @param engine Pointer to GameEngine to destroy
 */
void GameEngine_Destroy(GameEngine *engine)
{
    if (engine == NULL) {
        return;
    }

    /* Free surfaces */
    if (engine->screen != NULL) {
        SDL_FreeSurface(engine->screen);
    }
    if (engine->collisionMask != NULL) {
        SDL_FreeSurface(engine->collisionMask);
    }

    /* Free sound */
    if (engine->clickSound != NULL) {
        Mix_FreeChunk(engine->clickSound);
    }

    /* Free music */
    for (int i = 0; i < 5; i++) {
        if (engine->backgroundMusic[i].music != NULL) {
            Mix_FreeMusic(engine->backgroundMusic[i].music);
        }
        if (engine->backgroundMusic[i].albumArt != NULL) {
            SDL_FreeSurface(engine->backgroundMusic[i].albumArt);
        }
    }

    /* Free player sprites */
    for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
        for (int frame = 0; frame < NUM_FRAMES_PER_DIRECTION; frame++) {
            if (engine->player.sprites[dir][frame] != NULL) {
                SDL_FreeSurface(engine->player.sprites[dir][frame]);
            }
            if (engine->player2.sprites[dir][frame] != NULL) {
                SDL_FreeSurface(engine->player2.sprites[dir][frame]);
            }
        }
    }

    /* Free enemy sprites */
    if (engine->enemy.spriteSheet != NULL) {
        SDL_FreeSurface(engine->enemy.spriteSheet);
    }

    /* Free background */
    if (engine->background.backgroundImage != NULL) {
        SDL_FreeSurface(engine->background.backgroundImage);
    }
    if (engine->background.cloudImage != NULL) {
        SDL_FreeSurface(engine->background.cloudImage);
    }

    /* Free minimap */
    if (engine->minimap.minimapImage != NULL) {
        SDL_FreeSurface(engine->minimap.minimapImage);
    }
    if (engine->minimap.playerIndicator != NULL) {
        SDL_FreeSurface(engine->minimap.playerIndicator);
    }

    /* Free puzzle surfaces */
    if (engine->currentPuzzle.questionSurface != NULL) {
        SDL_FreeSurface(engine->currentPuzzle.questionSurface);
    }
    if (engine->currentPuzzle.answer1Surface != NULL) {
        SDL_FreeSurface(engine->currentPuzzle.answer1Surface);
    }
    if (engine->currentPuzzle.answer2Surface != NULL) {
        SDL_FreeSurface(engine->currentPuzzle.answer2Surface);
    }
    if (engine->currentPuzzle.answer3Surface != NULL) {
        SDL_FreeSurface(engine->currentPuzzle.answer3Surface);
    }

    /* Free UI elements */
    for (int i = 0; i < 2; i++) {
        if (engine->buttonPlay.sprites[i] != NULL) {
            SDL_FreeSurface(engine->buttonPlay.sprites[i]);
        }
        if (engine->buttonSettings.sprites[i] != NULL) {
            SDL_FreeSurface(engine->buttonSettings.sprites[i]);
        }
        if (engine->buttonQuit.sprites[i] != NULL) {
            SDL_FreeSurface(engine->buttonQuit.sprites[i]);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (engine->menuBg.sprites[i] != NULL) {
            SDL_FreeSurface(engine->menuBg.sprites[i]);
        }
    }

    for (int i = 0; i < 11; i++) {
        if (engine->menuLogo.sprites[i] != NULL) {
            SDL_FreeSurface(engine->menuLogo.sprites[i]);
        }
    }

    if (engine->menuText.textSurface != NULL) {
        SDL_FreeSurface(engine->menuText.textSurface);
    }

    if (engine->menuText.font != NULL) {
        TTF_CloseFont(engine->menuText.font);
    }

    if (engine->gameTimer.display.font != NULL) {
        TTF_CloseFont(engine->gameTimer.display.font);
    }

    if (engine->gameTimer.display.textSurface != NULL) {
        SDL_FreeSurface(engine->gameTimer.display.textSurface);
    }

    /* Free engine structure */
    free(engine);
}

/**
 * @brief Transition to a new game state
 * @param engine The game engine
 * @param newState The new state
 */
void GameEngine_SetState(GameEngine *engine, GameState newState)
{
    if (engine == NULL) {
        return;
    }

    engine->previousState = engine->currentState;
    engine->currentState = newState;
}

/**
 * @brief Get current game state
 * @param engine The game engine
 * @return Current state
 */
GameState GameEngine_GetState(GameEngine *engine)
{
    if (engine == NULL) {
        return STATE_QUIT;
    }
    return engine->currentState;
}

/**
 * @brief Handle SDL input events
 * @param engine The game engine
 * @param event SDL event to process
 */
void GameEngine_HandleInput(GameEngine *engine, SDL_Event *event)
{
    if (engine == NULL || event == NULL) {
        return;
    }

    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {
        case SDLK_RIGHT:
            engine->inputKeyRight = true;
            break;
        case SDLK_LEFT:
            engine->inputKeyLeft = true;
            break;
        case SDLK_UP:
            engine->inputKeyUp = true;
            break;
        case SDLK_DOWN:
            engine->inputKeyDown = true;
            break;
        case SDLK_ESCAPE:
            engine->isRunning = 0;
            break;
        case SDLK_f:
            engine->shouldFullscreen = !engine->shouldFullscreen;
            SDL_WM_ToggleFullScreen(engine->screen);
            break;
        default:
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event->key.keysym.sym) {
        case SDLK_RIGHT:
            engine->inputKeyRight = false;
            break;
        case SDLK_LEFT:
            engine->inputKeyLeft = false;
            break;
        case SDLK_UP:
            engine->inputKeyUp = false;
            break;
        case SDLK_DOWN:
            engine->inputKeyDown = false;
            break;
        default:
            break;
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (event->button.button == SDL_BUTTON_LEFT) {
            engine->mouseX = event->button.x;
            engine->mouseY = event->button.y;
            engine->mouseLeftClicked = true;
        }
        break;

    case SDL_MOUSEBUTTONUP:
        if (event->button.button == SDL_BUTTON_LEFT) {
            engine->mouseLeftClicked = false;
        }
        break;

    case SDL_MOUSEMOTION:
        engine->mouseX = event->motion.x;
        engine->mouseY = event->motion.y;
        break;

    default:
        break;
    }
}

/**
 * @brief Update game logic based on current state
 * @param engine The game engine
 */
void GameEngine_Update(GameEngine *engine)
{
    if (engine == NULL) {
        return;
    }

    /* State-specific updates */
    switch (engine->currentState) {
    case STATE_MENU:
        /* Menu state: handle menu navigation and selection */
        if (engine->mouseLeftClicked) {
            /* Check menu button clicks */
            /* Play button handling */
            if (engine->mouseX >= PLAY_BUTTON_X && 
                engine->mouseX <= PLAY_BUTTON_X + BUTTON_WIDTH &&
                engine->mouseY >= PLAY_BUTTON_Y && 
                engine->mouseY <= PLAY_BUTTON_Y + BUTTON_HEIGHT) {
                engine->currentState = STATE_GAMEPLAY;
            }
            /* Settings button handling */
            else if (engine->mouseX >= SETTINGS_BUTTON_X && 
                     engine->mouseX <= SETTINGS_BUTTON_X + BUTTON_WIDTH &&
                     engine->mouseY >= SETTINGS_BUTTON_Y && 
                     engine->mouseY <= SETTINGS_BUTTON_Y + BUTTON_HEIGHT) {
                engine->currentState = STATE_SETTINGS;
            }
            /* Quit button handling */
            else if (engine->mouseX >= QUIT_BUTTON_X && 
                     engine->mouseX <= QUIT_BUTTON_X + BUTTON_WIDTH &&
                     engine->mouseY >= QUIT_BUTTON_Y && 
                     engine->mouseY <= QUIT_BUTTON_Y + BUTTON_HEIGHT) {
                engine->currentState = STATE_QUIT;
            }
            engine->mouseLeftClicked = false;
        }
        break;

    case STATE_SETTINGS:
        /* Settings state: handle settings menu */
        if (engine->inputKeyDown) {
            engine->menuSelection = (engine->menuSelection + 1) % 3;
            engine->inputKeyDown = false;
        }
        if (engine->inputKeyUp) {
            engine->menuSelection = (engine->menuSelection - 1 + 3) % 3;
            engine->inputKeyUp = false;
        }
        /* Return to menu with ESC or back selection */
        if (engine->inputKeyLeft || (engine->menuSelection == 0 && engine->mouseLeftClicked)) {
            engine->currentState = STATE_MENU;
            engine->mouseLeftClicked = false;
        }
        break;

    case STATE_GAMEPLAY:
        /* Game state: update is handled in game_loop() */
        break;

    case STATE_PUZZLE:
        /* Puzzle update logic: handle puzzle interactions and timer */
        if (engine->gameTimer.seconds > (PUZZLE_TIME_LIMIT / 1000)) {
            engine->currentState = STATE_GAMEPLAY;
        }
        break;

    case STATE_MINIGAME:
        /* Minigame update logic: handled separately in minigame functions */
        break;

    case STATE_PAUSE:
        /* Pause state: resume or quit to menu */
        if (engine->inputKeyDown) {
            engine->menuSelection = (engine->menuSelection + 1) % 2;
            engine->inputKeyDown = false;
        }
        if (engine->inputKeyUp) {
            engine->menuSelection = (engine->menuSelection - 1 + 2) % 2;
            engine->inputKeyUp = false;
        }
        /* Resume game */
        if (engine->menuSelection == 0 && engine->inputKeyUp) {
            engine->currentState = STATE_GAMEPLAY;
        }
        /* Return to menu */
        else if (engine->menuSelection == 1 && engine->inputKeyDown) {
            engine->currentState = STATE_MENU;
        }
        break;

    case STATE_GAME_OVER:
        /* Game over state: wait for player to restart or return to menu */
        if (engine->mouseLeftClicked) {
            engine->currentState = STATE_MENU;
            engine->mouseLeftClicked = false;
        }
        if (engine->inputKeyUp) {
            engine->currentState = STATE_MENU;
            engine->inputKeyUp = false;
        }
        break;

    case STATE_QUIT:
        engine->isRunning = 0;
        break;

    default:
        break;
    }
}

/**
 * @brief Render current frame based on state
 * @param engine The game engine
 */
void GameEngine_Render(GameEngine *engine)
{
    if (engine == NULL || engine->screen == NULL) {
        return;
    }

    /* Clear screen */
    SDL_FillRect(engine->screen, NULL, SDL_MapRGB(engine->screen->format, 0, 0, 0));

    /* State-specific rendering */
    switch (engine->currentState) {
    case STATE_MENU:
        /* Render menu background */
        if (engine->menuBg.sprites[0] != NULL) {
            SDL_BlitSurface(engine->menuBg.sprites[0], NULL, engine->screen, NULL);
        }
        
        /* Render animated logo */
        if (engine->menuLogo.sprites[engine->menuLogo.currentFrame] != NULL) {
            SDL_Rect logoPos = {
                (SCREEN_WIDTH - engine->menuLogo.sprites[engine->menuLogo.currentFrame]->w) / 2,
                50,
                0, 0
            };
            SDL_BlitSurface(engine->menuLogo.sprites[engine->menuLogo.currentFrame], 
                          NULL, engine->screen, &logoPos);
        }
        
        /* Render menu buttons */
        if (engine->buttonPlay.sprites[0] != NULL) {
            SDL_Rect playPos = {PLAY_BUTTON_X, PLAY_BUTTON_Y, 0, 0};
            SDL_BlitSurface(engine->buttonPlay.sprites[0], NULL, engine->screen, &playPos);
        }
        if (engine->buttonSettings.sprites[0] != NULL) {
            SDL_Rect settingsPos = {SETTINGS_BUTTON_X, SETTINGS_BUTTON_Y, 0, 0};
            SDL_BlitSurface(engine->buttonSettings.sprites[0], NULL, engine->screen, &settingsPos);
        }
        if (engine->buttonQuit.sprites[0] != NULL) {
            SDL_Rect quitPos = {QUIT_BUTTON_X, QUIT_BUTTON_Y, 0, 0};
            SDL_BlitSurface(engine->buttonQuit.sprites[0], NULL, engine->screen, &quitPos);
        }
        break;

    case STATE_SETTINGS:
        /* Render settings screen with menu items */
        if (engine->menuBg.sprites[1] != NULL) {
            SDL_BlitSurface(engine->menuBg.sprites[1], NULL, engine->screen, NULL);
        }
        /* Settings options would be rendered here based on menuSelection */
        break;

    case STATE_GAMEPLAY:
        /* Game rendering is handled by game_loop() */
        break;

    case STATE_PUZZLE:
        /* Render puzzle interface */
        if (engine->background.backgroundImage != NULL) {
            SDL_BlitSurface(engine->background.backgroundImage, NULL, engine->screen, NULL);
        }
        
        /* Render puzzle question and answers */
        if (engine->currentPuzzle.questionSurface != NULL) {
            SDL_Rect qPos = {PUZZLE_QUESTION_X, PUZZLE_QUESTION_Y, 0, 0};
            SDL_BlitSurface(engine->currentPuzzle.questionSurface, NULL, engine->screen, &qPos);
        }
        
        if (engine->currentPuzzle.answer1Surface != NULL) {
            SDL_Rect a1Pos = {PUZZLE_ANSWER1_X, PUZZLE_ANSWER1_Y, 0, 0};
            SDL_BlitSurface(engine->currentPuzzle.answer1Surface, NULL, engine->screen, &a1Pos);
        }
        if (engine->currentPuzzle.answer2Surface != NULL) {
            SDL_Rect a2Pos = {PUZZLE_ANSWER2_X, PUZZLE_ANSWER2_Y, 0, 0};
            SDL_BlitSurface(engine->currentPuzzle.answer2Surface, NULL, engine->screen, &a2Pos);
        }
        if (engine->currentPuzzle.answer3Surface != NULL) {
            SDL_Rect a3Pos = {PUZZLE_ANSWER3_X, PUZZLE_ANSWER3_Y, 0, 0};
            SDL_BlitSurface(engine->currentPuzzle.answer3Surface, NULL, engine->screen, &a3Pos);
        }
        
        /* Render puzzle timer */
        if (engine->gameTimer.display.textSurface != NULL) {
            SDL_Rect timerPos = {TIMER_X, TIMER_Y, 0, 0};
            SDL_BlitSurface(engine->gameTimer.display.textSurface, NULL, engine->screen, &timerPos);
        }
        break;

    case STATE_MINIGAME:
        /* Render minigame (Connect-4) - handled by minigame functions */
        /* This is typically rendered within the minigame function itself */
        break;

    case STATE_PAUSE:
        /* Render pause overlay */
        SDL_FillRect(engine->screen, NULL, SDL_MapRGB(engine->screen->format, 0, 0, 0));
        
        /* Render pause menu text */
        if (engine->menuText.textSurface != NULL) {
            SDL_Rect pausePos = {
                (SCREEN_WIDTH - engine->menuText.textSurface->w) / 2,
                (SCREEN_HEIGHT - engine->menuText.textSurface->h) / 2,
                0, 0
            };
            SDL_BlitSurface(engine->menuText.textSurface, NULL, engine->screen, &pausePos);
        }
        
        /* Render pause menu options based on menuSelection */
        break;

    case STATE_GAME_OVER:
        /* Render game over screen */
        if (engine->menuBg.sprites[2] != NULL) {
            SDL_BlitSurface(engine->menuBg.sprites[2], NULL, engine->screen, NULL);
        }
        
        /* Render game over message */
        if (engine->menuText.textSurface != NULL) {
            SDL_Rect gameOverPos = {
                (SCREEN_WIDTH - engine->menuText.textSurface->w) / 2,
                (SCREEN_HEIGHT - engine->menuText.textSurface->h) / 2,
                0, 0
            };
            SDL_BlitSurface(engine->menuText.textSurface, NULL, engine->screen, &gameOverPos);
        }
        break;

    default:
        break;
    }

    /* Update display */
    SDL_Flip(engine->screen);
}
