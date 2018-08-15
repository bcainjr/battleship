CC = gcc
CFLAGS = $(CF) -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=512 -Wfloat-equal -Waggregate-return -Winline
OUT = battleship
SRC = battleship.c BattleshipGame.c
DEPS = BattleshipGame.h
OBJ = battleship.o BattleshipGame.o 

all:
	@$(CC) $(CFLAGS) -o $(OUT) $(SRC)

debug:
	@$(CC) -g $(CFLAGS) -o $(OUT) $(SRC)

clean:
	-@rm -rf *.o $(OUT)

