#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "debug.h"

void trata_sinal(int signal);

/* Flag para termino do ciclo principal do programa*/
int continua = 1;

/* Rotina de tratamento de sinais*/
void trata_sinal(int signal)
{
	int aux;
	/* Copia da variavel global errno */
	aux = errno;

	if (signal == SIGUSR1){
		printf("Recebi o sinal SIGUSR1 (%d)\n", signal);
	} else if (signal == SIGINT){
		continua=0;
		printf("Recebi o sinal SIGINT (%d)\n", signal);
	}

	/* Restaura valor da variavel global errno */
	errno = aux;
}

int main(int argc, char *argv[])
{
	struct sigaction act;

	/*Silencia warnings...*/
	(void) argc; (void) argv;

	/* Regista rotina de tratamento de sinais  */
	act.sa_handler = trata_sinal;

	/* Comportamento por omissao -- fidedigno */
	act.sa_flags = 0;

	/* Mascara sem sinais para nao os bloquear */
	sigemptyset(&act.sa_mask);

	/* Captura do sinal SIGUSR1 */
	if (sigaction(SIGUSR1, &act, NULL) < 0){
	  ERROR(1, "sigaction - SIGUSR1");
	}

	/* Captura do sinal SIGINT */
	if (sigaction(SIGINT, &act, NULL) < 0){
	  ERROR(2, "sigaction - SIGINT");
	}

	/* Informa utilizador do funcionamento do programa */
	printf("O programa esta pronto a receber os signals SIGINT e SIGUSR1\n");
	printf("PID do processo: %d\n", getpid() );

	while (continua){
	  /* ciclo principal */
	  pause(); /* Espera bloqueante */
	  printf("Pause interrompido\n");
	}

	exit(0);
}
