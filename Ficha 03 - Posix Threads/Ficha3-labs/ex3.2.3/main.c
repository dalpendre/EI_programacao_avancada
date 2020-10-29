#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"
#include "memory.h"

#define C_ERRO_PTHREAD_CREATE 	1
#define C_ERRO_PTHREAD_JOIN 	2

void *showFiles(void *arg);

int main(int argc, char *argv[])
{
	/* Disable warnings */
	(void)argc; (void)argv;

	pthread_t thread_pares;
	if((errno = pthread_create(thread_pares, NULL, showFiles, NULL)) != 0) 
	{
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
	}

	return 0;
}

void *showFiles(void *arg)
{
	(void)arg;
	printf("My name is Thread, Posix Thread= [%lu]\n", (unsigned long) pthread_self());
	return NULL;
}