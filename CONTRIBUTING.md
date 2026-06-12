# Contributing to Gold Rush

Thanks for your interest in improving Gold Rush! This is a C / SDL 1.2
game; contributions of all sizes are welcome.

## Getting set up

1. Install the SDL 1.2 toolchain for your OS — see the
   [build instructions](README.md#build).
2. Build the game: `make` then `./game` (run from the repo root so
   relative asset paths resolve).
3. Run the AI unit tests (no SDL needed): `make -C tests`.

## Coding standards

- **C99**, built with `-Wall -Wextra`. New code should compile warning-free.
- 4-space indentation, Allman braces — see `.clang-format`
  (`clang-format -i <file>` to auto-format).
- Add a `/* SPDX-License-Identifier: Zlib */` header to new source files.
- Document new public functions with Doxygen-style comments.
- Put tunable constants in `config.h`, not magic numbers in code.
- Keep gameplay logic SDL-free where practical so it can be unit-tested
  (see `connect4_ai.c` as the model).

## Adding content

**A new enemy.** Enemy state and behaviour live in `enemy.c` / `enemy.h`.
Add the enemy's data to the enemy struct/array, give it an update function
that moves it relative to the player (see the existing tracking logic), and
load its sprite from `assets/` by relative path. Keep tunables (speed,
detection range, damage) in `config.h`.

**A new level / world.** Level geometry and backgrounds are handled in
`world.c` / `world.h`. Add the parallax background art under `assets/`
(follow the `back0.jpg`, `back1.jpg` … numbering), register the layer, and
wire collision/spawn points through the world setup. Reuse the camera and
minimap code rather than duplicating it.

**A new puzzle question or minigame.** Quiz questions are driven by
`puzzle.c` / `puzzle_game.c`; the Connect Four minigame lives in
`minigame.c` with its SDL-free AI in `connect4_ai.c`. Keep any new decision
logic SDL-free and add a Unity test under `tests/` (the Connect Four suite
is the model).

After adding content, update [docs/](docs/) and the README controls table if
the player-facing behaviour changed.

## Before opening a PR

- `make clean && make` builds with no new warnings.
- `make -C tests` passes (and `make -C tests sanitize` if you touched the
  Connect Four logic).
- Fill in the pull-request template, including the affected game modes.

## Commit messages

Use clear, imperative messages (e.g. "Fix Connect Four block detection").
Conventional Commit prefixes are welcome but not required.

## Reporting bugs

Open an issue with the bug-report template. Security issues should follow
[SECURITY.md](SECURITY.md) instead.
