#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/time.h>

#include "debug.h"

#define C_ERRO_PTHREAD_CREATE 	1
#define C_ERRO_PTHREAD_JOIN 	2
#define NUM_THREADS 2
#define NUM_PROCESSOS 3

void* task(void *arg);

int main(int argc, char* argv[])
{
	(void)argc; 
	(void)argv;

	pid_t pid;
	for(int i = 0; i < NUM_PROCESSOS; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			pthread_t tids[NUM_THREADS];
			for(int i = 0; i < NUM_THREADS; i++)
			{
				if((errno = pthread_create(&tids[i], NULL, task, NULL)) != 0)
				{
					ERROR(2, "Erro no pthread_create()!");
				}
			}

			for(int i = 0; i < NUM_THREADS; i++)
			{
				if((errno = pthread_join(tids[i], NULL)) != 0)
				{
					ERROR(3, "Erro no pthread_join()!\n");
				}
			}

			exit(0);
		}
		else if(pid > 0)
		{

		}
		else
		{
			ERROR(1, "Erro na execução do fork()\n");
		}
		
	}

	return 0;
}

void* task(void *arg)
{
	(void) arg;

	printf("\n\tPID: %d | PPID: %d | TID: %lu\n", getpid(), getppid(), pthread_self());

	return NULL;
}