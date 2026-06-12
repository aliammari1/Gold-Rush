/* SPDX-License-Identifier: Zlib */
/*
 * Unity tests for the SDL-free Connect Four minimax opponent.
 *
 * These exercise pure board logic (connect4_ai.c) and do not link SDL, so
 * they run on any machine with a C compiler. The headline guarantee is
 * "the depth-limited alpha-beta opponent never loses" against weaker play.
 */
#include <stdlib.h>
#include "unity.h"
#include "connect4_ai.h"

static void clear_board(int b[C4_ROWS][C4_COLS])
{
    int r, c;
    for (r = 0; r < C4_ROWS; r++) {
        for (c = 0; c < C4_COLS; c++) {
            b[r][c] = C4_EMPTY;
        }
    }
}

void setUp(void) {}
void tearDown(void) {}

/* --- Win detection --------------------------------------------------- */

void test_detects_horizontal_win(void)
{
    int b[C4_ROWS][C4_COLS];
    clear_board(b);
    b[5][0] = b[5][1] = b[5][2] = b[5][3] = C4_HUMAN;
    TEST_ASSERT_EQUAL_INT(C4_HUMAN, c4_winner(b));
}

void test_detects_vertical_win(void)
{
    int b[C4_ROWS][C4_COLS];
    clear_board(b);
    b[5][2] = b[4][2] = b[3][2] = b[2][2] = C4_CPU;
    TEST_ASSERT_EQUAL_INT(C4_CPU, c4_winner(b));
}

void test_detects_diagonal_win(void)
{
    int b[C4_ROWS][C4_COLS];
    clear_board(b);
    /* Down-right diagonal. */
    b[2][0] = b[3][1] = b[4][2] = b[5][3] = C4_HUMAN;
    TEST_ASSERT_EQUAL_INT(C4_HUMAN, c4_winner(b));
}

void test_empty_board_has_no_winner(void)
{
    int b[C4_ROWS][C4_COLS];
    clear_board(b);
    TEST_ASSERT_EQUAL_INT(0, c4_winner(b));
}

/* --- Move legality --------------------------------------------------- */

void test_drop_stacks_and_fills_column(void)
{
    int b[C4_ROWS][C4_COLS];
    int row;
    clear_board(b);
    row = c4_drop(b, 3, C4_HUMAN);
    TEST_ASSERT_EQUAL_INT(C4_ROWS - 1, row); /* bottom row */
    row = c4_drop(b, 3, C4_CPU);
    TEST_ASSERT_EQUAL_INT(C4_ROWS - 2, row); /* stacks on top */
}

void test_full_column_is_not_playable(void)
{
    int b[C4_ROWS][C4_COLS];
    int i;
    clear_board(b);
    for (i = 0; i < C4_ROWS; i++) {
        c4_drop(b, 0, C4_HUMAN);
    }
    TEST_ASSERT_FALSE(c4_column_playable(b, 0));
    TEST_ASSERT_EQUAL_INT(-1, c4_drop(b, 0, C4_CPU));
}

/* --- Tactical behaviour --------------------------------------------- */

void test_ai_takes_immediate_win(void)
{
    int b[C4_ROWS][C4_COLS];
    int col;
    clear_board(b);
    /* CPU has three in a row on the bottom; col 3 completes it. */
    b[5][0] = b[5][1] = b[5][2] = C4_CPU;
    col = c4_best_move(b, C4_CPU, C4_DEFAULT_DEPTH);
    TEST_ASSERT_EQUAL_INT(3, col);
}

void test_ai_blocks_immediate_loss(void)
{
    int b[C4_ROWS][C4_COLS];
    int col;
    clear_board(b);
    /* Human threatens to complete a row at col 3; CPU must block there. */
    b[5][0] = b[5][1] = b[5][2] = C4_HUMAN;
    col = c4_best_move(b, C4_CPU, C4_DEFAULT_DEPTH);
    TEST_ASSERT_EQUAL_INT(3, col);
}

/* --- "Never loses" self-play ---------------------------------------- */

/*
 * A deterministic weak opponent: takes an immediate win, else blocks an
 * immediate loss, else plays a shallow (depth-1) greedy move. This stands
 * in for a casual human / the original heuristic CPU.
 */
static int weak_move(const int board[C4_ROWS][C4_COLS], int me)
{
    return c4_best_move(board, me, 1);
}

/*
 * Play one full game. `ai_starts` decides who moves first. Returns the
 * winner (C4_CPU = strong minimax AI, C4_HUMAN = weak opponent, 0 = draw).
 */
static int play_game(int ai_starts, int ai_depth)
{
    int b[C4_ROWS][C4_COLS];
    int turn;
    clear_board(b);
    turn = ai_starts ? C4_CPU : C4_HUMAN;

    while (!c4_board_full(b)) {
        int col;
        if (turn == C4_CPU) {
            col = c4_best_move(b, C4_CPU, ai_depth);
        } else {
            col = weak_move(b, C4_HUMAN);
        }
        if (col < 0) {
            break;
        }
        c4_drop(b, col, turn);
        if (c4_winner(b) == turn) {
            return turn;
        }
        turn = (turn == C4_CPU) ? C4_HUMAN : C4_CPU;
    }
    return 0; /* draw */
}

void test_minimax_never_loses_going_first(void)
{
    int winner = play_game(1, C4_DEFAULT_DEPTH);
    /* The strong AI must win or draw, never lose. */
    TEST_ASSERT_NOT_EQUAL_INT(C4_HUMAN, winner);
}

void test_minimax_never_loses_going_second(void)
{
    int winner = play_game(0, C4_DEFAULT_DEPTH);
    TEST_ASSERT_NOT_EQUAL_INT(C4_HUMAN, winner);
}

/*
 * Stress: many semi-random openings, then the strong AI must not lose.
 * The opponent occasionally plays a random legal move to vary the line.
 */
void test_minimax_never_loses_under_random_openings(void)
{
    int game;
    srand(20260612u);
    for (game = 0; game < 40; game++) {
        int b[C4_ROWS][C4_COLS];
        int turn = (game % 2 == 0) ? C4_CPU : C4_HUMAN;
        int plies = 0;
        clear_board(b);
        while (!c4_board_full(b)) {
            int col;
            if (turn == C4_CPU) {
                col = c4_best_move(b, C4_CPU, 5);
            } else if (plies < 2) {
                /* random legal opening move for the opponent */
                do {
                    col = rand() % C4_COLS;
                } while (!c4_column_playable(b, col));
            } else {
                col = weak_move(b, C4_HUMAN);
            }
            if (col < 0) {
                break;
            }
            c4_drop(b, col, turn);
            if (c4_winner(b) == turn) {
                TEST_ASSERT_NOT_EQUAL_INT(C4_HUMAN, turn);
                break;
            }
            turn = (turn == C4_CPU) ? C4_HUMAN : C4_CPU;
            plies++;
        }
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_detects_horizontal_win);
    RUN_TEST(test_detects_vertical_win);
    RUN_TEST(test_detects_diagonal_win);
    RUN_TEST(test_empty_board_has_no_winner);
    RUN_TEST(test_drop_stacks_and_fills_column);
    RUN_TEST(test_full_column_is_not_playable);
    RUN_TEST(test_ai_takes_immediate_win);
    RUN_TEST(test_ai_blocks_immediate_loss);
    RUN_TEST(test_minimax_never_loses_going_first);
    RUN_TEST(test_minimax_never_loses_going_second);
    RUN_TEST(test_minimax_never_loses_under_random_openings);
    return UNITY_END();
}
