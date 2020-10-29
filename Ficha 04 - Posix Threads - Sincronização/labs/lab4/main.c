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

int main(int argc, char *argv[]) 
{
    pthread_t t1, t2;
    thread_params_t thread_params;

    (void)argc;(void)argv;

	/* Inicialização do mutex */
	if ((errno = pthread_mutex_init(&thread_params.mutex, NULL)) != 0)
		ERROR(C_ERRO_MUTEX_INIT, "pthread_mutex_init() failed!");
		
    /* Inicialização da variável de condição */
	if ((errno = pthread_cond_init(&thread_params.cond, NULL)) != 0)
		ERROR(C_ERRO_CONDITION_INIT, "pthread_cond_init() failed!");		

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
			
	/* Destroi a variável de condição */
	if ((errno = pthread_cond_destroy(&thread_params.cond)) != 0)
		ERROR(C_ERRO_CONDITION_DESTROY, "pthread_cond_destroy() failed!");
					
    return 0;
}

/* Thread 1 */
void *thread_1(void *arg)
{
	thread_params_t *params = (thread_params_t *) arg;
	
	printf("Thread_1\n");	
	
	/* Entra na secção crítica */
	if ((errno = pthread_mutex_lock(&(params->mutex))) != 0) {
		WARNING("pthread_mutex_lock() failed\n");
		return NULL;
	}

	printf("Thread_1 - entrou na secção crítica\n");	
	printf("Thread_1 - à espera na variável de condição\n");	

	/* Espera na variável de condição */
	if ((errno = pthread_cond_wait(&(params->cond), &(params->mutex))) != 0) 
	{
		WARNING("pthread_cond_wait() failed");
		return NULL;
	}

	printf("Thread_1 - continua execução da secção crítica\n");	
	
	/* Sai da secçao crítica */	
	if ((errno = pthread_mutex_unlock(&(params->mutex))) != 0) {
		WARNING("pthread_mutex_unlock() failed");
		return NULL;
	}	

	printf("Thread_1 - saiu da secção crítica\n");	
		
    return NULL;
}

/* Thread 2 */
void *thread_2(void *arg)
{
	thread_params_t *params = (thread_params_t *) arg;
	
	printf("Thread_2\n");	
	
	/* Entra na secção crítica */
	if ((errno = pthread_mutex_lock(&(params->mutex))) != 0) {
		WARNING("pthread_mutex_lock() failed\n");
		return NULL;
	}

	printf("Thread_2 - entrou na secção crítica\n");	
	printf("Thread_2 - à espera na variável de condição\n");	

	/* Espera na variável de condição */
	if ((errno = pthread_cond_wait(&(params->cond), &(params->mutex))) != 0) {
		WARNING("pthread_cond_wait() failed");
		return NULL;
	}

	printf("Thread_2 - continua execução da secção crítica\n");	
	
	/* Sai da secçao crítica */	
	if ((errno = pthread_mutex_unlock(&(params->mutex))) != 0) {
		WARNING("pthread_mutex_unlock() failed");
		return NULL;
	}	

	printf("Thread_2 - saiu da secção crítica\n");	
		
    return NULL;
}
