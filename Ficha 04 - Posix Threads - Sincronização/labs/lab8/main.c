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

#define MAX 		5 		/* Capacidade do buffer */
#define LIMITE 		20 		/* Total de elementos a produzir */

typedef struct 
{
    int buffer[MAX];
    int index_leitura;
    int index_escrita;
    int total;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} thread_params_t;

/* protótipos */
void *produtor(void *arg);
void *consumidor(void *arg);

int main(int argc, char *argv[]) 
{
    pthread_t t1, t2;
    thread_params_t thread_params;

    (void)argc;(void)argv;

    /* Inicia o mutex */
	if ((errno = pthread_mutex_init(&thread_params.mutex, NULL)) != 0)
		ERROR(C_ERRO_MUTEX_INIT, "pthread_mutex_init() failed!");

    /* Inicia variavel de condicao */
	if ((errno = pthread_cond_init(&thread_params.cond, NULL)) != 0)
		ERROR(C_ERRO_CONDITION_INIT, "pthread_cond_init() failed!");

    /* Inicia os restantes parametros a passar 'as threads */
    memset(thread_params.buffer, 0, sizeof(thread_params.buffer));
    thread_params.total = 0;
    thread_params.index_escrita = 0;
    thread_params.index_leitura = 0;

    /* Cria thread para executar o consumidor */
	if ((errno = pthread_create(&t1, NULL, consumidor, &thread_params)) != 0)
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
	
	/* Cria thread para executar o produtor */
	if ((errno = pthread_create(&t2, NULL, produtor, &thread_params)) != 0)
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");

    /* Espera que todas as threads terminem */
	if ((errno = pthread_join(t1, NULL)) != 0)
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
	
	if ((errno = pthread_join(t2, NULL)) != 0)
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");

	/* Destroi o mutex */
	if ((errno = pthread_mutex_destroy(&thread_params.mutex)) != 0)
		ERROR(C_ERRO_MUTEX_DESTROY, "pthread_mutex_destroy() failed!");
	
	/* Destroi a condicao */
	if ((errno = pthread_cond_destroy(&thread_params.cond)) != 0)
		ERROR(C_ERRO_CONDITION_DESTROY, "pthread_cond_destroy() failed!");

    return 0;
}


/* produtor */
void *produtor(void *arg)
{
	thread_params_t *params = (thread_params_t *) arg;
    int i;

    for (i=0; i<LIMITE; i++) {
		if ((errno = pthread_mutex_lock(&(params->mutex))) != 0) {
			WARNING("pthread_mutex_lock() failed\n");
			return NULL;
		}

        /* Espera que o buffer tenha espaco disponivel */
        while (params->total == MAX)
			if ((errno = pthread_cond_wait(&(params->cond), &(params->mutex))) != 0) {
				WARNING("pthread_cond_wait() failed");
				return NULL;
			}

        /* Coloca um valor no buffer */
        params->buffer[params->index_escrita] = random() % 100 + 1;
        printf(">> %d\n", params->buffer[params->index_escrita]);
        params->index_escrita = (params->index_escrita + 1) % MAX;
        params->total++;

        /* Notifica consumidores 'a espera */
        if (params->total == 1)
			if ((errno = pthread_cond_signal(&(params->cond))) != 0) {
				WARNING("pthread_cond_signal() failed");
				return NULL;
			}

        /* Sai da seccao critica */	
		if ((errno = pthread_mutex_unlock(&(params->mutex))) != 0) {
			WARNING("pthread_mutex_unlock() failed");
			return NULL;
		}

        /* Adormece entre 0 a 4 segundos */
        sleep(random() % 5);
    }
    return NULL;
}



/* consumidor */
void *consumidor(void *arg) 
{
	thread_params_t *params = (thread_params_t *) arg;
    int i;

    for (i=0; i<LIMITE; i++) {
		if ((errno = pthread_mutex_lock(&(params->mutex))) != 0) {
			WARNING("pthread_mutex_lock() failed\n");
			return NULL;
		}

        /* Espera que o buffer tenha dados */
        while (params->total == 0)
			if ((errno = pthread_cond_wait(&(params->cond), &(params->mutex))) != 0) {
				WARNING("pthread_cond_wait() failed");
				return NULL;
			}

        /* Retira um valor no buffer */
        printf("       %d >>\n", params->buffer[params->index_leitura]);
        params->index_leitura = (params->index_leitura + 1) % MAX;
        params->total--;

        /* Notifica produtores 'a espera */
        if (params->total == MAX-1)
			if ((errno = pthread_cond_signal(&(params->cond))) != 0) {
				WARNING("pthread_cond_signal() failed");
				return NULL;
			}

        /* Sai da seccao critica */	
		if ((errno = pthread_mutex_unlock(&(params->mutex))) != 0) {
			WARNING("pthread_mutex_unlock() failed");
			return NULL;
		}

        /* Adormece entre 0 a 4 segundos */
        sleep(random() % 5);
    }
	
    return NULL;
}
