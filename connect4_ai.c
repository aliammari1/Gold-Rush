/* SPDX-License-Identifier: Zlib */
#include "connect4_ai.h"

/*
 * Depth-limited alpha-beta (minimax) Connect Four opponent.
 *
 * Pure C, no SDL: this file is compiled both into the game and into the
 * standalone Unity test (tests/test_connect4_ai.c).
 */

/* Column visit order, centre-out: central columns create more threats. */
static const int C4_COLUMN_ORDER[C4_COLS] = {3, 2, 4, 1, 5, 0, 6};

/* Large finite score used for a forced win/loss inside the search. */
#define C4_WIN_SCORE 100000

int c4_column_playable(const int board[C4_ROWS][C4_COLS], int col)
{
    if (col < 0 || col >= C4_COLS) {
        return 0;
    }
    /* The top cell of a column is empty iff the column has room. */
    return board[0][col] == C4_EMPTY;
}

int c4_drop(int board[C4_ROWS][C4_COLS], int col, int player)
{
    int row;

    if (col < 0 || col >= C4_COLS) {
        return -1;
    }
    for (row = C4_ROWS - 1; row >= 0; row--) {
        if (board[row][col] == C4_EMPTY) {
            board[row][col] = player;
            return row;
        }
    }
    return -1; /* column full */
}

int c4_board_full(const int board[C4_ROWS][C4_COLS])
{
    int col;
    for (col = 0; col < C4_COLS; col++) {
        if (board[0][col] == C4_EMPTY) {
            return 0;
        }
    }
    return 1;
}

/* Count a run of four cells starting at (r,c) stepping by (dr,dc). */
static int c4_four_in_line(const int board[C4_ROWS][C4_COLS],
                           int r, int c, int dr, int dc)
{
    int first = board[r][c];
    int k;

    if (first == C4_EMPTY) {
        return 0;
    }
    for (k = 1; k < 4; k++) {
        int rr = r + dr * k;
        int cc = c + dc * k;
        if (rr < 0 || rr >= C4_ROWS || cc < 0 || cc >= C4_COLS) {
            return 0;
        }
        if (board[rr][cc] != first) {
            return 0;
        }
    }
    return first;
}

int c4_winner(const int board[C4_ROWS][C4_COLS])
{
    int r, c;
    /* Four directions: right, down, down-right, down-left. */
    static const int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (r = 0; r < C4_ROWS; r++) {
        for (c = 0; c < C4_COLS; c++) {
            int d;
            for (d = 0; d < 4; d++) {
                int w = c4_four_in_line(board, r, c, dirs[d][0], dirs[d][1]);
                if (w != C4_EMPTY) {
                    return w;
                }
            }
        }
    }
    return 0;
}

/* Score a 4-cell window for `me` (higher is better for `me`). */
static int c4_score_window(int a, int b, int c, int d, int me)
{
    int opp = (me == C4_CPU) ? C4_HUMAN : C4_CPU;
    int mine = 0, theirs = 0, empty = 0;
    int cells[4];
    int i;

    cells[0] = a; cells[1] = b; cells[2] = c; cells[3] = d;
    for (i = 0; i < 4; i++) {
        if (cells[i] == me) {
            mine++;
        } else if (cells[i] == opp) {
            theirs++;
        } else {
            empty++;
        }
    }

    /* A window with both colours is dead and worth nothing. */
    if (mine > 0 && theirs > 0) {
        return 0;
    }
    if (mine == 4) {
        return 1000;
    }
    if (mine == 3 && empty == 1) {
        return 50;
    }
    if (mine == 2 && empty == 2) {
        return 10;
    }
    if (theirs == 3 && empty == 1) {
        return -80; /* block opponent's open three a bit harder */
    }
    if (theirs == 2 && empty == 2) {
        return -8;
    }
    return 0;
}

