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

/*  protóptipos */
void *thread_1(void *arg);
void *thread_2(void *arg);

/* Estrutura a 'passar' às threads */
typedef struct 
{
	int contador;
	pthread_mutex_t mutex;
}thread_params_t;


/*  main  */
int main(int argc, char *argv[]) 
{
    pthread_t t1, t2;
    thread_params_t thread_params;

    (void)argc;(void)argv;

	/* Inicialização dos campos da estrutura thread_params: */
	/*		Mutex	*/
	if ((errno = pthread_mutex_init(&thread_params.mutex, NULL)) != 0)
		ERROR(C_ERRO_MUTEX_INIT, "pthread_mutex_init() failed!");
	/*		Contador	*/
	thread_params.contador = 0;	
	
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
			
	/* Mostra valor do campo contador */
	printf("Contador = %d\n", thread_params.contador);
			
	/* Destroi o mutex */
	if ((errno = pthread_mutex_destroy(&thread_params.mutex)) != 0)
		ERROR(C_ERRO_MUTEX_DESTROY, "pthread_mutex_destroy() failed!");			
			
    return 0;
}

/* Thread 1 */
void *thread_1(void *arg)
{
	thread_params_t *params = (thread_params_t *) arg;	   
	printf("Thread_1\n");	

	if((errno = pthread_mutex_lock(&params->mutex)) != 0)
	{
		WARNING("pthread_mutex_lock() failed\n");
		return NULL;
	}	
	
	usleep(100*(random() % 2));	/* Adormece entre 0 a 100 usecs */
	int cont = params->contador;
	sched_yield();
	usleep(100*(random() % 2));	/* Adormece entre 0 a 100 usecs */
	params->contador = cont + 2;
			
	if((errno = pthread_mutex_unlock(&params->mutex)) != 0)
	{
		WARNING("pthread_mutex_unlock() failed\n");
		return NULL;
	}	
	
    return NULL;
}


/* Thread 2 */
void *thread_2(void *arg)
{
	thread_params_t *params = (thread_params_t *) arg;	   
	printf("Thread_2\n");

	if((errno = pthread_mutex_lock(&params->mutex)) != 0)
	{
		WARNING("pthread_mutex_lock() failed\n");
		return NULL;
	}	
		
	usleep(100*(random() % 2));	/* Adormece entre 0 a 100 usecs */
	int cont = params->contador;
	sched_yield();
	usleep(100*(random() % 2));	/* Adormece entre 0 a 100 usecs */
	params->contador = cont + 4;
	  	   
	//usleep -> para execução durante (microsegundos)

	if((errno = pthread_mutex_unlock(&params->mutex)) != 0)
	{
		WARNING("pthread_mutex_unlock() failed\n");
		return NULL;
	}	
			
    return NULL;
}
