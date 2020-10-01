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
	(void)argc;

	if(argc != 3)
	{
		ERROR(1, "Number of arguments must be 3 ( ./ContaFicheiros /home/dalpendre/ /usr/include/ )\n");
		exit(0);
	}

	pid_t f1 = fork();

	if(f1 == -1)
	{
		ERROR(2, "Error creating f1 for folder /home/dalpendre\n");
		exit(0);
	}

	//ls | wc -l to return number of files in directory

	if(f1 == 0)
	{
		execvp("ls", "ls", argv[1], NULL);
		execlp("ls", "ls", "|", "wc", "-l", argv[1], NULL);	
		printf("\n\n");
		exit(0);
	}

	pid_t f2 = fork();

	if(f2 == -1)
	{
		ERROR(2, "Error creating f2 for folder /usr/include/\n");
		exit(0);
	}

	if(f2 == 0)
	{
		wait(NULL);
		execlp("ls", "ls", argv[2], NULL);
		exit(0);
	}

	return 0;
}
