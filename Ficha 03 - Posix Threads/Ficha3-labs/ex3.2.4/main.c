/**
* @file main.c
* @brief Description
* @date 2018-1-1
* @author name of author
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"
#include "memory.h"

#define NUM_ROWS 5
#define NUM_COLS 5

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	size_t mem_len = NUM_ROWS * NUM_COLS * sizeof(int);
	int *matrix_ptr = malloc(mem_len);
	if(matrix_ptr == NULL)
	{
		fprintf(stderr, "Can't allocate %zu bytes for %d x %d matrix\n", mem_len, NUM_ROWS, NUM_COLS);
		exit(4);
	}

	//Fills matrix
	int row, col;
	int idx_row_col;
	for(row=0; row < NUM_ROWS; row++)
	{
		for(col=0; col < NUM_COLS; col++)
		{
			idx_row_col = row * NUM_COLS + col;
			matrix_ptr[idx_row_col] = rand() % 10;
		}
	}

	//Shows matrix
	/*printf("\n");
	for(row=0; row < NUM_ROWS; row++)
	{
		for(col=0; col < NUM_COLS; col++)
		{
			idx_row_col = row * NUM_COLS + col;
			printf("[%d][%d]=%d | ", row, col, matrix_ptr[idx_row_col]);
		}
		printf("\n");
	}
	printf("\n");*/
	
	return 0;
}

