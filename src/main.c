#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "structs.h"
#include "output.h"
#include "sudoku.h"
#include "computations.h"

#define USAGE_INFO "Usage: ./build <sudoku file path>"

static int attempt_row_insertions(int row_num);
static int attempt_col_insertions(int col_num);
static int attempt_square_insertions(int square_x, int square_y);

int main(int argc, char** argv){
        int row;
        int col;
        int square_x;
        int square_y;
        int num_runs;
        int num_unsolved;
        int last_unsolved;
        int exit_code;
        int changes_made;
        char* file_path;
        struct timeval start_time, end_time;

        if(argc != 2){
                printf("Invalid number of arguments!\n");
                printf("%s\n", USAGE_INFO);
                return -1;
        }

        file_path = argv[1];

        allocate_sudoku();
        populate_values(file_path);

        print_sudoku();

        num_runs = 0;
        changes_made = 0;

        gettimeofday(&start_time, NULL);

        last_unsolved = 81;

        while(1){
                num_unsolved = get_num_unsolved(get_sudoku());
                if(num_unsolved == 0){
                        exit_code = 0;
                        break;
                }

                if(num_unsolved == last_unsolved){
                        exit_code = -1;
                        break;
                }

                for(row = 0; row < 9; ++row){
                        changes_made += attempt_row_insertions(row);
                }
                for(col = 0; col < 9; ++col){
                        changes_made += attempt_col_insertions(col);
                }
                for(square_x = 0; square_x < 3; ++square_x){
                        for(square_y = 0; square_y < 3; ++square_y){
                                changes_made += attempt_square_insertions(square_x, square_y);
                        }
                }

                ++num_runs;

                last_unsolved = num_unsolved;
        }

        // fix for when it gets stuck
        if(exit_code == -1){
                // enter some other algorithm, most likely a brute force solution using backtracking
                printf("Got stuck using intelligent algorithm, entering brute force now...\n");
                sudokuSolver();
        }

        printf("Finished\n");

        gettimeofday(&end_time, NULL);

        printf("Time in microseconds: %ld\n", ((end_time.tv_sec - start_time.tv_sec)*1000000L +end_time.tv_usec) - start_time.tv_usec);

        printf("Num Passes: %d\n", num_runs);
        printf("Number of changes made by intelligent algorithm: %d\n", changes_made);
        printf("\n");
        print_sudoku();

        free_sudoku();

        return 0;
}

static int attempt_square_insertions(int square_x, int square_y){
        int** square;
        struct array* missing_numbers;
        int i;
        int num;
        int row;
        int col;
        int num_options;
        int option_row;
        int option_col;
        int* row_array;
        int* col_array;
        int changes_made;

        square = get_square(square_x, square_y);
        missing_numbers = calculateSquareMissingNumbers(square);

        print_3x3_array(square);
        print_array_struct(missing_numbers);

        changes_made = 0;

        for(i = 0; i < missing_numbers->size; ++i){
                num = missing_numbers->data[i];
                num_options = 0;
                option_col = 0;
                option_row = 0;

                for(row = (3*square_x); row < ((3*square_x)+3); ++row){
                        for(col = (3*square_y); col < ((3*square_y)+3); ++col){
                                if(get_value(row, col) == 0){
                                        row_array = get_row(row);
                                        if(!contains_len9(row_array, num)){
                                                col_array = get_col(col);
                                                if(!contains_len9(col_array, num)){
                                                        ++num_options;
                                                        option_col = col;
                                                        option_row = row;
                                                }
                                                free_1d_array(col_array);
                                        }
                                        free_1d_array(row_array);
                                }
                        }
                }

                if(num_options == 1){
                        set_val(option_row, option_col, num);
                        printf("Change made\n");
                        print_sudoku();
                        ++changes_made;
                }
        }

        free_2d_array(square);
        free_array_struct(missing_numbers);

        return changes_made;
}

static int attempt_col_insertions(int col_num){
        int* col;
        struct array* missing_numbers;
        int i;
        int num;
        int row;
        int square_x;
        int square_y;
        int num_options;
        int option_row;
        int* row_array;
        int** square_array;
        int changes_made;

        square_y = col_num / 3;

        col = get_col(col_num);

        missing_numbers = calculateMissingNumbers(col);

        print_size9_array(col);
        print_array_struct(missing_numbers);

        changes_made = 0;

        for(i = 0; i < missing_numbers->size; ++i){
                num = missing_numbers->data[i];
                num_options = 0;
                option_row = 0;

                for(row = 0; row < 9; ++row){
                        if(get_value(row, col_num) == 0){
                                row_array = get_row(row);
                                if(!contains_len9(row_array, num)){
                                        square_x = row / 3;

                                        square_array = get_square(square_x, square_y);
                                        if(!contains_square(square_array, num)){
                                                ++num_options;
                                                option_row = row;
                                        }
                                        free_2d_array(square_array);
                                }
                                free_1d_array(row_array);
                        }
                }

                if(num_options == 1){
                        set_val(option_row, col_num, num);
                        printf("Change made\n");
                        print_sudoku();
                        ++changes_made;
                }
        }

        free_1d_array(col);
        free_array_struct(missing_numbers);

        return changes_made;
}

static int attempt_row_insertions(int row_num){
        int* row;
        struct array* missing_numbers;
        int i;
        int num;
        int col;
        int square_x;
        int square_y;
        int num_options;
        int option_col;
        int* col_array;
        int** square_array;
        int changes_made;

        square_x = row_num / 3;

        row = get_row(row_num);

        missing_numbers = calculateMissingNumbers(row);

        //print_size9_array(row);
        //print_array_struct(missing_numbers);

        changes_made = 0;

        for(i = 0; i < missing_numbers->size; ++i){
                num = missing_numbers->data[i];
                num_options = 0;
                option_col = 0;

                for(col = 0; col < 9; ++col){
                        if(get_value(row_num, col) == 0){
                                col_array = get_col(col);
                                if(!contains_len9(col_array, num)){
                                        square_y = col / 3;

                                        square_array = get_square(square_x, square_y);
                                        if(!contains_square(square_array, num)){
                                                ++num_options;
                                                option_col = col;
                                        }
                                        free_2d_array(square_array);
                                }
                                free_1d_array(col_array);
                        }
                }

                if(num_options == 1){
                        set_val(row_num, option_col, num);
                        printf("Change made\n");
                        print_sudoku();
                        ++changes_made;
                }
        }

        free_1d_array(row);
        free_array_struct(missing_numbers);

        return changes_made;
}
