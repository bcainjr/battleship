/*
 * Bruce Cain
 *
 * Battleship header file.
 */

#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

#include <stdint.h>

#define BANNER  " ____        _   _   _           _     _       \n"\
                "| __ )  __ _| |_| |_| | ___  ___| |__ (_)_ __  \n"\
                "|  _ \\ / _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ \n"\
                "| |_) | (_| | |_| |_| |  __/\\__ \\ | | | | |_) |\n"\
                "|____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/ \n"\
                "                                        |_|    \n"


typedef struct ShipHit
{
    uint8_t patrol:1;
    uint8_t sub:1;
    uint8_t cruiser:1;
    uint8_t destroyer:1;
    uint8_t battleship:1;
    uint8_t aircraft:1;
} ShipHit;

typedef struct ShipHP
{
    uint8_t patrolHit:2;
    uint8_t subHit:2;
    uint8_t cruiserHit:2;
    uint8_t destroyerHit:2;
    uint8_t battleshipHit:3;
    uint8_t aircraftHit:3;

} ShipHP;

typedef struct Player
{
    uint8_t size;
    uint8_t hits;
    uint8_t totalShots;
    ShipHP *shipHP;
    ShipHit *shipHit;
    char **hitMiss;
    char **shipPlacement;
} Player;

typedef enum Ships
{
    Patrol     = 2, 
    Sub        = 2, 
    Cruiser    = 3,
    Destroyer  = 3, 
    Battleship = 4,
    Carrier    = 5
} Ships;

int mainMenu(Player **players, char *input);
int game(Player **players, int turn);
void save(Player **players);
void wrtieSave(Player **players);
void saveBoard(char **board, int size, FILE *saveFile);
int load(Player **players);
void readLoad(Player **players, FILE *loadFile);
void loadBoard(char **board, int size, FILE *loadFile);
int newGame(Player **players);
int checkTurn(Player **players);
int playerInit(Player **players);
void boardInit(Player *player);
void playerDestruct(Player **players);
int shipPlacement(char **shipPlacement, int player, int size);
int autoShipPlacement(char **shipPlacement, int size);
int placeShip(char **shipPlacement, int boardSize, char *start, char *end, 
        char ship, Ships size);
int validLocationInput(char **shipPlacement, int boardSize, char *start, char *end, Ships size);
int shipCheck(char *start, char *end, char ship);
void printBoard(char **board, int size);
void printUpperRow(int size);
void checkSunkinShip(Player *player, int turn);
int validGameInput(int boardSize, int row, int column);
char checkShot(Player *player, int row, int column);
void exit(int exitCode);
#endif
