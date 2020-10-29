/**
* @file main.c
* @brief Description
* @date 2015-10-24
* @author name of author
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <pthread.h>

#include "args.h"
#include "debug.h"
#include "memory.h"

#define MAX_LETTER 26

typedef struct 
{
	int state;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}thread_params_t;

typedef struct
{
	char letter;
	int letter_counter;
}letter_counts_t; 

void* ler_bytes(void* arg);

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	struct gengetopt_args_info args_info;
	letter_counts_t letter_counts[MAX_LETTER];

	//Fill letter counts with letters
	for(int i = 0; i < MAX_LETTER; i++)
	{
		letter_counts[i].letter = 'a' + i;
	}

	for (int i = 0; i < MAX_LETTER; i++)
	{
		printf("%c\n", letter_counts[i].letter);
	}
	
	if(cmdline_parser(argc, argv, &args_info))
	{
		ERROR(1, "Erro: execução de cmdline_parser\n");
	}

	FILE *fptr = fopen(args_info.ficheiro_arg, "r");

	if(fptr == NULL)
	{
		ERROR(1, "File %s can't be opened\n", args_info.ficheiro_arg);
		exit(0);
	}

	pthread_t threads[args_info.num_threads_arg];
	thread_params_t thread_params;

	void* ler_bytes(void* arg);

	printf("\n\tThread\tBytes a ler no ficheiro\n");
	//Each thread will execute the block size until the limit of the file size
	for(int i = 0; i < args_info.num_threads_arg; i++)
	{		
		if ((errno = pthread_create(&threads[i], NULL, ler_bytes, &threads[i])) != 0){
			ERROR(10, "Erro no pthread_create()!");
		}

		printf("")
	}

	cmdline_parser_free(&args_info);

	return 0;
}

void* ler_bytes(void *arg)
{
	return NULL;
}
