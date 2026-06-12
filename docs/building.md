# Building from source

Gold Rush builds with `make` and links the SDL 1.2 family of libraries
(`-lSDL -lSDL_ttf -lSDL_image -lSDL_mixer`). Assets are loaded by relative
path, so run the game from the repository root.

## Linux

=== "Ubuntu / Debian"

    ```bash
    sudo apt-get update
    sudo apt-get install -y build-essential \
      libsdl1.2-dev libsdl-image1.2-dev \
      libsdl-mixer1.2-dev libsdl-ttf2.0-dev
    make
    ./game
    ```

=== "Fedora / RHEL"

    ```bash
    sudo dnf install gcc make \
      SDL-devel SDL_image-devel SDL_ttf-devel SDL_mixer-devel
    make
    ./game
    ```

=== "Arch"

    ```bash
    sudo pacman -S base-devel sdl sdl_image sdl_ttf sdl_mixer
    make
    ./game
    ```

## macOS

SDL 1.2 is end-of-life; use the `sdl12-compat` shim (a SDL 1.2 API on top
of SDL 2):

```bash
brew install sdl12-compat sdl_image sdl_mixer sdl_ttf
make
./game
```

## Windows

Native SDL 1.2 on Windows is fiddly. Prefer the upcoming WebAssembly build
(see [Play in browser](play-in-browser.md)) or build under WSL using the
Linux instructions above.

## Tests

The Connect Four AI is pure C and builds without SDL:

```bash
make -C tests          # build and run the unit tests
make -C tests sanitize # run under AddressSanitizer + UBSan
```
