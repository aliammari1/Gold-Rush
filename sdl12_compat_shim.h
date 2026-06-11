/* SPDX-License-Identifier: Zlib */
#ifndef SDL12_COMPAT_SHIM_H
#define SDL12_COMPAT_SHIM_H

/*
 * SDL 1.2 -> SDL 2 compatibility shim for Gold Rush.
 *
 * The game was written against the SDL 1.2 video API (SDL_SetVideoMode,
 * SDL_Flip, SDL_WM_*). Rather than rewrite every call site, this header
 * provides thin SDL 2 reimplementations behind the original names so the
 * existing code compiles against SDL 2 with minimal churn.
 *
 *   SDL_SetVideoMode(w,h,bpp,flags) -> creates/resizes a single window and
 *                                      returns its window surface.
 *   SDL_Flip(surface)               -> SDL_UpdateWindowSurface(window).
 *   SDL_WM_SetCaption(title, icon)  -> SDL_SetWindowTitle(window, title).
 *   SDL_WM_ToggleFullScreen(s)      -> toggles desktop fullscreen.
 *
 * Surface blitting, SDL_image/ttf/mixer, and the event/keysym API are
 * source-compatible between SDL 1.2 and SDL 2, so they are left as-is.
 *
 * NOTE: This branch (feat/sdl2-wasm) NEEDS COMPILE VERIFICATION against
 * real SDL2 / emcc headers before merge.
 *
 * Include this AFTER <SDL2/SDL.h> (core.h handles the ordering).
 */

#include <SDL2/SDL.h>

/* SDL 1.2 surface flags that no longer exist in SDL 2; define as no-ops so
 * old flag expressions (e.g. SDL_HWSURFACE | SDL_DOUBLEBUF) still compile. */
#ifndef SDL_HWSURFACE
#define SDL_HWSURFACE 0x00000000u
#endif
#ifndef SDL_SWSURFACE
#define SDL_SWSURFACE 0x00000000u
#endif
#ifndef SDL_DOUBLEBUF
#define SDL_DOUBLEBUF 0x00000000u
#endif
#ifndef SDL_FULLSCREEN
#define SDL_FULLSCREEN 0x80000000u
#endif
#ifndef SDL_ANYFORMAT
#define SDL_ANYFORMAT 0x00000000u
#endif
#ifndef SDL_RESIZABLE
#define SDL_RESIZABLE 0x00000000u
#endif

/* The single application window backing every "screen" surface. */
extern SDL_Window *g_sdl12_window;

/*
 * Create (or resize) the application window and return its surface.
 * Mirrors the SDL 1.2 SDL_SetVideoMode signature.
 */
SDL_Surface *SDL12_SetVideoMode(int width, int height, int bpp, Uint32 flags);

/* Present the window surface (SDL 1.2 SDL_Flip). */
int SDL12_Flip(SDL_Surface *screen);

/* Window title (SDL 1.2 SDL_WM_SetCaption). */
void SDL12_WM_SetCaption(const char *title, const char *icon);

/* Toggle desktop fullscreen (SDL 1.2 SDL_WM_ToggleFullScreen). */
int SDL12_WM_ToggleFullScreen(SDL_Surface *screen);

/* Redirect the legacy names to the shim implementations. */
#define SDL_SetVideoMode(w, h, bpp, flags) SDL12_SetVideoMode((w), (h), (bpp), (flags))
#define SDL_Flip(screen) SDL12_Flip((screen))
#define SDL_WM_SetCaption(title, icon) SDL12_WM_SetCaption((title), (icon))
#define SDL_WM_ToggleFullScreen(screen) SDL12_WM_ToggleFullScreen((screen))

/*
 * SDL_CreateRGBSurface dropped its flags argument's old meaning; the first
 * argument must be 0 in SDL 2. world.c passes SDL_HWSURFACE | SDL_DOUBLEBUF
 * (now 0 via the no-op defines above), so no change is needed there.
 */

#endif /* SDL12_COMPAT_SHIM_H */
