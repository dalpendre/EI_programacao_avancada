/**
* @file main.c
* @brief Description
* @date 2015-10-24
* @author name of author
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#include "debug.h"
#include "memory.h"

int main(int argc, char *argv[])
{
	/* Disable warnings */
	(void)argc; (void)argv;

	/* Main code */
	DEBUG("Main is empty -- add code here");


	return 0;
}

