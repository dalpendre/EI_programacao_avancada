#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "debug.h"

#define MAX 100

void trata_sinal(int signal);

void trata_sinal(int signal)
{
	int aux;
	/* Copia da variavel global errno */
	aux = errno;

	if(signal == SIGUSR1)
	{
		printf("Recebi o sinal SIGUSR1 (%d)\n", signal);
	}

	/* Restaura valor da variavel global errno */
	errno = aux;
}


int main(int argc, char *argv[])
{
	char buf[MAX];
	struct sigaction act;
	ssize_t n;

	/*Silencia warnings...*/
	(void) argc; (void) argv;

	/* Definir a rotina de resposta a sinais */
	act.sa_handler = trata_sinal;

	/* mascara sem sinais -- nao bloqueia os sinais */
	sigemptyset(&act.sa_mask);

	act.sa_flags = SA_RESTART; /*recupera chamadas bloqueantes*/

	/* Captura do sinal SIGUSR1 */
	if(sigaction(SIGUSR1, &act, NULL) < 0)
	{
		ERROR(1, "sigaction - SIGUSR1");
	}

	printf("O processo esta pronto para receber sinais [SIGUSR1]...\n");
	printf("PID do processo: %d\n", getpid() );
	printf("Introduza informacao atraves do teclado:\n");

	n = read(0, buf, MAX);
	if (n < 0)
		ERROR(2, "Erro de entrada.");
	buf[n]='\0';

	printf("Foi lido do teclado: %s\n", buf);

	exit(0);
}
