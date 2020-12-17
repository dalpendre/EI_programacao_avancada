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

#include "args.h"
#include "debug.h"
#include "memory.h"

#define COUNT_STATE 0
#define NOT_COUNT_STATE 1
#define MAX_LETTERS 26

typedef struct letter_count
{
	char letters[MAX_LETTERS];
	int count;
} letter_count_t;

typedef struct 
{
	int state;
	int bloco;
	FILE *fptr;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}thread_params_t;

void* count_letters(void* arg);

int main(int argc, char *argv[])
{
	/* Disable warnings */
	(void)argc; (void)argv;

	struct gengetopt_args_info args_info;
	size_t filesize = 0;
	int num_threads = args_info.threads_arg;
	int filename = args_info.ficheiro_arg;

	pthread_t threads[num_threads];
	thread_params_t thread_params;
	letter_count_t letter_count;

	thread_params.bloco = args_info.bloco_arg;

	if(cmdline_parser(argc, argv, &args_info))
		ERROR(1, "Erro: execução de cmdline_parser\n");

	thread_params.fptr = fopen(filename, "r");
	
	if(thread_params.fptr == NULL)
	{
		ERROR(1, "Ficheiro não existe\n");
	}

	fseek(thread_params.fptr, 0, SEEK_END);
	filesize = ftell(thread_params.fptr);
	fseek(thread_params.fptr, 0, SEEK_SET); 

	if(thread_params.bloco < 1 || thread_params.bloco > filesize)
	{
		ERROR(2, "Invalid block of bytes to read");
	}

	if((errno = pthread_mutex_init(&thread_params.mutex, NULL)) != 0)
		ERROR(12, "pthread_mutex_init() failed\n");

	if((errno = pthread_cond_init(&thread_params.cond, NULL)) != 0)
		ERROR(14, "pthread_mutex_init() failed\n");


	for(int i = 0; i < num_threads; i++)
	{
		if((errno = pthread_create(&threads[i], NULL, count_letters, &thread_params) != 0)) 
		{   	
			ERROR(10, "Erro no pthread_create()!");
		}

		if((errno = pthread_join(threads[i], NULL) != 0))
		{
				ERROR(11, "Erro no pthread_join()!\n");
		}

		if((errno = pthread_join(threads[i], NULL) != 0))
		{
			ERROR(11, "Erro no pthread_join()!\n");
		}
	}

	if((errno = pthread_mutex_destroy(&thread_params.mutex)) != 0)
		ERROR(13, "pthread_mutex_destroy() failed\n");

	if((errno = pthread_cond_destroy(&thread_params.cond)) != 0)
		ERROR(14, "pthread_mutex_init() failed\n");

	cmdline_parser_free(&args_info);

	return 0;
}

void* count_letters(void* arg)
{
	thread_params_t *params = (thread_params_t *) arg;

	for(int i = 0; i < params->bloco; i++)
	{
		
	}
}