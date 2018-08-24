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
    char *line = NULL, valid = 0, playing = 1;
    size_t size = 0;
    int turn = 0;

    while(!valid)
    {
        system("clear");
        printf(BANNER "  1. New Game\n  2. Load\n  [Q]uit\n> ");

        getline(&line, &size, stdin);
        valid = mainMenu(players, line);
    }
    
    while(playing && valid)
    {
        system("tput reset");
        turn = checkTurn(players);
        playing = game(players, turn);
    }

    playerDestruct(players);
    return 0;
}
