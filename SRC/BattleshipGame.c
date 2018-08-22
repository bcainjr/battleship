/*
* TDQC5
* Bruce Cain
*
* BattleshipGame source
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "BattleshipGame.h"

#define HIT          'H'
#define MISS         'M'

/* Error codes */
#define VALID          1
#define INVALID        0
#define BADCALLOC      9
#define BADPLAYERINIT 10
#define FAILEDLOAD    11
#define WIN           19

static int getWidth(int num)
{
    int size = 0;

    if(num == 0)
    {
        num++;
    }

    while(num != 0)
    {
        num /= 10;
        size++;
    }

    return size;
}

static void getBoardSize(Player **players)
{
    char *line = NULL;
    size_t size = 0;

    printf("Board size: ");
    do
    {
        getline(&line, &size, stdin);
        if(atoi(line) < 10 || atoi(line) > 26)
        {
            printf("\033[1A\033[K");
            printf("Try again, 10 to 26: ");
            continue;
        }

        break;
    }while(1);

    players[0]->size = atoi(line);
    players[1]->size = atoi(line);
    free(line);
}

void printDivider(int boardSize)
{
    for(int i = 0; i < boardSize * 2 + 3; i++)
    {
        printf("=");
    }
    printf("\n");
}

void printUpperRow(int size)
{
    int rowWidth = getWidth(size);
    char const *upperRow = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    printf("%*c ", rowWidth, ' ');

    for(int i = 0; i < size; i++)
    {
        printf("%c ", upperRow[i]);
    }

    printf("\n");
}

void printBoard(char **board, int size)
{
    int rowWidth = getWidth(size);
    printUpperRow(size);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size + 1; j++)
        {
            if(!j)
            {
                printf("%*d ", rowWidth, i+1);
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

int placeShip(char **shipPlacement, int boardSize, char *start, char *end, 
        char ship, Ships size)
{
    /* Check bounds and ship length */
    if(!validLocationInput(shipPlacement, boardSize, start, end, size))
    {
        return INVALID;
    }

    for(int j = toupper(*start) - 'A'; j < toupper(*end) - 'A' + 1; j++)
    {
        for(int i = strtol(start+1, NULL, 10); i < strtol(end+1, NULL, 10) + 1; i++)
        {
            shipPlacement[i-1][j] = ship;
        }
    }

    return VALID;
}

int validLocationInput(char **shipPlacement, int boardSize, char *start, char *end, Ships size)
{
    int startVal = (toupper(*start) - 'A') + strtol(start+1, NULL, 10),
        endVal = (toupper(*end) - 'A') + strtol(end+1, NULL, 10),
        row = strtol(start+1, NULL, 10),
        column = toupper(*start) - 'A';
    char startBoundry = startVal >= 1 && startVal < (boardSize * 2),
         endBoundry = endVal >= 1 && endVal < (boardSize * 2),
         boatLength = endVal - startVal + 1 == (int) size;

    
    if(!startBoundry || !endBoundry || !boatLength ||
           shipPlacement[row][column] || shipPlacement[row][column])
    {
        return INVALID;
    }

    for(int j = toupper(*start) - 'A'; j < toupper(*end) - 'A' + 1; j++)
    {
        for(int i = strtol(start+1, NULL, 10); i < strtol(end+1, NULL, 10) + 1; i++)
        {
            if(shipPlacement[i-1][j])
            {
                return INVALID;
            }
        }
    }
    return VALID;
}

int autoShipPlacement(char **shipPlacement, int boardSize)
{
    char start[7][3] = 
        {
            "a1", "a3", "a5", "b1", "c1", "d1"
        }, 
        end[7][3] = 
        {
            "a2", "a4", "c5", "b3", "c4", "d5"
        };
    char ships[7][17] =
    {
        "Patrol Boat", "Submarine", "Cruiser",
        "Destroyer", "Battleship", "Aircraft Carrier"
    };
    Ships ship[7] =
    {
        Patrol, Sub, Cruiser,
        Destroyer, Battleship,
        Carrier
    };

    for(int i = 0; i < 6; i++)
    {
        placeShip(shipPlacement, boardSize, start[i], end[i], ships[i][0], ship[i]);
    }

    return VALID;
}


int shipPlacement(char **shipPlacement, int player, int boardSize)
{
    char *start = NULL, *end = NULL;
    size_t size = 0;
    char ships[7][17] =
    {
        "Patrol Boat", "Submarine", "Cruiser",
        "Destroyer", "Battleship", "Aircraft Carrier"
    };
    Ships ship[7] =
    {
        Patrol, Sub, Cruiser,
        Destroyer, Battleship,
        Carrier
    };

    for(int i = 0; i < 6; i++)
    {
        system("tput reset");
        printBoard(shipPlacement, boardSize);
        printf("Player %d place:\n%4c%s Size: %u\n", 
                player + 1, ' ', ships[i], ship[i]);

        printf("Start> ");
        getline(&start, &size, stdin);
        start[strlen(start)-1] = '\0';

        printf("End  > ");
        getline(&end, &size, stdin);
        end[strlen(end)-1] = '\0';


        if(!placeShip(shipPlacement, boardSize, start, end, ships[i][0], ship[i]))
        {
            /* Try again */
            i--;
        }
    }

    free(start);
    free(end);
    return VALID;
}

void boardInit(Player *player)
{
    player->hitMiss = calloc(player->size, sizeof(char *));
    player->shipPlacement = calloc(player->size, sizeof(char *));

    for(int i = 0; i < player->size; i++)
    {
        player->hitMiss[i] = calloc(player->size, sizeof(char));
        player->shipPlacement[i] = calloc(player->size, sizeof(char));
    }
}

void playerDestruct(Player **players)
{
    for(int i = 0; i < 2; i++)
    {
        free(players[i]->shipHit);
        free(players[i]->shipHP);

        for(int j = 0; j < players[i]->size; j++)
        {
            free(players[i]->hitMiss[j]);
            free(players[i]->shipPlacement[j]);
        }

        free(players[i]->hitMiss);
        free(players[i]->shipPlacement);
        free(players[i]);
    }
}

int playerInit(Player **players)
{
    for(int i = 0; i < 2; i++)
    {
        players[i] = calloc(sizeof(Player), 1);
        players[i]->shipHit = calloc(sizeof(ShipHit), 1);
        players[i]->shipHP = calloc(sizeof(ShipHP), 1);

        if(players[i] == NULL)
        {
            return BADCALLOC;
        }
    }

    return VALID;
}

void saveBoard(char **board, int size, FILE *saveFile)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fwrite(&board[i][j], sizeof(char), 1, saveFile);
        }
    }
}

