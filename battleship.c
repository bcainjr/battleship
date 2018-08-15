/*
* TDQC5
* Bruce Cain
* 
* Wanna play battleship?
*/

#include <stdio.h>
#include <stdlib.h>
#include "BattleshipGame.h"

int main(void)
{
    Player *players[2];
    char *line = NULL, contMenu = 1;
    size_t size = 0;

    while(contMenu)
    {
        system("clear");
        printf("  1. New Game\n  2. Load\n  [Q]uit\n>");

        getline(&line, &size, stdin);
        contMenu = mainMenu(players, line);
    }

    return 0;
}

