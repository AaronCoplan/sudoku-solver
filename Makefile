INCLUDE_DIR = ./include
OBJ_DIR = ./obj
SRC_DIR = ./src

CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -pedantic -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g -lm

_DEPS = computations.h output.h sudoku.h bruteforce.h
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ = computations.o main.o output.o sudoku.o bruteforce.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o *~ build* $(INCLUDE_DIR)/*~
