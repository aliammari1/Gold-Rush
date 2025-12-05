# Quick Start Guide - Game States & Controls

## Game States

| State | Description | How to Reach | Exit Method |
|-------|-------------|-------------|-------------|
| **MENU** | Main menu with Play/Settings/Quit | Startup or from gameplay | Click buttons |
| **SETTINGS** | Settings navigation menu | From menu: Settings button | Back button or ESC |
| **GAMEPLAY** | Active game with player & enemy | From menu: Play button | Press ESC or P |
| **PUZZLE** | Quiz/riddle challenge | Triggered during gameplay | Timer expires or answer |
| **MINIGAME** | Connect-4 game | Triggered during gameplay | Win/Lose |
| **PAUSE** | Game paused, resume options | During gameplay: Press P | Resume or Quit |
| **GAME_OVER** | Game ended screen | Automatic on player loss | Click or press key |
| **QUIT** | Application exit | From menu: Quit button | Program terminates |

## Controls

### Menu Controls
- **Left Click**: Select menu option (Play, Settings, Quit)
- **1 Key**: Select Player 1
- **2 Key**: Select Player 2
- **Up/Down**: Navigate menu items

### Gameplay Controls
- **Left Arrow**: Move left
- **Right Arrow**: Move right
- **Up Arrow**: Jump
- **P Key**: Pause/Resume game
- **ESC Key**: Return to menu
- **F Key**: Toggle fullscreen

### Pause Menu Controls
- **Up/Down Arrows**: Navigate between Resume and Quit
- **Enter**: Select option
- **P Key**: Quick resume

## Key Functions

### State Machine
```c
GameEngine_SetState(engine, STATE_MENU);      // Change state
GameState state = GameEngine_GetState(engine); // Query current state
GameEngine_Update(engine);                     // Update state logic
GameEngine_Render(engine);                     // Render state visuals
```

### Game Loop
```c
int result = game_loop(engine);  // Run gameplay loop
```

### Player Selection
```c
selectPlayer(&playerNum, screen);  // Player select UI
```

## Menu Button Positions

### Main Menu
- **Play Button**: (565, 296) size 158×70
- **Settings Button**: (565, 416) size 284×70
- **Quit Button**: (565, 530) size 158×100

## Game Parameters

| Parameter | Value | Location |
|-----------|-------|----------|
| FPS Target | 60 | config.h |
| Screen Width | 1280 | config.h |
| Screen Height | 639 | config.h |
| Game Width | 1280 | config.h |
| Game Height | 419 | config.h |
| Player Max Velocity | 10 | config.h |
| Enemy Speed | 5 | config.h |
| Puzzle Time Limit | 16 seconds | config.h |

## File Structure

```
.
├── game (executable - 158KB)
├── main.c (application entry point)
├── game_state.c (state machine)
├── game_loop.c (gameplay loop)
├── player.c (player system)
├── enemy.c (enemy system)
├── puzzle.c (puzzle system)
├── minigame.c (minigame loop)
├── timer.c (timer system)
├── ui.c (background/UI)
├── world.c (minimap/scoring)
├── utils.c (menu utilities)
├── core.h (main header)
├── types.h (type definitions)
├── config.h (configuration)
├── game_state.h (state machine header)
└── assets/ (game resources)
    ├── images/ (player/enemy sprites)
    ├── music/ (background music)
    └── questionsans (puzzle questions)
```

## Debugging Tips

### Enable Console Output
```c
printf("Current state: %d\n", GameEngine_GetState(engine));
```

### State Values
- STATE_MENU = 0
- STATE_SETTINGS = 1
- STATE_GAMEPLAY = 2
- STATE_PUZZLE = 3
- STATE_MINIGAME = 4
- STATE_PAUSE = 5
- STATE_GAME_OVER = 6
- STATE_QUIT = 7

### Check Resource Loading
```c
if (surface == NULL) {
    printf("Failed to load resource: %s\n", IMG_GetError());
}
```

## Common Issues & Solutions

### Game Won't Start
- Check that all asset files exist in `assets/` directory
- Verify SDL libraries are installed
- Check console output for initialization errors

### Buttons Not Responding
- Verify button positions match screen coordinates
- Check that SDL_Event is being processed
- Ensure GameEngine_HandleInput() is being called

### Game Crashes on Transition
- Check for NULL pointer dereferences
- Verify all resources are allocated before use
- Ensure proper cleanup in state transitions

### Performance Issues
- Check if FPS is being limited correctly
- Monitor memory usage (should be stable)
- Verify no infinite loops in state logic

## Compilation

### Quick Compile
```bash
cd /workspaces/C-GAME-PROJECT
make clean
make
```

### Run Game
```bash
./game
```

### Clean Build Artifacts
```bash
make clean
```

## Next Steps

1. **Test Basic Flow**: Start game → Play → Pause → Resume → Menu → Quit
2. **Test All States**: Visit all 8 states and verify transitions
3. **Test Controls**: Verify all keyboard inputs work correctly
4. **Test UI**: Click all menu buttons and verify hit detection
5. **Stress Test**: Play for extended period, check for memory leaks
6. **Edge Cases**: Close window during gameplay, rapid transitions

---

**Version**: 1.0  
**Last Updated**: 2025-12-05  
**Status**: ✅ Ready for Testing
