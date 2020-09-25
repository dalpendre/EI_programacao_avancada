#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"
#include "memory.h"

int main(void)
{
	pid_t pid;
	switch (pid = fork())
	{
		case -1:
			ERROR(1, "erro no fork() para crir filho 1\n");
			break;

		//Processo filho (filho 1) cria neto 1
		case 0:
			switch (pid = fork())
			{
				case -1:
					ERROR(1, "erro no fork() para criar neto 1\n");
					break;
				
				case 0:
					printf("eu sou o neto: PID=%d (PPID=%d)\n", getpid(), getppid());
					break;

				default:
					wait(NULL);
					printf("eu sou o filho 1: PID=%d (PPID=%d)\n", getpid(), getppid());
					break;
			}

			break;
		
		//Filho 2
		default:
			wait(NULL);
			switch (pid = fork())
			{
				case -1:
					ERROR(1, "erro no fork() para criar filho 2\n");
					break;
				
				case 0:
					printf("eu sou o filho 2: PID=%d (PPID=%d)\n", getpid(), getppid());
					break;

				default:
				wait(NULL);
					printf("eu sou o pai: PID=%d (PPID=%d)\n", getpid(), getppid());
					break;
			}

			break;
	}

	return 0;
}