void writeSave(Player **players)
{
    FILE *saveFile = fopen("SRC/.battleship", "wb");

    if(saveFile == NULL)
    {
        saveFile = fopen("../SRC/.battleship", "wb");

        if(saveFile == NULL)
        {
            fprintf(stderr, "Couldn't open save file.\n");
            return;
        }
    }

    for(int i = 0; i < 2; i++)
    {
        fwrite(&players[i]->size, sizeof(char), 1, saveFile);
        fwrite(&players[i]->totalShots, sizeof(char), 1, saveFile);
        fwrite(&players[i]->hits, sizeof(char), 1, saveFile);
        fwrite(players[i]->shipHP, sizeof(ShipHP), 1, saveFile);
        fwrite(players[i]->shipHit, sizeof(ShipHit), 1, saveFile);
        saveBoard(players[i]->hitMiss, players[i]->size, saveFile);
        saveBoard(players[i]->shipPlacement, players[i]->size, saveFile);
    }

    fclose(saveFile);
}

void save(Player **players)
{
    char *line = NULL, saving = 1;
    size_t size = 0;

    printf("Save game? y/n\n> ");

    do
    {
        getline(&line, &size, stdin);

        switch(line[0])
        {
            case 'y':
            case 'Y':
            {
                writeSave(players);
                free(line);
                return;
            }
            case 'n':
            case 'N':
            {
                free(line);
                return;
            }
            default:
            {
                /* Move cursor up one line and delete its contents */
                printf("\033[1A\033[K");
                printf("Invalid Value, try again\n> ");
            }
        }
    } while(saving);
}

void loadBoard(char **board, int size, FILE *loadFile)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fread(&board[i][j], sizeof(char), 1, loadFile);
        }
    }

}

void readLoad(Player **players, FILE *loadFile)
{
    playerInit(players);
    for(int i = 0; i < 2; i++)
    {
        fread(&players[i]->size, sizeof(char), 1, loadFile); 
        fread(&players[i]->totalShots, sizeof(char), 1, loadFile);
        fread(&players[i]->hits, sizeof(char), 1, loadFile);
        fread(players[i]->shipHP, sizeof(ShipHP), 1, loadFile);
        fread(players[i]->shipHit, sizeof(ShipHit), 1, loadFile);
        boardInit(players[i]);
        loadBoard(players[i]->hitMiss, players[i]->size, loadFile);
        loadBoard(players[i]->shipPlacement, players[i]->size, loadFile);
    }
}

int load(Player **players)
{
    FILE *loadFile = fopen("SRC/.battleship", "rb");

    if(loadFile == NULL)
    {
        loadFile = fopen("../SRC/.battleship", "rb");
        if(loadFile == NULL)
        {
            fprintf(stderr, "Failed to load file.\n");
            sleep(2);
            return INVALID;
        }
    }

    readLoad(players, loadFile);
    fclose(loadFile);

    return VALID;
}

int newGame(Player **players)
{
    if(!playerInit(players))
    {
        fprintf(stderr, "Player initialize fail.\n");
        return BADPLAYERINIT;
    }

    getBoardSize(players);

    for(int i = 0; i < 2; i++)
    {
        boardInit(players[i]);
        autoShipPlacement(players[i]->shipPlacement, players[i]->size);
        //shipPlacement(players[i]->shipPlacement, i, players[i]->size);
    } 

    return VALID;
}

