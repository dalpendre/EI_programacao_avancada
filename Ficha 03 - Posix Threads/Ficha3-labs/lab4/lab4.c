#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "debug.h"

#define C_ERRO_PTHREAD_CREATE 1

void *hello(void *arg);


int main (int argc, char *argv[])
{
	pthread_t tid;
	(void)argc; (void)argv;

	if ((errno = pthread_create(&tid, NULL, hello, NULL)) != 0) {
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
	}
	
	exit(0);
}


void *hello(void *arg)
{
	(void)arg;
	printf("My name is Thread, Posix Thread= [%lu]\n", (unsigned long) pthread_self());
	return NULL;
}

