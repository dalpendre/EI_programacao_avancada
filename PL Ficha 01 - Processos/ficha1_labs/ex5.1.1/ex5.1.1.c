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

int main(int argc, char *argv[])
{	
	struct gengetopt_args_info args_info;
	
	if(cmdline_parser(argc, argv, &args_info))
	{
		ERROR(1, "Erro: execução de cmlin_parser\n");
	}

	if(args_info.num_procs_arg < 1)
	{
		ERROR(1, "num_procs tem que ser inteiro positivo!\n");
	}

	pid_t pid;
	for(int i = 0; i < args_info.num_procs_arg; i++)
	{
		pid = fork();

		if(pid == -1) //Processos filhos (criados)
		{
			ERROR(2, "erro no fork()\n");
		}
		else if(pid == 0)
		{
			printf("Processo #%d (PID=%d)\n", i+1, getpid());
			exit(0);
		}
	}

	return 0;
}
