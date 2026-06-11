/* SPDX-License-Identifier: Zlib */
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "types.h"

/**
 * @enum GameState
 * @brief Main game states
 */
typedef enum
{
    STATE_MENU = 0,      /*!< Main menu */
    STATE_SETTINGS = 1,  /*!< Settings menu */
    STATE_GAMEPLAY = 2,  /*!< Active gameplay */
    STATE_PUZZLE = 3,    /*!< Quiz puzzle */
    STATE_MINIGAME = 4,  /*!< Connect-4 minigame */
    STATE_PAUSE = 5,     /*!< Game paused */
    STATE_GAME_OVER = 6, /*!< Game over */
    STATE_QUIT = 7       /*!< Exit game */
} GameState;

/**
 * @enum MenuSelection
 * @brief Menu navigation states
 */
typedef enum
{
    MENU_PLAY = 0,     /*!< Play game selected */
    MENU_SETTINGS = 1, /*!< Settings selected */
    MENU_QUIT = 2      /*!< Quit selected */
} MenuSelection;

/**
 * @struct GameEngine
 * @brief Main game engine state
 */
typedef struct
{
    GameState currentState;      /*!< Current game state */
    GameState previousState;     /*!< Previous game state */
    MenuSelection menuSelection; /*!< Current menu selection */
    int numPlayers;              /*!< Number of active players (1 or 2) */
    int playerScore;             /*!< Current player score */
    int isRunning;               /*!< Game is running flag */
    int shouldFullscreen;        /*!< Fullscreen toggle */

    /* Game objects */
    Player player;         /*!< Player 1 */
    Player player2;        /*!< Player 2 */
    Enemy enemy;           /*!< Enemy entity */
    Background background; /*!< World background */
    Minimap minimap;       /*!< Minimap display */
    GameTimer gameTimer;   /*!< Game timer */
    GameTimer puzzleTimer; /*!< Puzzle timer */
    Puzzle currentPuzzle;  /*!< Current puzzle */

    /* Input state */
    bool inputKeyRight;    /*!< Right key pressed */
    bool inputKeyLeft;     /*!< Left key pressed */
    bool inputKeyUp;       /*!< Up key pressed */
    bool inputKeyDown;     /*!< Down key pressed */
    int mouseX;            /*!< Mouse X position */
    int mouseY;            /*!< Mouse Y position */
    bool mouseLeftClicked; /*!< Left mouse button clicked */

    /* Rendering */
    SDL_Surface *screen;        /*!< Main screen surface */
    SDL_Surface *collisionMask; /*!< Collision detection mask */

    /* UI Elements */
    MenuButton buttonPlay;              /*!< Play button */
    MenuButton buttonSettings;          /*!< Settings button */
    MenuButton buttonQuit;              /*!< Quit button */
    MenuButton buttonFullscreen;        /*!< Fullscreen button */
    MenuBackground menuBg;              /*!< Menu background */
    MenuLogo menuLogo;                  /*!< Menu logo */
    MenuText menuText;                  /*!< Menu text */
    GameImage logoGroupe;               /*!< Group logo */
    GameImage teamLogo;                 /*!< Team logo */
    GameImage witcherImage;             /*!< The Witcher image */
    BackgroundMusic backgroundMusic[5]; /*!< Background music tracks */
    Mix_Chunk *clickSound;              /*!< Click sound effect */
} GameEngine;

/**
 * @brief Initialize the game engine
 * @return GameEngine pointer or NULL on error
 */
GameEngine *GameEngine_Create(void);

/**
 * @brief Destroy the game engine and free resources
 * @param engine The game engine pointer
 */
void GameEngine_Destroy(GameEngine *engine);

/**
 * @brief Transition to a new game state
 * @param engine The game engine
 * @param newState The new state to transition to
 */
void GameEngine_SetState(GameEngine *engine, GameState newState);

/**
 * @brief Get the current game state
 * @param engine The game engine
 * @return Current game state
 */
GameState GameEngine_GetState(GameEngine *engine);

/**
 * @brief Handle input events
 * @param engine The game engine
 * @param event SDL event to process
 */
void GameEngine_HandleInput(GameEngine *engine, SDL_Event *event);

/**
 * @brief Update game logic
 * @param engine The game engine
 */
void GameEngine_Update(GameEngine *engine);

/**
 * @brief Render game frame
 * @param engine The game engine
 */
void GameEngine_Render(GameEngine *engine);

#endif /* GAME_STATE_H */
