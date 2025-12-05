# 🎮 GOLD RUSH

<div align="center">


**A Feature-Rich 2D Platformer Game Built with SDL in C**

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![SDL](https://img.shields.io/badge/SDL-1.2-green.svg)](https://www.libsdl.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg)](https://www.linux.org/)

[Features](#-features) • [Installation](#-installation) • [Gameplay](#-gameplay) • [Controls](#-controls) • [Architecture](#-architecture) • [Contributing](#-contributing)

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Screenshots](#-screenshots)
- [Installation](#-installation)
  - [Prerequisites](#prerequisites)
  - [Building from Source](#building-from-source)
- [Gameplay](#-gameplay)
- [Controls](#-controls)
- [Game Modes](#-game-modes)
- [Project Structure](#-project-structure)
- [Architecture](#-architecture)
- [Technical Details](#-technical-details)
- [Configuration](#-configuration)
- [Assets](#-assets)
- [Development](#-development)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [License](#-license)
- [Credits](#-credits)

---

## 🌟 Overview

This is a comprehensive 2D platformer game developed in **C** using the **SDL (Simple DirectMedia Layer)** library. The game features a sophisticated game engine with multiple game states, physics-based movement, AI enemies, puzzle challenges, and mini-games. It demonstrates advanced C programming techniques including modular architecture, state machines, sprite animation, collision detection, and audio integration.

### Key Highlights

- 🎯 **State Machine Architecture** - Robust game state management system
- 🏃 **Physics-Based Movement** - Realistic player movement with acceleration, friction, and jumping mechanics
- 🤖 **AI Enemy System** - Intelligent enemy AI with following behavior
- 🧩 **Puzzle Mini-Game** - Quiz-based puzzles with scoring system
- 🎲 **Connect Four Game** - Fully playable Connect Four mini-game
- 👥 **Multiplayer Support** - Split-screen two-player mode
- 🗺️ **Minimap System** - Real-time minimap with player tracking
- 🎨 **Sprite Animation** - Multi-directional character sprites with smooth animations
- 🎵 **Audio System** - Background music and sound effects
- ⚙️ **Settings Menu** - Customizable game settings including fullscreen mode

---

## ✨ Features

### Core Gameplay Features

- **Advanced Player Movement System**
  - Velocity-based movement with acceleration
  - Friction and deceleration
  - Jump mechanics with arc-based physics
  - Multi-directional sprite animations (idle, walking, jumping)

- **Enemy AI**
  - State-based AI (waiting, following)
  - Player tracking and pursuit
  - Collision detection

- **Game States**
  - Main Menu
  - Settings Menu
  - Active Gameplay
  - Puzzle Mode
  - Mini-Game Mode
  - Pause State
  - Game Over

### Mini-Games

- **Quiz Puzzle System**
  - Timed questions with multiple-choice answers
  - Score tracking (correct: +20, wrong: -20)
  - 16-second time limit per puzzle
  - Visual feedback

- **Connect Four**
  - Classic Connect Four gameplay
  - AI opponent
  - 6x7 game board
  - Win condition detection

### Visual & Audio

- **Graphics**
  - Parallax scrolling backgrounds
  - Cloud animations
  - Sprite-based character animations (12 frames per direction)
  - Split-screen rendering for multiplayer
  - Minimap with real-time player tracking

- **Audio**
  - Background music system
  - Sound effects (click sounds, etc.)
  - SDL_mixer integration

### Technical Features

- **60 FPS** frame rate targeting
- **1280x639** screen resolution (customizable)
- **Modular architecture** with clear separation of concerns
- **Memory management** with proper initialization and cleanup
- **Collision detection** system
- **Camera system** with viewport management
- **Score persistence** system

---

## 📸 Screenshots

> *Add your game screenshots here*

```
[Main Menu]  [Gameplay]  [Puzzle Mode]  [Minimap]
```

---

## 🚀 Installation

### Prerequisites

Before building the game, ensure you have the following dependencies installed:

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install libsdl1.2-dev
sudo apt-get install libsdl-image1.2-dev
sudo apt-get install libsdl-ttf2.0-dev
sudo apt-get install libsdl-mixer1.2-dev
```

#### Fedora/RHEL
```bash
sudo dnf install gcc make
sudo dnf install SDL-devel
sudo dnf install SDL_image-devel
sudo dnf install SDL_ttf-devel
sudo dnf install SDL_mixer-devel
```

#### Arch Linux
```bash
sudo pacman -S base-devel
sudo pacman -S sdl sdl_image sdl_ttf sdl_mixer
```

### Building from Source

1. **Clone the repository**
   ```bash
   git clone https://github.com/aliammari1/C-GAME-PROJECT.git
   cd C-GAME-PROJECT
   ```

2. **Build the game**
   ```bash
   make clean all
   ```

3. **Run the game**
   ```bash
   make run
   # or directly
   ./game
   ```

### Build Options

- **Clean build artifacts:**
  ```bash
  make clean
  ```

- **Build only (without running):**
  ```bash
  make all
  ```

- **Debug build:**
  The makefile includes `-g` flag for debugging. Use with gdb:
  ```bash
  gdb ./game
  ```

---

## 🎮 Gameplay

The game is a side-scrolling platformer where you control a character navigating through a world filled with enemies and challenges. Your objective is to:

1. **Navigate the Environment** - Use arrow keys to move and jump
2. **Avoid or Defeat Enemies** - Enemy AI will track and follow you
3. **Complete Puzzles** - Answer quiz questions within the time limit
4. **Play Mini-Games** - Challenge yourself with Connect Four
5. **Score Points** - Track your progress with the scoring system
6. **Use the Minimap** - Navigate using the real-time minimap display

### Game Flow

```
Main Menu → Select Mode → Gameplay → Puzzles/Mini-Games → Game Over → Menu
     ↓
  Settings ← → Fullscreen Toggle
     ↓
   Quit
```

---

## 🎯 Controls

### Main Menu
| Key | Action |
|-----|--------|
| `↑` / `↓` | Navigate menu options |
| `Enter` | Select menu item |
| `Mouse` | Click buttons |

### Gameplay
| Key | Action |
|-----|--------|
| `→` | Move right |
| `←` | Move left |
| `↑` | Jump |
| `P` | Pause/Unpause |
| `ESC` | Return to menu |

### Settings
| Key | Action |
|-----|--------|
| `F` | Toggle fullscreen |
| `ESC` | Return to menu |

### Puzzle Mode
| Key | Action |
|-----|--------|
| `1` / `2` / `3` | Select answer |
| `Mouse` | Click answer |

### Mini-Game (Connect Four)
| Mouse | Action |
|-------|--------|
| `Click Column` | Drop token |

---

## 🎲 Game Modes

### 🏃 Single Player Mode
Navigate through the world, complete challenges, and achieve the highest score.

### 👥 Two Player Mode
Split-screen multiplayer experience with independent camera systems.

### 🧩 Puzzle Mode
Answer timed quiz questions:
- **Correct Answer:** +20 points
- **Wrong Answer:** -20 points
- **Time Limit:** 16 seconds per question

### 🎯 Mini-Game: Connect Four
Classic strategy game against AI opponent:
- 6 rows × 7 columns board
- First to connect 4 wins
- AI with intelligent move selection

---

## 📁 Project Structure

```
C-GAME-PROJECT/
│
├── 📄 main.c                 # Entry point and initialization
├── 📄 core.h                 # Core header with all includes
├── 📄 config.h               # Game configuration constants
├── 📄 types.h                # Type definitions and structures
│
├── 🎮 Game Engine
│   ├── game_loop.c           # Main game loop
│   ├── game_state.c          # State machine implementation
│   └── game_state.h          # State definitions
│
├── 👤 Player System
│   ├── player.c              # Player logic and physics
│   └── player.h              # Player declarations
│
├── 👾 Enemy System
│   ├── enemy.c               # Enemy AI and behavior
│   └── enemy.h               # Enemy declarations
│
├── 🎨 UI & Rendering
│   ├── ui.c                  # UI rendering functions
│   └── ui.h                  # UI declarations
│
├── 🌍 World
│   ├── world.c               # World, minimap, scoring
│   └── world.h               # World declarations
│
├── 🧩 Puzzle System
│   ├── puzzle.c              # Quiz puzzle logic
│   ├── puzzle.h              # Puzzle declarations
│   └── puzzle_game.c         # Puzzle game implementation
│
├── 🎲 Mini-Game
│   ├── minigame.c            # Connect Four logic
│   ├── minigame.h            # Mini-game declarations
│   ├── minigame_utils.c      # Mini-game utilities
│   └── menu_keyboard.c       # Menu input handling
│
├── ⏱️ Timer System
│   ├── timer.c               # Timer implementation
│   └── timer.h               # Timer declarations
│
├── 🛠️ Utilities
│   └── utils.c               # Utility functions
│
├── 📦 Assets
│   ├── images/               # Sprite sheets and graphics
│   ├── music/                # Background music
│   ├── song/                 # Sound effects
│   ├── logo/                 # Logo assets
│   ├── *.ttf                 # Font files
│   └── *.png, *.jpg, *.bmp   # Image files
│
└── 📋 makefile               # Build configuration
```

---

## 🏗️ Architecture

### State Machine

The game uses a robust state machine pattern for managing game flow:

```
┌─────────────┐
│  STATE_MENU │ ◄──────────────────┐
└──────┬──────┘                    │
       │                           │
       ├─► STATE_SETTINGS          │
       │                           │
       ├─► STATE_GAMEPLAY ────────►│
       │         │                 │
       │         ├─► STATE_PAUSE   │
       │         │                 │
       │         ├─► STATE_PUZZLE ─┤
       │         │                 │
       │         └─► STATE_MINIGAME│
       │                           │
       └─► STATE_QUIT              │
                                   │
       STATE_GAME_OVER ────────────┘
```

### Module Organization

The codebase follows a modular architecture with clear separation of concerns:

1. **Core Systems**
   - Game Engine (state management, main loop)
   - Input handling
   - Rendering pipeline

2. **Game Logic**
   - Player system (physics, animation)
   - Enemy system (AI, collision)
   - World system (background, camera, minimap)

3. **Mini-Games**
   - Puzzle system (questions, scoring, timer)
   - Connect Four (board logic, AI)

4. **Utilities**
   - Timer system
   - UI components
   - Asset management

### Data Structures

#### GameEngine
The central structure managing the entire game:
```c
typedef struct {
    GameState currentState;      // Current state
    GameState previousState;     // For state transitions
    MenuSelection menuSelection; // Menu navigation
    int numPlayers;             // 1 or 2 players
    int playerScore;            // Current score
    int isRunning;              // Game running flag
    Player player;              // Player 1
    Player player2;             // Player 2
    Enemy enemy;                // Enemy entity
    Background background;       // World and camera
    Minimap minimap;            // Minimap display
    GameTimer gameTimer;        // Timer system
    // ... more fields
} GameEngine;
```

#### Player
Physics-based player with sprite animation:
```c
typedef struct {
    SDL_Rect position;           // Screen position
    SDL_Rect relativePosition;   // Jump arc position
    SDL_Surface *sprites[6][12]; // 6 directions × 12 frames
    float velocityX;             // Horizontal velocity
    PlayerDirection direction;   // Current direction
    int currentFrame;            // Animation frame
    int isJumping;               // Jump state
} Player;
```

---

## 🔧 Technical Details

### Graphics System

- **Rendering:** SDL 1.2 software rendering
- **Sprites:** Multi-frame sprite sheets with 12 frames per direction
- **Animations:** Frame-based animation system at 60 FPS
- **Camera:** Viewport-based camera system with smooth scrolling
- **Collision:** Pixel-perfect collision detection using color masks

### Physics Engine

- **Movement:** Velocity-based with acceleration/deceleration
  - Base velocity: 5 units
  - Max velocity: 10 units
  - Acceleration: 0.01 units per frame
  - Friction: 0.001 units per frame

- **Jumping:** Arc-based jump system
  - Jump duration: 20 frames
  - Parabolic trajectory

### Audio System

- **Music:** Background music using SDL_mixer
- **Sound Effects:** Click sounds and effects
- **Audio Format:** 44100 Hz, stereo, 1024 byte chunks

### Performance

- **Target FPS:** 60
- **Frame Time:** ~16.67ms per frame
- **Resolution:** 1280×639 pixels (16:10 aspect ratio)
- **Game Area:** 1280×419 pixels (UI takes bottom portion)

---

## ⚙️ Configuration

All game constants can be modified in `config.h`:

### Display Settings
```c
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 639
#define SCREEN_BPP 32
#define TARGET_FPS 60
```

### Player Physics
```c
#define PLAYER_BASE_VELOCITY 5
#define PLAYER_MAX_VELOCITY 10
#define PLAYER_ACCELERATION 0.01f
#define PLAYER_FRICTION 0.001f
#define PLAYER_JUMP_FRAMES 20
```

### Puzzle Settings
```c
#define PUZZLE_TIME_LIMIT 16000        // milliseconds
#define PUZZLE_SCORE_CORRECT 20
#define PUZZLE_SCORE_WRONG -20
```

### UI Positions
```c
#define MINIMAP_POSITION_X 1000
#define MINIMAP_POSITION_Y 100
#define TIMER_X 50
#define TIMER_Y 50
```

---

## 🎨 Assets

### Required Assets

The game requires the following assets in the `assets/` directory:

#### Fonts
- `angelina.TTF` - Default UI font
- `Trajan Pro.ttf` - Large title font
- `arial.ttf` - Alternative font
- `alger.TTF` - Additional font

#### Images
- **Backgrounds:** `back0.jpg`, `back1.jpg`, `back2.jpg`, `bg.png`, `fond.png`
- **UI Elements:** `play0.png`, `play1.png`, `settings0.png`, `settings1.png`, `quit0.png`, `quit1.png`
- **Game Elements:** `cloud.png`, `mini_backgg.png`, `skulltest.png`
- **Tokens:** `rouge.png`, `jaune.png` (Connect Four)
- **Sprites:** Player and enemy sprite sheets in `images/` subdirectories

#### Audio
- **Music:** Background music files in `music/` and `song/`
- **SFX:** `videoplayback.wav`, `Mouse_Click.wav`, `audio.wav`, `effet.wav`

#### Logos
- Team and game logos in `logo/` directory

### Asset Organization
```
assets/
├── images/
│   ├── 0/ ... 5/    # Sprite sheets organized by direction
├── music/           # Background music tracks
├── song/            # Sound effects
├── logo/            # Logo files
└── [root files]     # Fonts, UI elements, backgrounds
```

---

## 🛠️ Development

### Compilation Flags

```makefile
CFLAGS := -g -Wall -Wextra -Wno-unused-parameter
```

- `-g`: Debug symbols for gdb
- `-Wall -Wextra`: Enable all warnings
- `-Wno-unused-parameter`: Suppress unused parameter warnings

### Libraries

```makefile
LIBS := -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer
```

### Adding New Features

1. **New Game State:**
   - Add state to `GameState` enum in `game_state.h`
   - Implement state logic in `game_state.c`
   - Add rendering in `GameEngine_Render()`

2. **New Character/Enemy:**
   - Define structure in `types.h`
   - Implement init/update/render functions
   - Add to game engine structure

3. **New Mini-Game:**
   - Create new `.c` and `.h` files
   - Add state to `GameState` enum
   - Implement game logic and integrate into main loop

### Debugging

**Using GDB:**
```bash
make clean all
gdb ./game
(gdb) run
(gdb) break main
(gdb) continue
```

**Common Debug Points:**
- `main.c:33` - Game engine creation
- `game_loop.c:30` - Game loop start
- `game_state.c` - State transitions
- `player.c` - Player physics

---

## 🐛 Troubleshooting

### Common Issues

#### SDL Initialization Failure
```
SDL initialization failed: [error]
```
**Solution:** Ensure SDL libraries are properly installed
```bash
sudo apt-get install --reinstall libsdl1.2-dev
```

#### Missing Assets
```
Failed to load: assets/[filename]
```
**Solution:** Verify assets are in the correct directory structure

#### Compilation Errors
```
undefined reference to `SDL_*`
```
**Solution:** Check that SDL libraries are linked correctly in makefile

#### Audio Issues
```
Audio initialization failed
```
**Solution:** Ensure SDL_mixer is installed and audio device is available
```bash
sudo apt-get install libsdl-mixer1.2-dev
```

#### Font Loading Failure
```
TTF initialization failed
```
**Solution:** Verify SDL_ttf is installed and font files exist
```bash
sudo apt-get install libsdl-ttf2.0-dev
```

### Performance Issues

- **Low FPS:** Reduce sprite resolution or disable cloud animations
- **Memory Leaks:** Ensure proper cleanup in `GameEngine_Destroy()`
- **Stuttering:** Check for blocking I/O operations

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### How to Contribute

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/amazing-feature
   ```
3. **Commit your changes**
   ```bash
   git commit -m "Add amazing feature"
   ```
4. **Push to the branch**
   ```bash
   git push origin feature/amazing-feature
   ```
5. **Open a Pull Request**

### Contribution Guidelines

- Follow the existing code style
- Comment your code appropriately
- Test your changes thoroughly
- Update documentation if needed
- Keep commits atomic and well-described

### Areas for Contribution

- 🎮 New mini-games or puzzles
- 🎨 Additional sprites and animations
- 🤖 Enhanced enemy AI
- 🎵 More sound effects and music
- 🌍 New levels or world designs
- 🐛 Bug fixes and optimizations
- 📚 Documentation improvements
- 🧪 Unit tests

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 Ali Ammari

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 👥 Credits

### Development Team

**Ali Ammari** - Project Lead & Developer
- GitHub: [@aliammari1](https://github.com/aliammari1)

### Technologies Used

- **SDL 1.2** - Simple DirectMedia Layer
- **SDL_image** - Image loading library
- **SDL_ttf** - TrueType font rendering
- **SDL_mixer** - Audio mixing library
- **GCC** - GNU Compiler Collection

### Special Thanks

- SDL Development Team for the amazing multimedia library
- All contributors and testers
- Open source community

---

## 📞 Contact

**Ali Ammari**
- GitHub: [@aliammari1](https://github.com/aliammari1)
- Repository: [C-GAME-PROJECT](https://github.com/aliammari1/C-GAME-PROJECT)

---

## 🔗 Links

- [SDL Official Website](https://www.libsdl.org/)
- [SDL Documentation](https://wiki.libsdl.org/)
- [Project Repository](https://github.com/aliammari1/C-GAME-PROJECT)
- [Issue Tracker](https://github.com/aliammari1/C-GAME-PROJECT/issues)

---

## 📊 Project Status

**Current Version:** 1.0.0  
**Status:** Active Development  
**Last Updated:** December 2025

### Roadmap

- [ ] Level editor
- [ ] Save/Load game state
- [ ] Achievement system
- [ ] Networked multiplayer
- [ ] Mobile port (SDL2 migration)
- [ ] Steam integration
- [ ] Modding support

---

<div align="center">

**⭐ Star this repository if you found it helpful! ⭐**

Made with ❤️ using C and SDL

[Back to Top](#-c-game-project)

</div>
