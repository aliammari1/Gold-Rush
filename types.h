#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* SDL 2 headers. sdl12_compat_shim.h maps the legacy SDL 1.2 video API
 * (SDL_SetVideoMode / SDL_Flip / SDL_WM_*) onto SDL 2 so the rest of the
 * codebase compiles unchanged. */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "sdl12_compat_shim.h"
#include "config.h"

/**
 * @enum PlayerDirection
 * @brief Player movement directions
 */
typedef enum {
    DIR_IDLE_RIGHT = 0,
    DIR_MOVING_RIGHT = 1,
    DIR_IDLE_LEFT = 2,
    DIR_MOVING_LEFT = 3,
    DIR_JUMP_RIGHT = 4,
    DIR_JUMP_LEFT = 5
} PlayerDirection;

/**
 * @enum EnemyAIState
 * @brief Enemy AI states
 */
typedef enum {
    ENEMY_WAITING = 0,
    ENEMY_FOLLOWING = 1
} EnemyAIState;

/**
 * @struct Player
 * @brief Player character structure
 */
typedef struct {
    SDL_Rect position;              /*!< Position on screen */
    SDL_Rect relativePosition;      /*!< Position relative to jump arc */
    SDL_Surface *sprites[NUM_DIRECTIONS][NUM_FRAMES_PER_DIRECTION]; /*!< Sprite sheets */
    float velocityX;                /*!< Horizontal velocity */
    PlayerDirection direction;      /*!< Current direction state */
    int currentFrame;               /*!< Current animation frame */
    int lastDirection;              /*!< Last direction pressed (0=right, 1=left) */
    int isJumping;                  /*!< Jump state */
} Player;

/**
 * @struct Enemy
 * @brief Enemy character structure
 */
typedef struct {
    int direction;                  /*!< Direction: 0=right, 1=left */
    SDL_Rect screenPosition;        /*!< Position on screen */
    SDL_Rect spritePosition;        /*!< Position on sprite sheet */
    SDL_Surface *spriteSheet;       /*!< Enemy sprite sheet */
    EnemyAIState state;             /*!< AI state */
} Enemy;

/**
 * @struct TextDisplay
 * @brief Text rendering structure
 */
typedef struct {
    SDL_Surface *textSurface;       /*!< Rendered text surface */
    SDL_Rect textPosition;          /*!< Position on screen */
    char textBuffer[20];            /*!< Text content */
    SDL_Color textColor;            /*!< Text color */
    TTF_Font *font;                 /*!< Font for rendering */
} TextDisplay;

/**
 * @struct GameTimer
 * @brief Game timer structure
 */
typedef struct {
    int startTime;                  /*!< Start time in ms */
    int minutes;                    /*!< Minutes elapsed */
    int seconds;                    /*!< Seconds elapsed */
    TextDisplay display;            /*!< Display info */
} GameTimer;

/**
 * @struct Background
 * @brief Background and world structure
 */
typedef struct {
    SDL_Surface *backgroundImage;   /*!< Background image */
    SDL_Rect displayPosition;       /*!< Position on screen */
    SDL_Rect camera;                /*!< Camera viewport */
    SDL_Rect cloudPosition;         /*!< Cloud animation position */
    SDL_Surface *cloudImage;        /*!< Cloud image */
} Background;

/**
 * @struct Minimap
 * @brief Minimap display structure
 */
typedef struct {
    SDL_Surface *minimapImage;      /*!< Minimap image */
    SDL_Rect minimapPosition;       /*!< Position on screen */
    SDL_Surface *playerIndicator;   /*!< Player marker */
    SDL_Rect playerMapPosition;     /*!< Position on minimap */
} Minimap;

/**
 * @struct Puzzle
 * @brief Quiz puzzle structure
 */
typedef struct {
    char questionText[100];         /*!< Question text */
    char answer1[100];              /*!< Answer 1 */
    char answer2[100];              /*!< Answer 2 */
    char answer3[100];              /*!< Answer 3 */
    int correctAnswer;              /*!< Correct answer number (1-3) */
    SDL_Surface *questionSurface;   /*!< Rendered question */
    SDL_Surface *answer1Surface;    /*!< Rendered answer 1 */
    SDL_Surface *answer2Surface;    /*!< Rendered answer 2 */
    SDL_Surface *answer3Surface;    /*!< Rendered answer 3 */
    SDL_Rect questionPosition;      /*!< Position on screen */
    SDL_Rect answer1Position;       /*!< Answer 1 position */
    SDL_Rect answer2Position;       /*!< Answer 2 position */
    SDL_Rect answer3Position;       /*!< Answer 3 position */
} Puzzle;

/**
 * @struct GameCell
 * @brief Connect-4 game cell
 */
typedef struct {
    int column;
    int row;
} GameCell;

/**
 * @struct MenuButton
 * @brief Menu button structure
 */
typedef struct {
    SDL_Surface *sprites[2];        /*!< Normal and hovered sprites */
    SDL_Rect position;              /*!< Button position */
    int isHighlighted;              /*!< Highlight state */
} MenuButton;

/**
 * @struct MenuBackground
 * @brief Menu background animation
 */
typedef struct {
    SDL_Surface *sprites[3];        /*!< Animation frames */
    SDL_Rect position;              /*!< Position on screen */
    int currentFrame;               /*!< Current animation frame */
} MenuBackground;

/**
 * @struct MenuLogo
 * @brief Menu logo animation
 */
typedef struct {
    SDL_Surface *sprites[11];       /*!< Animation frames */
    SDL_Rect position;              /*!< Position on screen */
    int currentFrame;               /*!< Current animation frame */
} MenuLogo;

/**
 * @struct MenuText
 * @brief Menu text display
 */
typedef struct {
    SDL_Rect position;              /*!< Position on screen */
    TTF_Font *font;                 /*!< Font for rendering */
    SDL_Surface *textSurface;       /*!< Rendered text */
    SDL_Color textColor;            /*!< Text color */
    char text[50];                  /*!< Text content */
} MenuText;

/**
 * @struct GameImage
 * @brief Simple image structure
 */
typedef struct {
    SDL_Surface *image;             /*!< Image surface */
    SDL_Rect position;              /*!< Position on screen */
} GameImage;

/**
 * @struct BackgroundMusic
 * @brief Background music structure
 */
typedef struct {
    Mix_Music *music;               /*!< Music data */
    SDL_Rect position;              /*!< Display position */
    SDL_Surface *albumArt;          /*!< Album art image */
    int trackNumber;                /*!< Track number */
} BackgroundMusic;

#endif /* TYPES_H */
