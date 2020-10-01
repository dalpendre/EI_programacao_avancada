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
#define MAX 5

void *fatorial(void *arg);

struct ThreadParams 
{
	unsigned long *ptrValor;
	unsigned long *ptrResultado;
};


int main(int argc, char *argv[]) 
{
	struct timeval tIni, tEnd;
	int i;
	pthread_t tids[MAX];
	unsigned long valores[MAX];
	unsigned long resultados[MAX];
	struct ThreadParams threadParams[MAX];
	
	(void)argc;(void)argv;
	
	// inicializar números para cálculo do fatorial (de 1 a 5)
	// "configurar" os parâmetros a passar às threads
	for (i = 0; i < MAX; i++){
		valores[i] = i + 1;		
		// para cada thread passa-se apenas a posição a calcular
		threadParams[i].ptrValor = &valores[i];
		threadParams[i].ptrResultado = &resultados[i];
	}
		
	// inicia contagem de tempo
	printf("A efetuar cálculos...\n");
    gettimeofday(&tIni, NULL);
	
	// criar as threads para cálculo e passar "o(s) parâmetro(s)"
	for (i = 0; i < MAX; i++) {		
		if ((errno = pthread_create(&tids[i], NULL, fatorial, &threadParams[i])) != 0) {
			ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
		}
	}
    
	// esperar que todas as threads terminem para mostrar resultados
	for (i = 0; i < MAX; i++) {
		if ((errno = pthread_join(tids[i], NULL)) != 0) {
			ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!\n");
		}
	}

	// termina contagem de tempo
    gettimeofday(&tEnd, NULL);

	// mostrar resultado da esecução das threads
    printf("Tempo: %d segundos\n", (int)(tEnd.tv_sec - tIni.tv_sec));    
	printf("Resultados:\n");	
	for (i = 0; i < MAX; i++) {
		printf("\t%lu!: %lu\n", valores[i], resultados[i]);
	}	

	exit(0);
}


void *fatorial(void *arg) 
{
	// cast para o tipo de dados original
	struct ThreadParams *params = (struct ThreadParams *) arg;
	
	// obter valor para cálculo do fatorial
	unsigned long valor = *params->ptrValor;
	
	// cálcular fatorial
	unsigned long aux = valor;
	while (--valor > 1) {
		aux *= valor;
	}
	
	// guardar valor calculado no vetor de resultados
	*params->ptrResultado = aux;
	
	//esperar um pouco (apenas para pergunta do próximo Lab)
	sleep(*params->ptrValor);
	
	return NULL;
}