/* Heuristic positional evaluation from `me`'s perspective. */
static int c4_evaluate(const int board[C4_ROWS][C4_COLS], int me)
{
    int score = 0;
    int r, c;

    /* Prefer central control. */
    for (r = 0; r < C4_ROWS; r++) {
        if (board[r][C4_COLS / 2] == me) {
            score += 6;
        }
    }

    /* Horizontal windows. */
    for (r = 0; r < C4_ROWS; r++) {
        for (c = 0; c <= C4_COLS - 4; c++) {
            score += c4_score_window(board[r][c], board[r][c + 1],
                                     board[r][c + 2], board[r][c + 3], me);
        }
    }
    /* Vertical windows. */
    for (c = 0; c < C4_COLS; c++) {
        for (r = 0; r <= C4_ROWS - 4; r++) {
            score += c4_score_window(board[r][c], board[r + 1][c],
                                     board[r + 2][c], board[r + 3][c], me);
        }
    }
    /* Diagonal down-right. */
    for (r = 0; r <= C4_ROWS - 4; r++) {
        for (c = 0; c <= C4_COLS - 4; c++) {
            score += c4_score_window(board[r][c], board[r + 1][c + 1],
                                     board[r + 2][c + 2], board[r + 3][c + 3],
                                     me);
        }
    }
    /* Diagonal down-left. */
    for (r = 0; r <= C4_ROWS - 4; r++) {
        for (c = 3; c < C4_COLS; c++) {
            score += c4_score_window(board[r][c], board[r + 1][c - 1],
                                     board[r + 2][c - 2], board[r + 3][c - 3],
                                     me);
        }
    }
    return score;
}

/* Remove the top token from a column (undo of c4_drop into row `row`). */
static void c4_undo(int board[C4_ROWS][C4_COLS], int row, int col)
{
    board[row][col] = C4_EMPTY;
}

/*
 * Alpha-beta negamax. `me` is the AI; the returned score is from `me`'s
 * perspective. `turn` is whose move it currently is.
 */
static int c4_alphabeta(int board[C4_ROWS][C4_COLS], int depth,
                        int alpha, int beta, int turn, int me)
{
    int winner = c4_winner(board);
    int opp = (me == C4_CPU) ? C4_HUMAN : C4_CPU;
    int i;
    int best;

    if (winner == me) {
        /* Prefer faster wins (and slower losses) by folding in depth. */
        return C4_WIN_SCORE + depth;
    }
    if (winner == opp) {
        return -C4_WIN_SCORE - depth;
    }
    if (depth == 0 || c4_board_full(board)) {
        return c4_evaluate(board, me);
    }

    if (turn == me) {
        best = -2 * C4_WIN_SCORE;
        for (i = 0; i < C4_COLS; i++) {
            int col = C4_COLUMN_ORDER[i];
            int row;
            int val;
            if (!c4_column_playable(board, col)) {
                continue;
            }
            row = c4_drop(board, col, turn);
            val = c4_alphabeta(board, depth - 1, alpha, beta, opp, me);
            c4_undo(board, row, col);
            if (val > best) {
                best = val;
            }
            if (best > alpha) {
                alpha = best;
            }
            if (alpha >= beta) {
                break; /* beta cutoff */
            }
        }
        return best;
    } else {
        best = 2 * C4_WIN_SCORE;
        for (i = 0; i < C4_COLS; i++) {
            int col = C4_COLUMN_ORDER[i];
            int row;
            int val;
            if (!c4_column_playable(board, col)) {
                continue;
            }
            row = c4_drop(board, col, turn);
            val = c4_alphabeta(board, depth - 1, alpha, beta, me, me);
            c4_undo(board, row, col);
            if (val < best) {
                best = val;
            }
            if (best < beta) {
                beta = best;
            }
            if (alpha >= beta) {
                break; /* alpha cutoff */
            }
        }
        return best;
    }
}

int c4_best_move(const int board[C4_ROWS][C4_COLS], int player, int depth)
{
    int work[C4_ROWS][C4_COLS];
    int r, c;
    int best_col = -1;
    int best_val = -2 * C4_WIN_SCORE - 1;
    int opp = (player == C4_CPU) ? C4_HUMAN : C4_CPU;
    int i;

    /* Copy so the caller's board is never mutated. */
    for (r = 0; r < C4_ROWS; r++) {
        for (c = 0; c < C4_COLS; c++) {
            work[r][c] = board[r][c];
        }
    }

    if (depth < 1) {
        depth = 1;
    }

    for (i = 0; i < C4_COLS; i++) {
        int col = C4_COLUMN_ORDER[i];
        int row;
        int val;
        if (!c4_column_playable(work, col)) {
            continue;
        }
        row = c4_drop(work, col, player);
        val = c4_alphabeta(work, depth - 1, -2 * C4_WIN_SCORE,
                           2 * C4_WIN_SCORE, opp, player);
        c4_undo(work, row, col);
        if (best_col == -1 || val > best_val) {
            best_val = val;
            best_col = col;
        }
    }
    return best_col;
}
