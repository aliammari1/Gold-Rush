/* SPDX-License-Identifier: Zlib */
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "core.h"
#include "connect4_ai.h"

/**
 * @brief Pick the CPU's move with depth-limited alpha-beta minimax.
 *
 * Bridges the SDL game board (1 = human/red, 2 = CPU/yellow, row 5 at the
 * bottom) to the SDL-free solver in connect4_ai.c, which shares the exact
 * same board convention, and returns the landing cell.
 *
 * @param board The current 6x7 Connect Four board.
 * @return The cell the CPU should fill (row/column).
 */
GameCell computerMoveMinimax(int board[GAME_BOARD_ROWS][GAME_BOARD_COLS])
{
    GameCell cell = {0, 0};
    int col;
    int row;

    col = c4_best_move(board, C4_CPU, C4_DEFAULT_DEPTH);
    if (col < 0) {
        /* Board full / no move; fall back to the heuristic opponent. */
        return computerMove(board);
    }

    /* Find the row the token would land in (lowest empty cell). */
    for (row = GAME_BOARD_ROWS - 1; row >= 0; row--) {
        if (board[row][col] == 0) {
            cell.row = row;
            cell.column = col;
            return cell;
        }
    }
    /* Should not happen if c4_best_move returned a playable column. */
    return computerMove(board);
}

int runConnectFourGame(void)
{
    return runConnectFourGameMode(CONNECT_FOUR_HEURISTIC);
}

int runConnectFourGameMode(ConnectFourOpponent opponent)
{

    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("assets/alger.TTF", 90);
    SDL_Color couleur = {52, 201, 36};
    SDL_Color couleur_r = {187, 11, 11};
    SDL_Color couleur_n = {0, 0, 0};
    SDL_Surface *fond_n;
    SDL_Rect pos_n;
    pos_n.x = 480;
    pos_n.y = 400;
    int check = 0;
    GameCell playerMove, aiMove;
    int gameBoard[6][7];
    int done = 1, j, i, nb_coups = 0;
    SDL_Surface *screen;
    SDL_Surface *fond;
    SDL_Surface *jaune;
    SDL_Surface *rouge;
    SDL_Rect pos_ecran;
    SDL_Rect pos_rouge;
    SDL_Rect pos;
    SDL_Surface *j_g;
    SDL_Surface *pc_g;
    SDL_Surface *gameover;
    j_g = TTF_RenderText_Blended(police, "YOU WON", couleur);
    pc_g = TTF_RenderText_Blended(police, "YOU LOST", couleur_r);
    gameover = TTF_RenderText_Blended(police, "Game Over", couleur_n);
    pos.x = 500;
    pos.y = 400;
    SDL_Event event;
    fond = IMG_Load("assets/puissance.png");
    fond_n = IMG_Load("assets/fond.png");
    jaune = IMG_Load("assets/jaune.png");
    rouge = IMG_Load("assets/rouge.png");
    pos_ecran.x = 150;
    pos_ecran.y = 0;
    /* SDL already initialized in main.c */
    screen = SDL_SetVideoMode(1250, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_BlitSurface(fond, NULL, screen, &pos_ecran);
    SDL_Flip(screen);
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
            gameBoard[i][j] = 0;
    }
    while (done == 1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONUP:
                if ((check == 0) && (nb_coups < 21))
                {
                    playerMove = dropToken(screen, rouge, event, gameBoard);
                    gameBoard[playerMove.row][playerMove.column] = 1;
                    nb_coups++;
                    check = checkWinCondition(gameBoard);
                    if (nb_coups == 21)
                    {
                        SDL_BlitSurface(fond_n, NULL, screen, &pos_n);
                        SDL_Flip(screen);
                        SDL_BlitSurface(gameover, NULL, screen, &pos);
                        SDL_Flip(screen);
                    }
                    if (check == 1)
                    {
                        SDL_BlitSurface(fond_n, NULL, screen, &pos_n);
                        SDL_Flip(screen);
                        SDL_BlitSurface(j_g, NULL, screen, &pos);
                        SDL_Flip(screen);
                    }
                    if (check == 2)
                    {
                        SDL_BlitSurface(fond_n, NULL, screen, &pos_n);
                        SDL_Flip(screen);
                        SDL_BlitSurface(pc_g, NULL, screen, &pos);
                        SDL_Flip(screen);
                    }
                    if ((nb_coups < 22) && (check == 0))
                    {
                        aiMove = (opponent == CONNECT_FOUR_MINIMAX)
                                     ? computerMoveMinimax(gameBoard)
                                     : computerMove(gameBoard);
                        gameBoard[aiMove.row][aiMove.column] = 2;
                        renderYellowToken(screen, jaune, aiMove);
                        check = checkWinCondition(gameBoard);
                        if (nb_coups == 21)
                        {
                            SDL_BlitSurface(fond_n, NULL, screen, &pos_n);
                            SDL_Flip(screen);
                            SDL_BlitSurface(gameover, NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        if (check == 1)
                        {
                            SDL_BlitSurface(fond_n, NULL, screen, &pos_n);
                            SDL_Flip(screen);
                            SDL_BlitSurface(j_g, NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                        if (check == 2)
                        {
                            SDL_BlitSurface(fond_n, NULL, screen, &pos_n);
                            SDL_Flip(screen);
                            SDL_BlitSurface(pc_g, NULL, screen, &pos);
                            SDL_Flip(screen);
                        }
                    }
                }
                break;
            case SDL_QUIT:
                done = 0;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_r)
                {
                    done = 0;
                }
                break;
            }
        }
    }
    return 0;
}
