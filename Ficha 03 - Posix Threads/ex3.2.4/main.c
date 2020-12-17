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
#include <pthread.h>
#include <sys/wait.h>

#include "debug.h"
#include "memory.h"
#include "args.h"

#define NUM_ROWS 5
#define NUM_COLS 5

typedef struct elements
{
	int a;
	int b;
	int c;
	int d;
} elementos;

int* calculateElement(elementos* elementos);

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	elementos elementosParaElementoMatrixFinal;
	size_t mem_len = NUM_ROWS * NUM_COLS * sizeof(int);
	int *matrixA_ptr = malloc(mem_len);
	int *matrixB_ptr = malloc(mem_len);
	int *matrixResultado_ptr = malloc(mem_len);

	if(matrixA_ptr == NULL)
	{
		fprintf(stderr, "Can't allocate %zu bytes for %d x %d matrix\n", mem_len, NUM_ROWS, NUM_COLS);
		exit(4);
	}

	if(matrixB_ptr == NULL)
	{
		fprintf(stderr, "Can't allocate %zu bytes for %d x %d matrix\n", mem_len, NUM_ROWS, NUM_COLS);
		exit(4);
	}

	if(matrixResultado_ptr == NULL)
	{
		fprintf(stderr, "Can't allocate %zu bytes for %d x %d matrix\n", mem_len, NUM_ROWS, NUM_COLS);
		exit(4);
	}

	//Fills matrix A
	int row, col;
	int idx_row_col;
	for(row=0; row < NUM_ROWS; row++)
	{
		for(col=0; col < NUM_COLS; col++)
		{
			idx_row_col = row * NUM_COLS + col;
			matrixA_ptr[idx_row_col] = rand() % 10;
		}
	}

	//Fills matrix B
	for(row = 0; row < NUM_ROWS; row++)
	{
		for(col = 0; col < NUM_COLS; col++)
		{
			idx_row_col = row * NUM_COLS + col;
			matrixA_ptr[idx_row_col] = rand() % 10;
		}
	}

	//Calculates the resultant matrix using threads
	/*for(row=0; row < NUM_ROWS; row++)
	{
		for(col=0; col < NUM_COLS; col++)
		{
			elementosParaElementoMatrixFinal.a = col;
			elementosParaElementoMatrixFinal.b = col + 1;
			elementosParaElementoMatrixFinal.c = row;
			elementosParaElementoMatrixFinal.d = row + 1;

			pthread_t tid;
			if((errno = pthread_create(&tid, NULL, calculateElement, &elementosParaElementoMatrixFinal) != 0))
				ERROR(10, "Erro no pthread_create()!\n");	
		}
		printf("\n");
	}*/

	//Shows matrix
	printf("\n");
	for(row=0; row < NUM_ROWS; row++)
	{
		for(col=0; col < NUM_COLS; col++)
		{
			idx_row_col = row * NUM_COLS + col;
			printf("[%d][%d]=%d | ", row, col, matrixA_ptr[idx_row_col]);
		}
		printf("\n");
	}
	printf("\n");
	
	return 0;
}

//Calculates matrix element
int* calculateElement(elementos* elementos)
{
	int elementoFinal = elementos->a * elementos->b + elementos->c * elementos->d;

	printf("%d * %d + %d * %d = %d\n", elementos->a, elementos->b, 
	elementos->c, elementos->d, elementoFinal);

	return elementoFinal;
}