#include <stdlib.h>
#include <stdio.h>

/* SDL 2 + the legacy-API shim are pulled in via minigame.h -> types.h. */
#include "minigame.h"
GameCell dropToken(SDL_Surface *screen, SDL_Surface *rouge, SDL_Event event, int t[6][7])
{
    int i = 5;
    GameCell cell = {0, 0};  /* Initialize to avoid undefined behavior */
    SDL_Rect pos = {0, 0, 0, 0};
    
    if ((event.motion.x > 175) && (event.motion.x < 276))
    {
        pos.x = 175 - 10;
        cell.column = 0;
    }
    else if ((event.motion.x > 306) && (event.motion.x < 399))
    {
        pos.x = 306 - 8;
        cell.column = 1;
    }
    else if ((event.motion.x > 439) && (event.motion.x < 533))
    {
        pos.x = 439 - 8;
        cell.column = 2;
    }
    else if ((event.motion.x > 571) && (event.motion.x < 667))
    {
        cell.column = 3;
        pos.x = 571 - 8;
    }
    else if ((event.motion.x > 706) && (event.motion.x < 800))
    {
        cell.column = 4;
        pos.x = 706 - 8;
    }
    else if ((event.motion.x > 838) && (event.motion.x < 934))
    {
        cell.column = 5;
        pos.x = 838 - 8;
    }
    else if ((event.motion.x > 972) && (event.motion.x < 1068))
    {
        cell.column = 6;
        pos.x = 972 - 8;
    }
    
    while ((t[i][cell.column] != 0) && (i > 0))
        i--;
        
    cell.row = i;
    switch (i)
    {
        case 0: pos.y = 22 - 5; break;
        case 1: pos.y = 154 - 5; break;
        case 2: pos.y = 287 - 5; break;
        case 3: pos.y = 422 - 5; break;
        case 4: pos.y = 554 - 5; break;
        case 5: pos.y = 686 - 5; break;
        default: pos.y = 686 - 5; break;
    }
    
    SDL_BlitSurface(rouge, NULL, screen, &pos);
    SDL_Flip(screen);
    return cell;
}
GameCell computerMove(int t[6][7])
{
    GameCell cell = {0, 0};  /* Initialize to avoid undefined behavior */
    int i, j = 0, test = 0;
    (void)test;  /* Suppress unused warning - test is used for control flow */
    while ((j < 7) && (test == 0))
    {
        i = 5;
        while ((i > 2) && (test == 0))
        {
            if (((t[i][j] == 2) && (t[i - 1][j] == 2) && (t[i - 2][j] == 2)) && ((t[i - 3][j] == 0)))
            {
                test = 1;
                cell.row = i - 3; // jaune gagne v
                cell.column = j;
            }
            i--;
        }
        j++;
    }
    i = 5;
    while ((i > 0) && (test == 0))
    {
        j = 0;
        while ((j < 4) && (test == 0))
        {
            if (((t[i][j] == 2) && (t[i][j + 1] == 2) && (t[i][j + 2] == 2)) && ((t[i][j - 1] == 0) || (t[i][j + 3] == 0)) && ((t[i - 1][j + 3] != 0) || (t[i - 1][j - 1] != 0)))
            {
                if ((t[i][j - 1] == 0) && (j != 0) && (t[i - 1][j - 1] != 0))
                {
                    cell.row = i; // jaune gagne h
                    cell.column = j - 1;
                    test = 1;
                }
                if ((t[i][j + 3] == 0) && (t[i - 1][j + 3] != 0))
                {
                    cell.row = i;
                    cell.column = j + 3;
                    test = 1;
                }
            }
            j++;
        }
        i--;
    }
    j = 0;
    while ((j < 7) && (test == 0))
    {
        i = 5;
        while ((i > 2) && (test == 0))
        {
            if (((t[i][j] == 1) && (t[i - 1][j] == 1) && (t[i - 2][j] == 1)) && ((t[i - 3][j] == 0)))
            {
                test = 1;
                cell.row = i - 3;
                cell.column = j;
            } // bloc rouge 3
            i--;
        }
        j++;
    }
    i = 5;
    while ((i > 0) && (test == 0))
    {
        j = 0;
        while ((j < 5) && (test == 0))
        {
            if (((t[i][j] == 1) && (t[i][j + 1] == 1) && (t[i][j + 2] == 1)) && ((t[i][j - 1] == 0) || (t[i][j + 3] == 0)))
            {
                if ((t[i][j + 3] == 0) && ((t[i - 1][j + 3] != 0) || (i == 5)))
                {
                    test = 1;
                    cell.row = i;
                    cell.column = j + 3;
                }
                if ((t[i][j - 1] == 0) && (j != 0) && ((t[i - 1][j - 1] != 0) || (i == 5))) // bloc rouge 3 h
                {
                    test = 1;
                    cell.row = i;
                    cell.column = j - 1;
                }
            }
            j++;
        }
        i--;
    }
    j = 0;
    while ((j < 7) && (test == 0))
    {
        i = 5;
        while ((i > 1) && (test == 0))
        {
            if (((t[i][j] == 2) && (t[i - 1][j] == 2)) && ((t[i - 2][j] == 0)))
            {
                test = 1;
                cell.row = i - 2;
                cell.column = j;
            }
            i--;
        }
        j++;
    }
    i = 5;
    while ((i > 0) && (test == 0))
    {
        j = 0;
        while ((j < 5) && (test == 0))
        {
            if (((t[i][j] == 2) && (t[i][j + 1] == 2)) && ((t[i][j - 1] == 0) || (t[i][j + 2] == 0)))
            {
                if ((t[i][j - 1] == 0) && (j != 0) && ((t[i - 1][j - 1] != 0) || (i == 5)))
                {
                    test = 1;
                    cell.row = i;
                    cell.column = j - 1;
                }
                if ((t[i][j + 2] == 0) && ((t[i - 1][j + 2] != 0) || (i == 5)))
                {
                    test = 1;
                    cell.row = i;
                    cell.column = j + 2;
                }
            }
            j++;
        }
        i--;
    }
    j = 0;
    while ((j < 7) && (test == 0))
    {
        i = 5;
        while ((i > 0) && (test == 0))
        {
            if (((t[i][j] == 2)) && ((t[i - 1][j] == 0)))
            {
                test = 1;
                cell.row = i - 1;
                cell.column = j;
            }
            i--;
        }
        j++;
    }
    i = 5;
    while ((i > 0) && (test == 0))
    {
        j = 0;
        while ((j < 6) && (test == 0))
        {
            if ((t[i][j] == 2) && (((t[i][j - 1] == 0) || (t[i][j + 1] == 0))))
            {

                if ((t[i][j - 1] == 0) && (j != 0) && ((t[i - 1][j - 1] != 0) || (i == 5)))
                {
                    test = 1;
                    cell.row = i;
                    cell.column = j - 1;
                }
                if ((t[i][j + 1] == 0) && ((t[i - 1][j + 1] != 0) || (i == 5)))
                {
                    test = 1;
                    cell.row = i;
                    cell.column = j + 1;
                }
            }
            j++;
        }
        i--;
    }
    j = rand() % 7;
    while ((test == 0))
    {
        i = 5;
        while ((i > 0) && (test == 0))
        {
            if (t[i][j] == 0)
            {
                test = 1;
                cell.column = j;
                cell.row = i;
            }
            i--;
        }
        j++;
    }
    return cell;
}
void renderYellowToken(SDL_Surface *screen, SDL_Surface *jaune, GameCell cell)
{
    SDL_Rect pos;
    if (cell.column == 0)
    {
        pos.x = 175 - 10;
    }
    if (cell.column == 1)
    {
        pos.x = 306 - 8;
    }
    if (cell.column == 2)
    {
        pos.x = 439 - 8;
    }
    if (cell.column == 3)
    {
        pos.x = 571 - 8;
    }
    if (cell.column == 4)
    {
        pos.x = 706 - 8;
    }
    if (cell.column == 5)
    {
        pos.x = 838 - 8;
    }
    if (cell.column == 6)
    {
        pos.x = 972 - 8;
    }
    if (cell.row == 0)
    {
        pos.y = 22 - 5;
    }
    if (cell.row == 1)
    {
        pos.y = 154 - 5;
    }
    if (cell.row == 2)
    {
        pos.y = 287 - 5;
    }
    if (cell.row == 3)
    {
        pos.y = 422 - 5;
    }
    if (cell.row == 4)
    {
        pos.y = 554 - 5;
    }
    if (cell.row == 5)
    {
        pos.y = 686 - 5;
    }
    SDL_BlitSurface(jaune, NULL, screen, &pos);
    SDL_Flip(screen);
}
int checkWinCondition(int t[GAME_BOARD_ROWS][GAME_BOARD_COLS])
{
    int j_g = 0, pc_g = 0, test = 0, j = 0, i;
    while ((j_g == 0) && (pc_g == 0) && (j < 7))
    {
        i = 5;
        while ((i > 2) && (j_g == 0) && (pc_g == 0))
        {
            if ((t[i][j] == 1) && (t[i - 1][j] == 1) && (t[i - 2][j] == 1) && (t[i - 3][j] == 1))
                j_g = 1;
            if ((t[i][j] == 2) && (t[i - 1][j] == 2) && (t[i - 2][j] == 2) && (t[i - 3][j] == 2))
                pc_g = 1;
            i--;
        }
        j++;
    }
    i = 5;
    while ((j_g == 0) && (pc_g == 0) && (i > 0))
    {
        j = 0;
        while ((j < 4) && (j_g == 0) && (pc_g == 0))
        {
            if ((t[i][j] == 1) && (t[i][j + 1] == 1) && (t[i][j + 2] == 1) && (t[i][j + 3] == 1))
                j_g = 1;
            if ((t[i][j] == 2) && (t[i][j + 1] == 2) && (t[i][j + 2] == 2) && (t[i][j + 3] == 2))
                pc_g = 1;
            j++;
        }
        i--;
    }
    j = 0;
    while ((j_g == 0) && (pc_g == 0) && (j < 4))
    {
        i = 5;
        while ((i > 2) && (j_g == 0) && (pc_g == 0))
        {
            if ((t[i][j] == 1) && (t[i - 1][j + 1] == 1) && (t[i - 2][j + 2] == 1) && (t[i - 3][j + 3] == 1))
                j_g = 1;
            if ((t[i][j] == 2) && (t[i - 1][j + 1] == 2) && (t[i - 2][j + 2] == 2) && (t[i - 3][j + 3] == 2))
                pc_g = 1;
            i--;
        }
        j++;
    }
    j = 3;
    while ((j_g == 0) && (pc_g == 0) && (j < 7))
    {
        i = 5;
        while ((i > 2) && (j_g == 0) && (pc_g == 0))
        {
            if ((t[i][j] == 1) && (t[i - 1][j - 1] == 1) && (t[i - 2][j - 2] == 1) && (t[i - 3][j - 3] == 1))
                j_g = 1;
            if ((t[i][j] == 2) && (t[i - 1][j - 1] == 2) && (t[i - 2][j - 2] == 2) && (t[i - 3][j - 3] == 2))
                pc_g = 1;
            i--;
        }
        j++;
    }
    if (j_g == 1)
        test = 1;
    if (pc_g == 1)
        test = 2;
    return test;
}
