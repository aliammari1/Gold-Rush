SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -g -Wall -Wextra -Wno-unused-parameter

# SDL 2 native build. Use pkg-config when available; fall back to plain -l.
SDL2_CFLAGS := $(shell pkg-config --cflags sdl2 2>/dev/null)
SDL2_LIBS := $(shell pkg-config --libs sdl2 2>/dev/null)
ifeq ($(strip $(SDL2_LIBS)),)
SDL2_LIBS := -lSDL2
endif

CFLAGS += $(SDL2_CFLAGS)
LIBS := $(SDL2_LIBS) -lSDL2_ttf -lSDL2_image -lSDL2_mixer

TARGET := game

# Emscripten / WebAssembly build settings.
EMCC := emcc
WASM_TARGET := game.html
# -sUSE_SDL=2 pulls in SDL2; the _image/_ttf/_mixer ports add the rest.
EMFLAGS := -O2 \
	-sUSE_SDL=2 \
	-sUSE_SDL_IMAGE=2 \
	-sUSE_SDL_TTF=2 \
	-sUSE_SDL_MIXER=2 \
	-sSDL2_IMAGE_FORMATS='["png","jpg","bmp"]' \
	-sALLOW_MEMORY_GROWTH=1 \
	--preload-file assets

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

# Build the in-browser WebAssembly bundle (game.html/.js/.wasm/.data).
# Requires the Emscripten SDK (emcc) on PATH.
wasm:
	$(EMCC) $(SRCS) $(EMFLAGS) -o $(WASM_TARGET)

clean:
	rm -f $(OBJS) $(TARGET) game.html game.js game.wasm game.data

.PHONY: all run wasm clean
