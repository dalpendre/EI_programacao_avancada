#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"
#include "memory.h"

int main(int argc, char *argv[])
{
	//Pasta /home/dalpendre
	pid_t f1 = fork();

	if(f1 == 0)
	{
		int result = system("ps -l");

		if(result < 0)
			ERROR(1, "Chamada à unção system falhou.\n");
		else
		{
			printf("Chamada a função system() retornou: %d\n", result);
		}
	}

	return 0;
}
