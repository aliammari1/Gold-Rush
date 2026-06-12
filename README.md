<!-- Hero banner: generate from the prompt in BANNER.md, commit to
     assets/banner/banner-wide.png, then swap the comment below for:
     ![Gold Rush](assets/banner/banner-wide.png)
     (1280x640 social-preview spec also in BANNER.md). -->

# Gold Rush

A 2D platformer written in **C** with **SDL 1.2**. It pairs a state-machine
game engine with physics-based movement, an enemy AI, a timed quiz puzzle,
and a **Connect Four** minigame backed by a depth-limited **alpha-beta
(minimax)** CPU opponent.

[![CI](https://github.com/aliammari1/Gold-Rush/actions/workflows/ci-cpp.yml/badge.svg?branch=master)](https://github.com/aliammari1/Gold-Rush/actions/workflows/ci-cpp.yml)
[![CodeQL](https://github.com/aliammari1/Gold-Rush/actions/workflows/codeql.yml/badge.svg?branch=master)](https://github.com/aliammari1/Gold-Rush/actions/workflows/codeql.yml)
[![Language: C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![SDL 1.2](https://img.shields.io/badge/SDL-1.2-green.svg)](https://www.libsdl.org/)
[![License: Zlib](https://img.shields.io/badge/license-Zlib-blue.svg)](LICENSE)

> **Gameplay GIF:** _coming soon_ — a short capture of the platformer,
> puzzle, and Connect Four modes will live here.

## Play it

Three ways to play — **no toolchain required for the first two:**

### Play in browser (WebAssembly)

The headline demo is a **pure-C game compiled to WebAssembly** and hosted on
**Cloudflare Pages** — it plays directly in the browser, no install.

**Play now:** _coming soon_ — `https://gold-rush.pages.dev`

> The browser build is produced from the `feat/sdl2-wasm` branch, which ports
> the renderer from SDL 1.2 to **SDL 2 + Emscripten** (`make wasm`). It must
> be compiled from that branch before the link goes live — see
> [docs/play-in-browser.md](docs/play-in-browser.md).

### Download a binary (Releases)

Prebuilt **Linux** and **macOS** binaries are published for every tagged
version on the [Releases](https://github.com/aliammari1/Gold-Rush/releases)
page (built by the [release workflow](.github/workflows/release.yml)).

### itch.io

Gold Rush is cross-posted to **[itch.io](https://aliammari1.itch.io/gold-rush)**
— the WebAssembly build runs in itch's HTML5 player and the native tarballs
are downloadable there. Publishing is automated with `butler` via the
[itch.io workflow](.github/workflows/itch.yml).

Or build it yourself from source (below).

## Features

- State-machine engine (menu, settings, gameplay, pause, puzzle, minigame).
- Physics-based player movement: acceleration, friction, arc-based jumps.
- Enemy AI that tracks the player.
- Timed quiz puzzle (+20 / -20 scoring, 16-second limit).
- **Connect Four vs CPU** with an alpha-beta minimax opponent
  ([how it works](docs/connect-four-ai.md)).
- Split-screen two-player mode, parallax backgrounds, and a live minimap.

## Build

The game builds with `make` and links the SDL 1.2 family
(`-lSDL -lSDL_ttf -lSDL_image -lSDL_mixer`). Assets are loaded by relative
path, so run `./game` from the repository root.

### Linux

```bash
# Ubuntu / Debian
sudo apt-get update
sudo apt-get install -y build-essential \
  libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
make
./game
```

```bash
# Fedora / RHEL
sudo dnf install gcc make SDL-devel SDL_image-devel SDL_ttf-devel SDL_mixer-devel
make && ./game
```

```bash
# Arch
sudo pacman -S base-devel sdl sdl_image sdl_ttf sdl_mixer
make && ./game
```

### macOS

SDL 1.2 is end-of-life; build against the `sdl12-compat` shim:

```bash
brew install sdl12-compat sdl_image sdl_mixer sdl_ttf
make && ./game
```

### Windows

Native SDL 1.2 on Windows is fiddly — use WSL with the Linux steps above,
or wait for the in-browser WebAssembly build.

## Controls

| Mode | Input | Action |
|------|-------|--------|
| Menu | ↑ / ↓, Enter | Navigate, select |
| Gameplay | ← / → | Move |
| Gameplay | ↑ | Jump |
| Gameplay | P / Esc | Pause / back to menu |
| Settings | F | Toggle fullscreen |
| Puzzle | 1 / 2 / 3 | Answer |
| Connect Four | Click column | Drop token |

Full reference: [docs/controls.md](docs/controls.md).

## Tests

The Connect Four AI is pure C and builds without SDL:

```bash
make -C tests          # build and run the unit tests
make -C tests sanitize # run under AddressSanitizer + UBSan
```

The suite (Unity) asserts win detection in every direction, move legality,
win/block tactics, and that the minimax opponent **never loses** to weaker
play.

## Documentation

Built with Material for MkDocs (`mkdocs serve`, sources in `docs/`):

- [Building](docs/building.md)
- [Controls](docs/controls.md)
- [Architecture](docs/architecture.md)
- [Connect Four AI](docs/connect-four-ai.md)
- [Play in browser](docs/play-in-browser.md)

## Engineering decisions

- **License: Zlib.** The de-facto standard for game projects — permissive,
  commercial-use friendly, attribution preserved. It removes the
  contribution-suppressing restrictions of a source-available license.
- **SDL-free AI.** Connect Four's decision logic lives in `connect4_ai.c`
  with no SDL dependency, so it is unit-testable anywhere and cleanly
  separated from rendering.
- **Cloudflare Pages** for the WASM "play in browser" build and the docs
  site (free tier, no Node burden for the C/MkDocs toolchain).

## Community & sharing

Gold Rush is a small, self-contained example of a **pure-C game that plays
in the browser** — handy as a learning reference or a starting point.

- **Topics:** `gamedev` · `sdl` · `c` · `platformer` · `indie-game`
  (set under the repo's About panel for discoverability).
- **Show it off:** the "pure C, plays in browser" angle suits a
  _Show HN_ post and an [r/gamedev](https://www.reddit.com/r/gamedev/)
  share once the WASM demo is live.
- **awesome-c:** a candidate for the *Games* section of
  [awesome-c](https://github.com/oz123/awesome-c) — submit once the browser
  demo and a gameplay GIF are published.

Contributions are welcome — see [CONTRIBUTING.md](CONTRIBUTING.md) for the
C coding standards and how to add levels and enemies.

## License

Released under the [Zlib license](LICENSE).

## Author

**Ali Ammari** — [@aliammari1](https://github.com/aliammari1)
