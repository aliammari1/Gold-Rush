# Connect Four AI

The yellow (CPU) tokens in the Connect Four minigame can be driven by a
depth-limited **alpha-beta minimax** opponent implemented in
`connect4_ai.c`. The module is pure C — no SDL — so it is fully
unit-tested.

## Board model

- A `6 × 7` `int` board.
- `0` = empty, `1` (`C4_HUMAN`) = red/player, `2` (`C4_CPU`) = yellow/CPU.
- Row 0 is the top; tokens fall to the lowest empty row in a column.

## Algorithm

1. **Search** — negamax with alpha-beta pruning to a configurable depth
   (`C4_DEFAULT_DEPTH`, 6 plies by default).
2. **Move ordering** — columns are explored centre-out (`3, 2, 4, 1, 5,
   0, 6`) because central play creates more winning lines, which improves
   pruning.
3. **Terminal scoring** — a win is `±100000`, adjusted by remaining depth
   so the AI prefers the *fastest* win and the *slowest* loss.
4. **Heuristic evaluation** at the depth limit scores every 4-cell window
   (horizontal, vertical, both diagonals): open threes and twos are
   rewarded, opponent threes are penalized harder to force blocks, and
   central control gets a bonus.

## Public API

```c
int c4_winner(const int board[C4_ROWS][C4_COLS]);          // 0, 1, or 2
int c4_drop(int board[C4_ROWS][C4_COLS], int col, int p);  // landing row or -1
int c4_best_move(const int board[C4_ROWS][C4_COLS],
                 int player, int depth);                   // best column
```

`c4_best_move` never mutates the caller's board.

## Tests

`tests/test_connect4_ai.c` (Unity) covers win detection in every
direction, move legality, immediate win/block tactics, and the headline
guarantee: the minimax opponent **never loses** to weaker play from either
side and across randomized openings. Run with `make -C tests` or, under
sanitizers, `make -C tests sanitize`.
