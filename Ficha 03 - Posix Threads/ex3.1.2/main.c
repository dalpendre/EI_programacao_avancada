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

	void *task(void *arg);

	for(int i = 0; i < num_threads; i++)
	{
		if((errno = pthread_create(&tids[i], NULL, task, &valor)) != 0)
			ERROR(10, "Erro no pthread_create()!\n");
	}

	for(int i = 0; i < num_threads; i++)
	{
		if((errno = pthread_join(tids[i], NULL) != 0))
		{
			ERROR(11, "Erro no pthread_join()!\n");
		}
	}
	
	printf("contador = %d\n", contador);

	cmdline_parser_free(&args_info);
	return 0;
}

void* task(void* arg)
{
	int *valor = (int *) arg;

	for(int i = 0; i < *valor; i++)
	{
		contador = contador + 1;
		
		//mutex unlock
		sched_yield();	//Recolocar thread no fim da lista de threads a executar
	}

	return NULL;
}