/*
 * Bruce Cain
 *
 * Battleship header file.
 */

#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

typedef struct ShipHit
{
    char patrol:2;
    char sub:2;
    char cruiser:2;
    char destroyer:2;
    char battleship:2;
    char aircraft:2;
} ShipHit;

typedef struct ShipHP
{
    char patrolHit:3;
    char subHit:3;
    char cruiserHit:4;
    char destroyerHit:4;
    char battleshipHit:5;
    char aircraftHit:6;

} ShipHP;

typedef struct Player
{
    char size;
    char totalShots;
    char hits;
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
