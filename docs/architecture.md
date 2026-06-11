# Architecture

Gold Rush is organized as small, single-responsibility translation units
wired together through `core.h` (the single include hub) and a central
`GameEngine` state machine.

## State machine

```
STATE_MENU ──► STATE_SETTINGS
   │
   ├──► STATE_GAMEPLAY ──► STATE_PAUSE
   │            ├──► STATE_PUZZLE
   │            └──► STATE_MINIGAME (Connect Four vs CPU)
   │
   └──► STATE_QUIT
```

The main loop in `main.c` polls SDL events, updates the engine, and renders
based on `currentState`. Entering `STATE_MINIGAME` launches Connect Four
against the minimax CPU.

## Modules

| Area | Files |
|------|-------|
| Entry / loop | `main.c`, `game_loop.c` |
| Engine / state | `game_state.c`, `game_state.h` |
| Player | `player.c`, `player.h` |
| Enemy AI | `enemy.c`, `enemy.h` |
| World / camera / minimap | `world.c`, `world.h` |
| UI / rendering | `ui.c`, `ui.h` |
| Quiz puzzle | `puzzle.c`, `puzzle_game.c`, `puzzle.h` |
| Connect Four (SDL) | `minigame.c`, `minigame_utils.c`, `minigame.h` |
| Connect Four (logic) | `connect4_ai.c`, `connect4_ai.h` |
| Timer | `timer.c`, `timer.h` |
| Config / types | `config.h`, `types.h` |

## Design note: SDL-free AI

The Connect Four decision logic lives in `connect4_ai.c`, which has **no SDL
dependency**. This keeps the algorithm unit-testable on any machine with a C
compiler (see `tests/`) and cleanly separates game rules from rendering.

## Configuration

All tunable constants (screen size, physics, scoring, asset paths, board
geometry) live in `config.h`.
