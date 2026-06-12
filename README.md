<!-- Hero banner: generate from the prompt in BANNER.md, commit to
     assets/banner/banner-wide.png, then swap the comment below for:
     ![Gold Rush](assets/banner/banner-wide.png)
     (1280x640 social-preview spec also in BANNER.md). -->

# Gold Rush

🎮 **A 2D platformer written in pure C + SDL — plays in your browser via WebAssembly.**

### ▶ [Play in browser](https://gold-rush.pages.dev) &nbsp;·&nbsp; ⬇ [Download](https://github.com/aliammari1/Gold-Rush/releases) &nbsp;·&nbsp; 🎮 [itch.io](https://aliammari1.itch.io/gold-rush) &nbsp;·&nbsp; ⭐ [Star this repo](https://github.com/aliammari1/Gold-Rush)

> The in-browser demo is a **pure-C game compiled to WebAssembly** (Emscripten)
> hosted on Cloudflare Pages — no install, no toolchain. It is built from the
> [`feat/sdl2-wasm`](https://github.com/aliammari1/Gold-Rush/tree/feat/sdl2-wasm)
> branch (`make wasm`), which ports the renderer from SDL 1.2 to SDL 2 +
> Emscripten; the link goes live once that build is published. See
> [docs/play-in-browser.md](docs/play-in-browser.md).

[![CI](https://github.com/aliammari1/Gold-Rush/actions/workflows/ci-cpp.yml/badge.svg?branch=master)](https://github.com/aliammari1/Gold-Rush/actions/workflows/ci-cpp.yml)
[![CodeQL](https://github.com/aliammari1/Gold-Rush/actions/workflows/codeql.yml/badge.svg?branch=master)](https://github.com/aliammari1/Gold-Rush/actions/workflows/codeql.yml)
[![OpenSSF Scorecard](https://api.scorecard.dev/projects/github.com/aliammari1/Gold-Rush/badge)](https://scorecard.dev/viewer/?uri=github.com/aliammari1/Gold-Rush)
[![codecov](https://codecov.io/gh/aliammari1/Gold-Rush/branch/master/graph/badge.svg)](https://codecov.io/gh/aliammari1/Gold-Rush)
[![Language: C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![SDL 1.2](https://img.shields.io/badge/SDL-1.2-green.svg)](https://www.libsdl.org/)
[![License: Zlib](https://img.shields.io/badge/license-Zlib-blue.svg)](LICENSE)

A state-machine game engine with physics-based movement, an enemy AI, a timed
quiz puzzle, and a **Connect Four** minigame backed by a depth-limited
**alpha-beta (minimax)** CPU opponent — all in a few thousand lines of plain C.

> **Gameplay GIF:** _coming soon_ — a short capture of the platformer,
> puzzle, and Connect Four modes will live here (see [BANNER.md](BANNER.md)).

## Play it

Three one-click ways to play — **no toolchain required:**

| | How | Notes |
|---|---|---|
| ▶ **Browser (WASM)** | [gold-rush.pages.dev](https://gold-rush.pages.dev) | Pure C → WebAssembly, hosted on Cloudflare Pages. The hero demo. Built from [`feat/sdl2-wasm`](https://github.com/aliammari1/Gold-Rush/tree/feat/sdl2-wasm). |
| ⬇ **Download** | [Releases](https://github.com/aliammari1/Gold-Rush/releases) | Prebuilt **Linux** + **macOS** tarballs per tag, with [SLSA build provenance](https://github.com/aliammari1/Gold-Rush/attestations) (verify with `gh attestation verify`). Built by the [release workflow](.github/workflows/release.yml). |
| 🎮 **itch.io** | [aliammari1.itch.io/gold-rush](https://aliammari1.itch.io/gold-rush) | WASM build runs in itch's HTML5 player; native tarballs downloadable. Auto-published with `butler` ([itch workflow](.github/workflows/itch.yml)). |

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
in the browser** — handy as a learning reference or a starting point. Launch
plan, topics, and submission kit live in [GROWTH.md](GROWTH.md).

- **Topics:** `gamedev` · `sdl` · `c` · `platformer` · `wasm` · `emscripten`
  · `indie-game` · `2d-game` (set under the repo's About panel).
- **Show it off:** the "pure C, plays in browser" angle suits a _Show HN_ post
  and shares to [r/gamedev](https://www.reddit.com/r/gamedev/) /
  [r/C_Programming](https://www.reddit.com/r/C_Programming/) — see GROWTH.md.
- **awesome-c / awesome-sdl:** a candidate for the *Games* sections of
  [awesome-c](https://github.com/oz123/awesome-c) and
  [awesome-sdl](https://github.com/0n3m4n/awesome-sdl).

Contributions are welcome — see [CONTRIBUTING.md](CONTRIBUTING.md) for the
C coding standards and how to add levels and enemies.

## License

Released under the [Zlib license](LICENSE).

## Author

**Ali Ammari** — [@aliammari1](https://github.com/aliammari1)

---

### Related projects

- 🎮 **Games:** [games](https://github.com/aliammari1/games) — browser games
  incl. an unbeatable minimax tic-tac-toe.
- 🧠 **AI / apps:** [JobPrep](https://github.com/aliammari1/JobPrep) ·
  [readrealm](https://github.com/aliammari1/readrealm) ·
  [pulmocare](https://github.com/aliammari1/pulmocare)
- 📊 **Dev tools:** [github-traffic-analytics](https://github.com/aliammari1/github-traffic-analytics)
  · [awesome-ai-tools](https://github.com/aliammari1/awesome-ai-tools)
- 👤 **All projects:** [github.com/aliammari1](https://github.com/aliammari1)
