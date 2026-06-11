/* SPDX-License-Identifier: Zlib */
/*
 * SDL 1.2 -> SDL 2 compatibility shim implementation.
 *
 * NEEDS COMPILE VERIFICATION against real SDL2 headers before merge.
 */
#include "sdl12_compat_shim.h"

SDL_Window *g_sdl12_window = NULL;

SDL_Surface *SDL12_SetVideoMode(int width, int height, int bpp, Uint32 flags)
{
    Uint32 win_flags = SDL_WINDOW_SHOWN;
    (void)bpp; /* SDL 2 picks the surface format. */

    if (flags & SDL_FULLSCREEN) {
        win_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (g_sdl12_window == NULL) {
        g_sdl12_window = SDL_CreateWindow(
            "Gold Rush",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, win_flags);
        if (g_sdl12_window == NULL) {
            return NULL;
        }
    } else {
        /* Reuse the window across "resolution changes" (menu/minigame
         * each call SDL_SetVideoMode): just resize it. */
        SDL_SetWindowSize(g_sdl12_window, width, height);
        if (flags & SDL_FULLSCREEN) {
            SDL_SetWindowFullscreen(g_sdl12_window,
                                    SDL_WINDOW_FULLSCREEN_DESKTOP);
        } else {
            SDL_SetWindowFullscreen(g_sdl12_window, 0);
        }
    }

    /* The window surface is owned by SDL; it is freed with the window. */
    return SDL_GetWindowSurface(g_sdl12_window);
}

int SDL12_Flip(SDL_Surface *screen)
{
    (void)screen; /* The window owns its surface. */
    if (g_sdl12_window == NULL) {
        return -1;
    }
    return SDL_UpdateWindowSurface(g_sdl12_window);
}

void SDL12_WM_SetCaption(const char *title, const char *icon)
{
    (void)icon;
    if (g_sdl12_window != NULL && title != NULL) {
        SDL_SetWindowTitle(g_sdl12_window, title);
    }
}

int SDL12_WM_ToggleFullScreen(SDL_Surface *screen)
{
    Uint32 flags;
    int is_fullscreen;
    (void)screen;

    if (g_sdl12_window == NULL) {
        return 0;
    }
    flags = SDL_GetWindowFlags(g_sdl12_window);
    is_fullscreen = (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
    return SDL_SetWindowFullscreen(
               g_sdl12_window,
               is_fullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP) == 0;
}
