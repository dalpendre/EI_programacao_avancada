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

typedef struct 
{
	int valor;
	pthread_mutex_t mutex;
}thread_params_t;

void* task(void* arg);
int contador;

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	struct gengetopt_args_info args_info;
	if(cmdline_parser(argc, argv, &args_info))
	{
		ERROR(1, "Erro: execução do cmline_parser\n");
	}

	int num_threads = args_info.num_th_arg;
	int valor = args_info.valor_arg;
	
	pthread_t tids[num_threads];
	thread_params_t thread_params;
	
	thread_params.valor = valor;

	void *task(void *arg);

	if((errno = pthread_mutex_init(&thread_params.mutex, NULL)) != 0)
		ERROR(12, "pthread_mutex_init() failed\n");

	for(int i = 0; i < num_threads; i++)
	{
		if((errno = pthread_create(&tids[i], NULL, task, &thread_params)) != 0)
		{
			ERROR(10, "Erro no pthread_create()!\n");
		}
	}

	for(int i = 0; i < num_threads; i++)
	{
		if((errno = pthread_join(tids[i], NULL) != 0))
		{
			ERROR(11, "Erro no pthread_join()!\n");
		}
	}

	if((errno = pthread_mutex_destroy(&thread_params.mutex)) != 0)
		ERROR(13, "pthread_mutex_destroy() failed\n");
	
	printf("contador = %d\n", contador);

	cmdline_parser_free(&args_info);
	return 0;
}

void* task(void* arg)
{
	thread_params_t *params = (thread_params_t *) arg;	

	for(int i = 0; i < params->valor; i++)
	{
		//mutex lock
		if((errno = pthread_mutex_lock(&(params->mutex))) != 0)
		{
			WARNING("pthread_mutex_lock() failed\n");
			return NULL;
		}

		contador = contador + 1;
		
		//mutex unlock
		if((errno = pthread_mutex_unlock(&(params->mutex))) != 0)
		{
			WARNING("pthread_mutex_unlock() failed\n");
			return NULL;
		}

		sched_yield();	//Recolocar thread no fim da lista de threads a executar
	}

	return NULL;
}