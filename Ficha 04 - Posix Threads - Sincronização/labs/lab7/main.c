#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "debug.h"

#define C_ERRO_PTHREAD_CREATE           1
#define C_ERRO_PTHREAD_JOIN             2
#define C_ERRO_MUTEX_INIT               3
#define C_ERRO_MUTEX_DESTROY            4
#define C_ERRO_CONDITION_INIT           5
#define C_ERRO_CONDITION_DESTROY        6
/*
Nota 1: neste exemplo é utilizada a mesma função para todas as threads;
Nota 2: é utilizado um identificador para distinguir o código que é específico a cada thread.
*/

#define MAX_THREADS				        4

/*  protóptipos */
void *task(void *arg);


/* Estrutura a 'passar' às threads */
typedef struct 
{	
	int id; 				/* identificador da thread */
    pthread_mutex_t *mutex; /* ponteiro para um mutex a partilhar por todas as threads */
    pthread_cond_t *cond; 	/* ponteiro para uma variável de condição a partilhar por todas as threads */
}thread_params_t;


/*  main  */
int main(int argc, char *argv[]) 
{
    pthread_t tids[MAX_THREADS];
    thread_params_t thread_params[MAX_THREADS];
    pthread_mutex_t mutex;		/* mutex que vai ser 'partilhado' por todas as threads */
    pthread_cond_t cond;		/* variável de condição que vai ser 'partilhada' por todas as threads */
    
    (void)argc;(void)argv;

	/* Inicialização do mutex */
	if ((errno = pthread_mutex_init(&mutex, NULL)) != 0)
		ERROR(C_ERRO_MUTEX_INIT, "pthread_mutex_init() failed!");
		
    /* Inicialização da variável de condição */
	if ((errno = pthread_cond_init(&cond, NULL)) != 0)
		ERROR(C_ERRO_CONDITION_INIT, "pthread_cond_init() failed!");		
		
	/* Inicialização das estruturas - para cada thread*/
	for (int i = 0; i < MAX_THREADS; i++)
	{
		thread_params[i].id = i + 1;
		thread_params[i].mutex = &mutex; 
		thread_params[i].cond = &cond;
	}
	
	/* Criação das threads + passagem de parametro */
	for (int i = 0; i < MAX_THREADS; i++){
		if ((errno = pthread_create(&tids[i], NULL, task, &thread_params[i])) != 0)
			ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
	}

    /* Espera que todas as threads terminem */
	for (int i = 0; i < MAX_THREADS; i++){
		if ((errno = pthread_join(tids[i], NULL)) != 0)
			ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");	
	}

	/* Destroi o mutex */
	if ((errno = pthread_mutex_destroy(&mutex)) != 0)
		ERROR(C_ERRO_MUTEX_DESTROY, "pthread_mutex_destroy() failed!");			
			
	/* Destroi a variável de condição */
	if ((errno = pthread_cond_destroy(&cond)) != 0)
		ERROR(C_ERRO_CONDITION_DESTROY, "pthread_cond_destroy() failed!");
					
    return 0;
}



/* Todas as threads executam esta função */
void *task(void *arg)
{
	thread_params_t *params = (thread_params_t *) arg;
	
	printf("Thread %d\n", params->id);	

	if (params->id == 1){
		printf("Thread %d - sinalizará a variável de condição daqui a 5 segundos\n", params->id);
		sleep(5);
	}	
	
	/* Entra na secção crítica */
	if ((errno = pthread_mutex_lock(params->mutex)) != 0) {
		WARNING("pthread_mutex_lock() failed\n");
		return NULL;
	}

	printf("Thread %d - entrou na secção crítica\n", params->id);	

	/* a primeira thread sinaliza uma variável de condição, as restantes esperam nessa variável */
	if (params->id == 1)
	{		
		/* Notifica threads à espera na variável de condição */
		if ((errno = pthread_cond_signal(params->cond)) != 0){
			WARNING("pthread_cond_signal() failed");
			return NULL;
		}		
		printf("Thread %d - $ notificou variável de condição $\n", params->id);			
	}
	else
	{	
		printf("Thread %d - ## à espera na variável de condição ##\n", params->id);	
		
		/* Espera na variável de condição */
		if ((errno = pthread_cond_wait(params->cond, params->mutex)) != 0) {
			WARNING("pthread_cond_wait() failed");
			return NULL;
		}	

		//seccao critica!!!
	}
	
	/* Sai da secçao crítica */	
	if ((errno = pthread_mutex_unlock(params->mutex)) != 0) {
		WARNING("pthread_mutex_unlock() failed");
		return NULL;
	}	

	printf("Thread %d -  *** terminou *** \n", params->id);	
		
    return NULL;
}

