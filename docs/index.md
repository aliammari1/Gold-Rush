# Gold Rush

A 2D platformer written in **C** with **SDL 1.2**. It bundles a state-machine
game engine, physics-based movement, an enemy AI, a timed quiz puzzle, and a
**Connect Four** minigame with a depth-limited **alpha-beta (minimax)** CPU
opponent.

!!! note "Status"
    The native game targets SDL 1.2. A SDL 2 + WebAssembly (Emscripten)
    "play in browser" build is in progress on the `feat/sdl2-wasm` branch —
    see [Play in browser](play-in-browser.md).

## Quick links

- [Building from source](building.md)
- [Controls](controls.md)
- [Architecture overview](architecture.md)
- [How the Connect Four AI works](connect-four-ai.md)

## License

Gold Rush is released under the [Zlib license](https://opensource.org/license/zlib),
the de-facto standard for game projects: permissive, commercial-use friendly,
with attribution preserved.
