#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "debug.h"

#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2

void *hello(void *arg);

int main(int argc, char *argv[]) 
{
	pthread_t tid;
	(void)argc;(void)argv;

	if((errno = pthread_create(&tid, NULL, hello, NULL)) != 0) 
	{
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
	}	
	
	printf("Processo: TID da thread criada = [%lu]\n", (unsigned long) tid);	
	
	if ((errno = pthread_join(tid, NULL)) != 0) 
	{
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
	}

	exit(0);
}


void *hello(void *arg) 
{
	(void)arg;
	printf("My name is Thread, Posix Thread= [%lu]\n", (unsigned long) pthread_self());
	return NULL;
}

