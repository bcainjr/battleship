CC = gcc
CFLAGS = $(CF) -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=512 -Wfloat-equal -Waggregate-return -Winline
OUT = BIN/battleship
SRC = SRC/battleship.c SRC/BattleshipGame.c
DEPS = SRC/BattleshipGame.h
OBJ = SRC/battleship.o SRC/BattleshipGame.o 

all:
	@$(CC) $(CFLAGS) -o $(OUT) $(SRC)

debug: $(DEPS)
	@$(CC) -g $(CFLAGS) -o $(OUT) $(SRC)

build: clean $(DEPS)
	@$(CC) $(CFLAGS) -o $(OUT) $(SRC)

buildAll: $(DEPS)
	@$(CC) -g $(CFLAGS) -o $(OUT) $(SRC)

cleanAll:
	-@rm -rf *.o $(OUT)

clean:
	-@rm -rf *.o
