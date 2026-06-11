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
