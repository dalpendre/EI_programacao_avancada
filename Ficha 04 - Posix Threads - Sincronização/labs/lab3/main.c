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

/*  protóptipos */
void *thread_1(void *arg);
void *thread_2(void *arg);

/* Estrutura a 'passar' às threads */
typedef struct 
{	
    pthread_mutex_t mutex;
	pthread_cond_t cond;
}thread_params_t;

/*  main  */
int main(int argc, char *argv[]) 
{
    pthread_t t1, t2;
    thread_params_t thread_params;

    (void)argc;(void)argv;

	/* Inicialização do mutex */
	if ((errno = pthread_mutex_init(&thread_params.mutex, NULL)) != 0)
		ERROR(C_ERRO_MUTEX_INIT, "pthread_mutex_init() failed!");

	if((errno = pthread_cond_init(&thread_params.cond, NULL)) != 0)
	{
		ERROR(14, "pthread_cond_init() failed!\n");
	}

    /* Cria thread_1 */
	if ((errno = pthread_create(&t1, NULL, thread_1, &thread_params)) != 0)
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
	
    /* Cria thread_2 */
	if ((errno = pthread_create(&t2, NULL, thread_2, &thread_params)) != 0)
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");

    /* Espera que as duas (2) threads terminem */
	if ((errno = pthread_join(t1, NULL)) != 0)
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");	
	if ((errno = pthread_join(t2, NULL)) != 0)
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
						
	/* Destroi o mutex */
	if ((errno = pthread_mutex_destroy(&thread_params.mutex)) != 0)
		ERROR(C_ERRO_MUTEX_DESTROY, "pthread_mutex_destroy() failed!");			
			
	if((errno = pthread_cond_destroy(&thread_params.cond)) != 0)
	{
		ERROR(15, "pthread_cond_init() failed!\n");
	}
	
    return 0;
}


/* Thread 1 */
void *thread_1(void *arg)
{
	(void)arg;  
	
	printf("Thread_1\n");	
		
    return NULL;
}


/* Thread 2 */
void *thread_2(void *arg)
{
	(void)arg;
   
	printf("Thread_2\n");
	   
    return NULL;
}
