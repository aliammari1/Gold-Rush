# Open Source Growth Plan

This plan converts the repository review into a practical backlog for Gold Rush.

## Quick wins

- Add gameplay GIFs and screenshots to the README.
- Add prebuilt release artifacts for Windows, Linux, and macOS when practical.
- Add a GitHub Actions build that compiles the C/SDL project on pull requests.
- Add a sanitizer/debug build target for memory and undefined-behavior checks.
- Add labels such as `good first issue`, `gameplay`, `docs`, and `bug`.
- Add a short trailer or itch.io page and link it from the README.

## Bugs and bad practices to watch

- Memory leaks around textures, audio assets, and level resources.
- Collision logic regressions that are hard to catch manually.
- Global mutable state that makes gameplay behavior difficult to test.
- Platform-specific build assumptions in Makefiles or local scripts.
- Missing input validation for level files or save data.

## Star growth strategy

1. Put visual proof of the game above the fold in the README.
2. Publish binary releases so visitors can play without compiling.
3. Create beginner issues for sprites, levels, sound effects, and documentation.
4. Add a short architecture document so contributors can find the game loop, physics, rendering, and input code quickly.
5. Share playable releases in game-dev communities and link back to the repository.

## Trending-library opportunities

- Use AI-assisted tooling outside the C runtime to generate level ideas, design notes, and playtest checklists.
- Use MarkItDown-style conversion for turning design documents into Markdown docs.
- Use small agent patterns for experimental NPC behavior prototypes before porting logic into C.

## Suggested next PRs

- Add CI compilation for the current supported platform.
- Add `docs/ARCHITECTURE.md` with the game loop, modules, and asset pipeline.
- Add a debug build target with sanitizers.
