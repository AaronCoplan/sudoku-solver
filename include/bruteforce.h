#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include<stdio.h>
#include<stdlib.h>
#include<sudoku.h>

int findEmptyCell(void);
int isValid(int cRow, int cCol, int num);
int sudokuSolver(void);
//void printSudoku();

#endif
