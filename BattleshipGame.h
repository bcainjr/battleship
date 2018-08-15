/*
 * Bruce Cain
 *
 * Battleship header file.
 */

#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

typedef struct Player
{
    int length;
    int width;
    char **hitMiss;
    char **shipPlacement;
} Player;

int mainMenu(Player **players, char *input);
void save(Player **players);
int load(void);
int playerInit(Player **players);
void boardInit(Player *player);
int playerDestruct(Player **players);
int shipPlacement(char **shipPlacement, int player);
int placeShip(char **shipPlacement, char *start, char *end, char ship);
void printBoard(char **board);
void printUpperRow(void);
int checkShot(char *location);
void exit(int exitCode);
#endif
