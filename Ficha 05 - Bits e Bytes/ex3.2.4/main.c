/**
* @file main.c
* @brief Description
* @date 2018-1-1
* @author name of author
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"
#include "memory.h"

int count_ones(int input);

int count_ones(int input)
{
	
}

int main(int argc, char *argv[])
{
	(void)argc; (void)argv;

	count_ones(0x512A);

	return 0;
}

