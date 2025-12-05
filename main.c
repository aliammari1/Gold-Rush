#include "core.h"

/**
 * @brief Initialize SDL and game systems
 * @return 0 on success, 1 on failure
 */
int initializeGameSystems(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        printf("TTF initialization failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
        printf("Audio initialization failed: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    return 0;
}

/**
 * @brief Main application entry point
 * @return 0 on success, 1 on error
 */
int main(void)
{
    GameEngine *gameEngine = NULL;
    Uint32 frameStart = 0;
    Uint32 frameTime = 0;
    
    /* Initialize SDL and subsystems */
    if (initializeGameSystems() != 0) {
        return 1;
    }

    /* Create and initialize game engine */
    gameEngine = GameEngine_Create();
    if (gameEngine == NULL) {
        printf("Failed to create game engine\n");
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    /* Set initial state to menu */
    GameEngine_SetState(gameEngine, STATE_MENU);
    gameEngine->isRunning = 1;

    /* Main game loop - run until STATE_QUIT or isRunning is false */
    while (gameEngine->isRunning && gameEngine->currentState != STATE_QUIT) {
        frameStart = SDL_GetTicks();

        /* Handle input events */
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            GameEngine_HandleInput(gameEngine, &event);
            
            if (event.type == SDL_QUIT) {
                gameEngine->isRunning = 0;
            }
        }

        /* Update game logic based on current state */
        GameEngine_Update(gameEngine);

        /* Special handling for gameplay state - run actual game loop */
        if (gameEngine->currentState == STATE_GAMEPLAY) {
            game_loop(gameEngine);
            /* After game loop, return to menu */
            GameEngine_SetState(gameEngine, STATE_MENU);
        }
        /* Special handling for puzzle state */
        else if (gameEngine->currentState == STATE_PUZZLE) {
            /* Puzzle game would be called here */
            GameEngine_SetState(gameEngine, STATE_GAMEPLAY);
        }
        /* Special handling for minigame state */
        else if (gameEngine->currentState == STATE_MINIGAME) {
            /* Minigame would be called here - runConnectFourGame() */
            GameEngine_SetState(gameEngine, STATE_GAMEPLAY);
        }
        /* For menu and settings, use normal rendering */
        else {
            /* Render frame based on current state */
            GameEngine_Render(gameEngine);
        }

        /* Frame rate limiting */
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_TIME_MS) {
            SDL_Delay(FRAME_TIME_MS - frameTime);
        }
    }

    /* Cleanup and shutdown */
    GameEngine_Destroy(gameEngine);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
