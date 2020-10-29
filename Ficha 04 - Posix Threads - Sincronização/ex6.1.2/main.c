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

#define LIMIT 10
#define PING 0
#define PONG 1

typedef struct 
{
	int state;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}thread_params_t;

void* task(void* arg);
int contador;

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	pthread_t tid_ping, tid_pong;
	thread_params_t thread_params;
	thread_params.state = PING;

	void* ping(void* arg);
	void* pong(void* arg);

	if((errno = pthread_mutex_init(&thread_params.mutex, NULL)) != 0)
		ERROR(12, "pthread_mutex_init() failed\n");

	if((errno = pthread_cond_init(&thread_params.cond, NULL)) != 0)
		ERROR(14, "pthread_mutex_init() failed\n");

	if((errno = pthread_create(&tid_ping, NULL, ping, &thread_params) != 0)) 
	{   	
		ERROR(10, "Erro no pthread_create()!");
	}

	if((errno = pthread_create(&tid_pong, NULL, pong, &thread_params) != 0)) 
	{   	
		ERROR(10, "Erro no pthread_create()!");
	}

	if((errno = pthread_join(tid_ping, NULL) != 0))
	{
			ERROR(11, "Erro no pthread_join()!\n");
	}

	if((errno = pthread_join(tid_pong, NULL) != 0))
	{
		ERROR(11, "Erro no pthread_join()!\n");
	}

	if((errno = pthread_mutex_destroy(&thread_params.mutex)) != 0)
		ERROR(13, "pthread_mutex_destroy() failed\n");

	if((errno = pthread_cond_destroy(&thread_params.cond)) != 0)
		ERROR(14, "pthread_mutex_init() failed\n");


	return 0;
}

void* ping(void* arg)
{
	thread_params_t *params = (thread_params_t *) arg;

	for(int i = 0; i < LIMIT; i++)
	{	
		if((errno = pthread_mutex_lock(&(params->mutex))) != 0)
		{
			WARNING("pthread_mutex_lock() failed\n");
			return NULL;
		}

		while(params->state != PING)
		{
			if((errno = pthread_cond_wait(&(params->cond), &(params->mutex))) != 0)
			{
				WARNING("pthread_cond_wait() failed\n");
				return NULL;
			}
		}

		printf("\n\tping...");
		params->state = PONG;

		if((errno = pthread_cond_signal(&(params->cond))) != 0)
		{
			WARNING("pthread_cond_signal() failed\n");
			return NULL;
		}

		if((errno = pthread_mutex_unlock(&(params->mutex))) != 0)
		{
			WARNING("pthread_mutex_unlock() failed\n");
			return NULL;
		}
	}

	return NULL;
}

void* pong(void* arg)
{
	thread_params_t *params = (thread_params_t *) arg;
 
	for(int i = 0; i < LIMIT; i++)
	{
		if((errno = pthread_mutex_lock(&(params->mutex))) != 0)
		{
			WARNING("pthread_mutex_lock() failed\n");
			return NULL;
		}

		while(params->state != PONG)
		{
			if((errno = pthread_cond_wait(&(params->cond), &(params->mutex))) != 0)
			{
				WARNING("pthread_cond_wait() failed\n");
				return NULL;
			}
		}

		printf("pong!\n");
		params->state = PING;

		if((errno = pthread_cond_signal(&(params->cond))) != 0)
		{
			WARNING("pthread_cond_signal() failed\n");
			return NULL;
		}

		if((errno = pthread_mutex_unlock(&(params->mutex))) != 0)
		{
			WARNING("pthread_mutex_unlock() failed\n");
			return NULL;
		}
	}

	return NULL;
}