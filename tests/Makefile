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

# gcov/lcov instrumentation for the Codecov coverage gate.
COVFLAGS ?= --coverage -O0 -g
COVBIN   := test_connect4_ai_cov

.PHONY: all run sanitize coverage clean

all: run

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(INCS) $(SRCS) -o $(BIN)

run: $(BIN)
	./$(BIN)

# Run under ASan/UBSan (used by CI).
sanitize: $(SRCS)
	$(CC) $(CFLAGS) $(SANFLAGS) $(INCS) $(SRCS) -o $(BIN)
	./$(BIN)

# Build + run with gcov instrumentation, then emit coverage.info (lcov format)
# for upload to Codecov. The report is restricted to connect4_ai.c -- the
# SDL-free decision logic that the suite actually exercises.
coverage: $(SRCS)
	$(CC) -std=c99 $(COVFLAGS) $(INCS) $(SRCS) -o $(COVBIN)
	./$(COVBIN)
	gcov -b -o . connect4_ai.gcno || true
	lcov --capture --directory . --output-file coverage.info \
	     --rc lcov_branch_coverage=1 2>/dev/null
	lcov --extract coverage.info '*connect4_ai.c' \
	     --output-file coverage.info --rc lcov_branch_coverage=1 2>/dev/null
	lcov --list coverage.info --rc lcov_branch_coverage=1 2>/dev/null || true

clean:
	rm -f $(BIN) $(COVBIN) *.gcno *.gcda *.gcov coverage.info
