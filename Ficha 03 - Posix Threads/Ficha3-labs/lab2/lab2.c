#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "debug.h"

int main (int argc, char *argv[])
{	
	/* Silencia os warnings */
	(void)argc;
	(void)argv;

	printf("\n\tNome do programa: %s\n", argv[0]);

	pid_t pidPrograma = getpid();
	printf("\n\tPID do programa atual: %d\n", pidPrograma);

	//system("ps -efL | grep /bin/bash$ | head -n 1 | tr -s ' ' '#' | cut -f 6 -d '#'");

	exit(0);
}
