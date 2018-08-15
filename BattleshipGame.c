/*
* TDQC5
* Bruce Cain
*
* BattleshipGame source
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BattleshipGame.h"

/* Error codes */
#define BADPLAYERINIT 10

void printUpperRow(void)
{
    char upperRow[11] = 
    {
        'A', 'B', 'C', 'D', 'E', 
        'F', 'G', 'H', 'I', 'J'
    };

    for(int i = 0; i < 11; i++)
    {
        if(!i)
        {
            printf("   ");
            continue;
        }

        printf("%c ", upperRow[i-1]);
    }

    printf("\n");
}

void printBoard(char **board)
{
    printUpperRow();

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(!j)
            {
                printf("%d  ", i);
                continue;
            }

            if(!board[i][j-1])
            {
                printf("_ ");
            }
            else
            {
                printf("%c ", board[i][j-1]);
            }
        }

        printf("\n");
    }
}

int placeShip(char **shipPlacement, char *start, char *end, char ship)
{
    /* Check bounds and ship length */

    for(int j = toupper(start[0]) - 'A'; j < toupper(end[0]) - 'A' + 1; j++)
    {
        for(int i = start[1] - '0'; i < end[1]- '0' + 1; i++)
        {
            shipPlacement[i][j] = ship;
        }
    }

    return 0;
}

int shipPlacement(char **shipPlacement, int player)
{
    char *start = NULL, *end = NULL, *done = 0;
    size_t size = 0;
    char ships[7][17] =
    {
        "Patrol Boat", "Submarine", "Cruiser",
        "Destroyer", "Battleship", "Aircraft Carrier"
    };

    for(int i = 0; i < 6; i++)
    {
        //system("clear");
        printf("Player %d place %s\n", player + 1, ships[i]);
        printBoard(shipPlacement);

        printf("Start> ");
        getline(&start, &size, stdin);
        start[strlen(start)-1] = '\0';

        printf("End  > ");
        getline(&end, &size, stdin);
        end[strlen(end)-1] = '\0';

        placeShip(shipPlacement, start, end, ships[i][0]);
    }

    free(start);
    free(end);
    return 0;
}

int mainMenu(Player **players, char *input)
{
    switch(input[0])
    {
        case '1':
        {
            if(playerInit(players))
            {
                printf("Player initialize fail.\n");
                return BADPLAYERINIT;
            }
            break;
        }
        case '2':
        {
            printf("2\n");
            break;
        }
        case 'q':
        case 'Q':
        {
            printf("Exiting...\n");
            return 0;
        }
        default:
        {
            return 1;
        }
    }

    return 1;
}

void boardInit(Player *player)
{
    player->hitMiss = calloc(10, sizeof(char *));
    player->shipPlacement = calloc(10, sizeof(char *));

    for(int i = 0; i < 10; i++)
    {
        player->hitMiss[i] = calloc(10, sizeof(char));
        player->shipPlacement[i] = calloc(10, sizeof(char));
    }
}

int playerInit(Player **players)
{
    for(int i = 0; i < 2; i++)
    {
        players[i] = calloc(sizeof(Player), 1);

        if(players[i] == NULL)
        {
            return 1;
        }
        
        boardInit(players[i]);
        shipPlacement(players[i]->shipPlacement, i);
    }

    return 0;
}
