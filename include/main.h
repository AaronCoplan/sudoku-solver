#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "computations.h"
#include "output.h"
#include "sudoku.h"
#include "bruteforce.h"

int main(void);
void attempt_row_insertions(int row_num);
void attempt_col_insertions(int col_num);
void attempt_square_insertions(int square_x, int square_y);

#endif
