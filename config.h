#ifndef CONFIG_H
#define CONFIG_H

/* Game Window Configuration */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 639
#define GAME_WIDTH 1280
#define GAME_HEIGHT 419
#define SCREEN_BPP 32

/* Game Settings */
#define TARGET_FPS 60
#define FRAME_TIME_MS (1000 / TARGET_FPS)
#define MAX_PLAYERS 2

/* Player Configuration */
#define PLAYER_BASE_VELOCITY 5
#define PLAYER_MAX_VELOCITY 10
#define PLAYER_ACCELERATION 0.01f
#define PLAYER_FRICTION 0.001f
#define PLAYER_JUMP_FRAMES 20

/* Sprite Configuration */
#define NUM_DIRECTIONS 6
#define NUM_FRAMES_PER_DIRECTION 12
#define SPRITE_SHEET_COLS 12

/* Enemy Configuration */
#define ENEMY_SPEED 5
#define ENEMY_SPAWN_X 300
#define ENEMY_SPAWN_Y 200

/* Minimap Configuration */
#define MINIMAP_POSITION_X 1000
#define MINIMAP_POSITION_Y 100
#define MINIMAP_PLAYER_SIZE 10
#define MINIMAP_SCALE_FACTOR 10

/* UI Configuration */
#define BUTTON_WIDTH 158
#define BUTTON_HEIGHT 70

#define PLAY_BUTTON_X 565
#define PLAY_BUTTON_Y 296
#define BUTTON_PLAY_W 158
#define BUTTON_PLAY_H 70

#define SETTINGS_BUTTON_X 565
#define SETTINGS_BUTTON_Y 416
#define BUTTON_SETTINGS_W 284
#define BUTTON_SETTINGS_H 70

#define QUIT_BUTTON_X 565
#define QUIT_BUTTON_Y 530
#define BUTTON_QUIT_W 158
#define BUTTON_QUIT_H 100

#define BUTTON_FULLSCREEN_X 565
#define BUTTON_FULLSCREEN_Y 296

/* Puzzle UI Positions */
#define PUZZLE_QUESTION_X 200
#define PUZZLE_QUESTION_Y 100
#define PUZZLE_ANSWER1_X 200
#define PUZZLE_ANSWER1_Y 250
#define PUZZLE_ANSWER2_X 200
#define PUZZLE_ANSWER2_Y 350
#define PUZZLE_ANSWER3_X 200
#define PUZZLE_ANSWER3_Y 450

/* Timer Display Positions */
#define TIMER_X 50
#define TIMER_Y 50

/* Font Configuration */
#define FONT_SMALL_SIZE 20
#define FONT_MEDIUM_SIZE 30
#define FONT_LARGE_SIZE 60

/* Asset Paths */
#define ASSET_PATH "assets/"
#define FONT_DEFAULT "assets/angelina.TTF"
#define FONT_LARGE "assets/Trajan Pro.ttf"
#define MUSIC_BACKGROUND "assets/musique.mp3"
#define SOUND_CLICK "assets/videoplayback.wav"

/* Timer Configuration */
#define PUZZLE_TIME_LIMIT 16000  /* milliseconds */
#define TIMER_UPDATE_FREQUENCY 1000

/* Puzzle Configuration */
#define NUM_ANSWERS 3
#define PUZZLE_SCORE_CORRECT 20
#define PUZZLE_SCORE_WRONG -20

/* Minigame (Connect Four) Configuration */
#define GAME_BOARD_ROWS 6
#define GAME_BOARD_COLS 7
#define GAME_BOARD_START_X 150
#define GAME_BOARD_START_Y 0
#define GAME_WINDOW_WIDTH 1250
#define GAME_WINDOW_HEIGHT 800

/* Collision Configuration */
#define COLLISION_CHECK_OFFSET 100  /* pixels */
#define PIXEL_COLLISION_BLACK_R 0
#define PIXEL_COLLISION_BLACK_G 0
#define PIXEL_COLLISION_BLACK_B 0

#endif /* CONFIG_H */
