# SDL-free unit tests for the Connect Four minimax opponent.
#
#   make            # build and run the tests
#   make run        # same
#   make clean
#
# These tests link only pure C (connect4_ai.c + a minimal Unity shim) and
# therefore build on any machine with a C compiler -- no SDL required.

CC      ?= gcc
CFLAGS  ?= -std=c99 -Wall -Wextra -O1 -g
# Address/UB sanitizers catch memory bugs in the board logic in CI.
SANFLAGS ?= -fsanitize=address,undefined -fno-omit-frame-pointer

ROOT    := ..
UNITY   := vendor/unity

SRCS := test_connect4_ai.c $(ROOT)/connect4_ai.c $(UNITY)/unity.c
INCS := -I$(ROOT) -I$(UNITY)

BIN := test_connect4_ai

.PHONY: all run sanitize clean

all: run

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(INCS) $(SRCS) -o $(BIN)

run: $(BIN)
	./$(BIN)

# Run under ASan/UBSan (used by CI).
sanitize: $(SRCS)
	$(CC) $(CFLAGS) $(SANFLAGS) $(INCS) $(SRCS) -o $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
