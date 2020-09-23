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
	
	if(cmdline_parser(argc, argv, &args_info) != 0)
	{
		exit(1);
	}

	pid_t pids[args_info.num_procs_arg];

	for(int i = 0; i < args_info.num_procs_arg; i++)
	{
		pids[i] = fork();

		if(pids[i] == 0) //Processos filhos (criados)
		{	
			printf("Processo #%i (PID=%d)\n", i+1, getpid());
			exit(0);
		}
	}

	return 0;
}
