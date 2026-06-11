# Play in browser

!!! warning "Work in progress"
    The browser build is being developed on the `feat/sdl2-wasm` branch and
    is **not yet released**. The link below is a placeholder until the SDL 2
    + Emscripten port is compile-verified and deployed.

Gold Rush is being ported from SDL 1.2 to **SDL 2** so it can be compiled to
**WebAssembly** with Emscripten and played directly in the browser, with no
install. The web build will be hosted on **Cloudflare Pages**.

**Play now:** _coming soon_ — `https://gold-rush.pages.dev`

## How it works

- The Makefile gains a `make wasm` target that compiles with `emcc` and
  `-sUSE_SDL=2`, preloading `assets/` via `--preload-file`.
- The blocking `while (isRunning)` main loop is refactored to use
  `emscripten_set_main_loop()` under `#ifdef __EMSCRIPTEN__`, because a
  blocking loop hangs the browser tab.
- A Cloudflare Pages deploy workflow publishes the generated
  `game.html` / `game.wasm` / `game.data` bundle.

Native binaries for Linux and macOS are published on the
[GitHub Releases](https://github.com/aliammari1/Gold-Rush/releases) page.
