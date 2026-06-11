# SDL 1.2 → SDL 2 + WebAssembly migration

> **STATUS: NEEDS COMPILE VERIFICATION.** This branch ports Gold Rush from
> SDL 1.2 to SDL 2 and adds an Emscripten/WebAssembly build. It has **not**
> been compiled against real SDL2 / emcc headers (no SDL2 dev libs or
> Emscripten SDK were available on the authoring machine). Build it with
> SDL2 and `emcc` before merging.

## What changed

### SDL 2 port via a compatibility shim
- `sdl12_compat_shim.{h,c}` reimplements the SDL 1.2 video API on SDL 2:
  - `SDL_SetVideoMode` → a single `SDL_CreateWindow` + `SDL_GetWindowSurface`
    (resized on subsequent calls, since the menu/minigame/puzzle each call
    `SDL_SetVideoMode` to "switch resolution").
  - `SDL_Flip` → `SDL_UpdateWindowSurface`.
  - `SDL_WM_SetCaption` → `SDL_SetWindowTitle`.
  - `SDL_WM_ToggleFullScreen` → `SDL_SetWindowFullscreen` (desktop).
  - Dead SDL 1.2 surface flags (`SDL_HWSURFACE`, `SDL_DOUBLEBUF`, …) become
    no-op `#define`s so existing flag expressions still compile.
- `types.h` now includes `<SDL2/SDL.h>` (+ image/ttf/mixer) and the shim;
  `minigame.c` / `minigame_utils.c` drop their direct `<SDL/...>` includes.
- Surface blitting, SDL_image/ttf/mixer, and the event/keysym API are
  source-compatible between SDL 1.2 and SDL 2, so call sites are unchanged.
  A repo-wide scan found none of the tricky SDL-1.2-only APIs
  (`SDL_SetColorKey` old signature, `SDL_DisplayFormat`,
  `SDL_GetKeyState`, `keysym.unicode`, `SDL_EnableKeyRepeat`, …).

### Emscripten main loop
- `main.c` extracts the per-frame work into `runOneFrame()` and, under
  `#ifdef __EMSCRIPTEN__`, drives it with `emscripten_set_main_loop_arg()`
  (fps=0 → requestAnimationFrame, `simulate_infinite_loop=1`). The native
  build keeps a blocking `while` loop. A blocking loop in the browser hangs
  the tab, so this is required.

### Build
- `makefile`: native libs `-lSDL*` → `-lSDL2*` (pkg-config when present);
  new `make wasm` target compiling with `-sUSE_SDL=2` (+ image/ttf/mixer
  ports) and `--preload-file assets`.

### CI / deploy (gated)
- `.github/workflows/wasm-deploy.yml` — build the WASM bundle with emsdk
  and deploy to Cloudflare Pages (gated on CF secrets).
- `.github/workflows/itch.yml` — publish the HTML5 build to itch.io with
  butler on tags (gated on `BUTLER_API_KEY` / `ITCH_*`).

## Remaining work before merge (must compile-verify)

1. Build natively against SDL2 (`make`) and fix any header/flag fallout.
2. Build the web bundle (`emcc … make wasm`) and load `game.html`.
3. **Nested blocking loops:** `game_loop()` and the Connect Four/menu/puzzle
   routines still contain their own `while` loops. Under Emscripten these
   must also be converted to per-frame steppers (or run via Asyncify) or
   they will freeze the browser tab. Only the top-level loop is converted
   here.
4. Verify `--preload-file assets` finds the corrected audio paths
   (`assets/music/0.mp3`, `assets/Mouse_Click.wav`).
