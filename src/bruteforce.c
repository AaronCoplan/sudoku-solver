#include "bruteforce.h"
//#include "sudoku.h"
#define RESET 0

int ** sudoku;




/*
//Test Sudoku
int sudoku[9][9]= {   {0, 0, 6, 7, 0, 0, 0, 0, 8},
                      {0, 5, 0, 0, 6, 0, 0, 2, 0},
                      {9, 0, 0, 0, 0, 1, 6, 0, 0},
                      {6, 0, 0, 0, 0, 9, 5, 0, 0},
                      {0, 4, 0, 0, 3, 0, 0, 8, 0},
                      {0, 0, 9, 8, 0, 0, 0, 0, 4},
                      {0, 0, 7, 2, 0, 0, 0, 0, 5},
                      {0, 2, 0, 0, 4, 0, 0, 9, 0},
                      {5, 0, 0, 0, 0, 7, 3, 0, 0}
                 };
*/
int row,col;
long int Calls =0;

int findEmptyCell(void){
    int i,j;

    for(i = row ; i<=8; i++){
        for( j = 0; j<=8; j++){
            if(sudoku[i][j] == 0){
                row = i; 
                col = j;
                return 1;
            }
        }
    }
    return 0;
}

int isValid(int cRow, int cCol, int num){
    int i,j;
        //trow,tcol,trow1,tcol1;
    int rowStart = (cRow/3) * 3;
    int colStart = (cCol/3) * 3;

    //Check Row && Column

    for (j = 0; j<=8; j++){
        if(sudoku[cRow][j] == num)
                return 0;
        if(sudoku[j][cCol] == num)
                return 0;
     }

    //Ckeck 3x3

    for (i=rowStart; i<=(rowStart +2); i++){
        for (j=colStart; j<=(colStart +2); j++){
            if (sudoku[i][j] == num) return 0;
        }
    }
    return 1;
 }

 int sudokuSolver(void){
    int digit;
    int pRow, pCol;
    Calls++;

    if(!findEmptyCell())
        return 1;

    for(digit=1; digit<=9; digit++){
        if(isValid(row,col,digit)){
            sudoku[row][col]=digit;
            pRow = row;
            pCol = col;
            if (sudokuSolver())
                return 1;
//Backtracking
            row = pRow; col = pCol;
            sudoku[row][col] = RESET;
        }
    }

    return 0;

}
/*
void printSudoku(){

 int i,j;

    printf("Calls:%ld\n",Calls);

 printf("\t-------------------------\n");
 for(i=0;i<9;i++){
    printf("\t");
    for(j=0;j<9;j++){
       if(j==0)
    printf("| ");
       if(sudoku[i][j]==0)
    printf(". ");
       else
    printf("%d ",sudoku[i][j]);
       if((j+1)%3==0 )
    printf("| ");

   }

   if((i+1)%3==0 )
       printf("\n\t-------------------------");

   printf("\n");

 }

}*/
