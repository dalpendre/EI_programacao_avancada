#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../debug/debug.h"
#include "../cmdline/client_cmdline.h"
#include <time.h>
#include "common.h"

int main(int argc, char *argv[]) 
{
	struct gengetopt_args_info args;

	// cmdline_parser: deve ser a primeira linha de código no main
	if( cmdline_parser(argc, argv, &args) )
		ERROR(99, "Erro: execução de cmdline_parser\n");
		
	pid_t pid;
		
	// processo pai cria N processos
	for(int i = 0; i < 5; i++)
	{
		pid = fork();
		if (pid == 0) 
		{			
			cliente(args.ip_arg, args.porto_arg);
			exit(0);	// Termina processo filho (para este não criar novos processos)
		} 
		else if (pid > 0) 
		{	
		}
		else
		{
			ERROR(2, "Erro na execução do fork()");
		}
	}

	for(int i = 0; i < 5; i++)
	{
		wait(NULL);
	}

	printf("Pai terminou");

	// libertar recurso (cmdline_parser)
	cmdline_parser_free(&args);	
		
	exit(0);
}	
