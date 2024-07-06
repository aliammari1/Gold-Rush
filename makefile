SRCS := $(wildcard *.c)

OBJS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -g -Wall

LIBS := -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer

TARGET := game

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
