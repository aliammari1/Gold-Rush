#include "core.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

/**
 * @brief Initialize SDL and game systems
 * @return 0 on success, 1 on failure
 */
int initializeGameSystems(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
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
 * @brief Run a single frame: input, update, state-specific work, render.
 *
 * Extracted from the old blocking while-loop so the frame can be driven
 * either by a native loop or by emscripten_set_main_loop() in the browser.
 *
 * NOTE (NEEDS COMPILE VERIFICATION): the gameplay/minigame branches below
 * still call functions (game_loop, runConnectFourGame*) that contain their
 * own blocking `while` loops. Under Emscripten those nested loops will also
 * need to be converted to per-frame steppers; only the top-level loop is
 * converted here.
 */
static void runOneFrame(GameEngine *gameEngine)
{
    Uint32 frameStart = SDL_GetTicks();
    Uint32 frameTime;
    SDL_Event event;

    /* Handle input events */
    while (SDL_PollEvent(&event)) {
        GameEngine_HandleInput(gameEngine, &event);

        if (event.type == SDL_QUIT) {
            gameEngine->isRunning = 0;
        }
    }

    /* Update game logic based on current state */
    GameEngine_Update(gameEngine);

    if (gameEngine->currentState == STATE_GAMEPLAY) {
        game_loop(gameEngine);
        GameEngine_SetState(gameEngine, STATE_MENU);
    } else if (gameEngine->currentState == STATE_PUZZLE) {
        /* Puzzle game would be called here */
        GameEngine_SetState(gameEngine, STATE_GAMEPLAY);
    } else if (gameEngine->currentState == STATE_MINIGAME) {
        /* Connect Four vs CPU would be launched here. */
        GameEngine_SetState(gameEngine, STATE_GAMEPLAY);
    } else {
        GameEngine_Render(gameEngine);
    }

    /* Frame rate limiting (native only; the browser paces via rAF). */
#ifndef __EMSCRIPTEN__
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_TIME_MS) {
        SDL_Delay(FRAME_TIME_MS - frameTime);
    }
#else
    (void)frameStart;
    (void)frameTime;
#endif
}

#ifdef __EMSCRIPTEN__
/* Adapter matching em_arg_callback_func; stops the loop on quit. */
static void emscriptenFrame(void *arg)
{
    GameEngine *gameEngine = (GameEngine *)arg;
    if (!gameEngine->isRunning || gameEngine->currentState == STATE_QUIT) {
        emscripten_cancel_main_loop();
        GameEngine_Destroy(gameEngine);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return;
    }
    runOneFrame(gameEngine);
}
#endif

/**
 * @brief Main application entry point
 * @return 0 on success, 1 on error
 */
int main(void)
{
    GameEngine *gameEngine = NULL;

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

#ifdef __EMSCRIPTEN__
    /* In the browser the main thread must return so the page stays
     * responsive. Drive the game one frame per animation frame (fps=0).
     * A blocking while-loop here would hang the tab. */
    emscripten_set_main_loop_arg(emscriptenFrame, gameEngine, 0, 1);
    /* emscripten_set_main_loop_arg with simulate_infinite_loop=1 does not
     * return; cleanup happens in emscriptenFrame on quit. */
    return 0;
#else
    /* Native blocking loop. */
    while (gameEngine->isRunning && gameEngine->currentState != STATE_QUIT) {
        runOneFrame(gameEngine);
    }

    /* Cleanup and shutdown */
    GameEngine_Destroy(gameEngine);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
#endif
}
