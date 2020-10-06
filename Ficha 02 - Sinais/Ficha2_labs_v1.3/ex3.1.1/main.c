#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"
#include "memory.h"
#include "args.h"

#define MAX 100

pid_t pid;
struct gengetopt_args_info args_info;

void trata_sinal_info(int signal, siginfo_t *siginfo, void *context);

// zona das funções
void trata_sinal_info(int signal, siginfo_t *siginfo, void *context) 
{
	(void)context;
	/* Cópia da variável global errno */
	int aux = errno;
	char *line = NULL;
	size_t linesize = 0;

	if(signal == SIGUSR1 && siginfo->si_pid == pid)
	{
		FILE *fptr = NULL;

		if((fptr = fopen(args_info.file_arg, "r")) == NULL)
			ERROR(5, "fopen() - não foi possível abrir o ficheiro\n");

		getline(&line, &linesize, fptr);

		printf("linha lida: %s\n", line);

		if(fclose(fptr) != 0)
			ERROR(6, "fclose() - não foi possível fechar o ficheiro\n");
	}
	/* Restaura valor da variável global errno */
	errno = aux;
}

int main(int argc, char *argv[])
{	
	(void) argc; (void) argv;

	char c;
	
	if(cmdline_parser(argc, argv, &args_info))
	{
		ERROR(1, "Erro: execução de cmlin_parser\n");
	}

	if(argc != 3)
	{
		ERROR(1, "Número errado de argumentos\n");
	}
	
	struct sigaction act_info;
		
	act_info.sa_sigaction = trata_sinal_info;
	sigemptyset(&act_info.sa_mask);
	act_info.sa_flags = 0;           	
	act_info.sa_flags |= SA_SIGINFO; 	
	act_info.sa_flags |= SA_RESTART;

	if(sigaction(SIGUSR1, &act_info, NULL) < 0)
	{
		ERROR(1, "sigaction (sa_sigaction)\n");
	}

	pid = fork();

	if(pid == -1)
	{
		ERROR(1, "Erro a criar filho\n");
	}
	else if (pid == 0) 
	{	
		while(1)
		{
			kill(getppid(), SIGUSR1);
			sleep(5);
		}

		exit(0);
	}
	else
	{
		while(1)
		{
			pause();
		}
		wait(NULL);
	}

	cmdline_parser_free(&args_info);

	//Daqui pra baixo resolução feita por mim
	/*pid_t f1 = fork();

	if(f1 == 0)
	{
		//Send signal here
		sendSignals();
	}

	FILE *fptr = NULL;
	fptr = fopen(args_info.file_arg, "r");

	if(!fptr)
	{
		ERROR(2, "File open error\n");
	}

	//Read file first line
	c = fgetc(fptr);
	while(c != EOF)
	{
		printf("%c", c);
		c = fgetc(fptr);		
	}
	
	fclose(fptr);

	exit(0);*/
}

/*int sendSignals()
{
	char buf[MAX];
	struct sigaction act;
	ssize_t n;

	/* Definir a rotina de resposta a sinais */
	//act.sa_sigaction = trata_sinal;

	/* mascara sem sinais -- nao bloqueia os sinais */
	//sigemptyset(&act.sa_mask);

	//every 5 seconds send signal to parent
//}