char checkShot(Player *player, int row, int column)
{
    switch(player->shipPlacement[row-1][column])
    {
        case 'P':
        {
            player->shipHP->patrolHit++;
            break;
        }
        case 'S':
        {
            player->shipHP->subHit++;
            break;
        }
        case 'C':
        {
            player->shipHP->cruiserHit++;
            break;
        }
        case 'D':
        {
            player->shipHP->destroyerHit++;
            break;
        }
        case 'B':
        {
            player->shipHP->battleshipHit++;
            break;
        }
        case 'A':
        {
            player->shipHP->aircraftHit++;
            break;
        }
    }

    if(player->shipPlacement[row-1][column])
    {
        player->hits += 1;
        return HIT;
    }

    return MISS;
}

void checkSunkinShip(Player *player, int turn)
{
    char flag = 1, printShip[17] = {0}, 
         ships[7][17] =
         {
             "Patrol Boat", "Submarine", "Cruiser",
             "Destroyer", "Battleship", "Aircraft Carrier"
         };
    Ships ship[7] =
          {
              Patrol, Sub, Cruiser,
              Destroyer, Battleship,
              Carrier
          };

    if(player->shipHP->patrolHit == (char) ship[0] &&
            !player->shipHit->patrol)
    {
        player->shipHit->patrol = 1;
        strcpy(printShip, ships[0]);
    }
    else if(player->shipHP->subHit == (char) ship[1] &&
            !player->shipHit->sub)
    {
        player->shipHit->sub = 1;
        strcpy(printShip, ships[1]);
    }
    else if(player->shipHP->cruiserHit == (char) ship[2] &&
            !player->shipHit->cruiser)
    {
        player->shipHit->cruiser = 1;
        strcpy(printShip, ships[2]);
    }
    else if(player->shipHP->destroyerHit == (char) ship[3] &&
            !player->shipHit->destroyer)
    {
        player->shipHit->destroyer = 1;
        strcpy(printShip, ships[3]);
    }
    else if(player->shipHP->battleshipHit == (char) ship[4] &&
            !player->shipHit->battleship)
    {
        player->shipHit->battleship = 1;
        strcpy(printShip, ships[4]);
    }
    else if(player->shipHP->aircraftHit == (char) ship[5] &&
            !player->shipHit->aircraft)
    {
        player->shipHit->aircraft = 1;
        strcpy(printShip, ships[5]);
    }
    else
    {
        flag = 0;
    }

    if(flag)
    {
        printf("Player %d sunk your %s!\n", turn, printShip);
    }
}

int validGameInput(int boardSize, int row, int column)
{
    if((row >= 1) && (row <= boardSize) &&
            (column >= 0) && (column <= boardSize))
    {
        return VALID;
    }

    return INVALID;
}

int checkTurn(Player **players)
{
    if(players[0]->totalShots <= players[1]->totalShots)
    {
        return 0;
    }

    return 1;
}

int mainMenu(Player **players, char *input)
{
    switch(input[0])
    {
        case '1':
        {
            if(!newGame(players))
            {
                free(input);
                return INVALID;
            }
            break;
        }
        case '2':
        {
            if(!load(players))
            {
                return INVALID;
            }
            break;
        }
        case 'q':
        case 'Q':
        {
            printf("Exiting...\n");
            free(input);
            exit(VALID);
        }
        default:
        {
            return INVALID;
        }
    }

    free(input);
    return VALID;
}

int game(Player **players, int turn)
{
    char *line = NULL;
    static char shot;
    size_t size = 0;
    int column = 0;
    long row = 0;

    checkSunkinShip(players[turn^1], turn+2);

    printBoard(players[turn]->hitMiss, players[turn]->size);
    printDivider(players[turn]->size);
    printBoard(players[turn]->shipPlacement, players[turn]->size);
    printf("Player %d SHOOT!\nType quit to exit.\n", turn + 1);

    do
    {
        getline(&line, &size, stdin);
        line[strlen(line) - 1] = '\0';

        /* Move cursor up one line and delete its contents */
        printf("\033[1A\033[K");

        if(!strcmp(line, "quit"))
        {
            save(players);
            free(line);
            return 0;
        }

        column = toupper(line[0]) - 'A';
        row = strtol(line + 1, NULL, 10);
    }while(!validGameInput(players[turn]->size, row, column) ||
            players[turn]->hitMiss[row-1][column]);

    players[turn]->totalShots++;
    shot = checkShot(players[turn], row, column); 
    players[turn]->hitMiss[row-1][column] = shot; 
    players[turn^1]->shipPlacement[row-1][column] = shot;

    free(line);

    if(players[turn]->hits == WIN)
    {
        printf("Player %d WINS!\n", turn + 1);
        return 0;
    }

    return 1;
}
