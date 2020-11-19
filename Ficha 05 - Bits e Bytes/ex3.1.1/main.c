#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "args.h"

#include "debug.h"
#include "memory.h"

int bin_to_decimal(const char *bin_s_ptr);

int bin_to_decimal(const char *bin_s_ptr)
{
	int i, digit = 0, max = strlen(bin_s_ptr)-1, exponent = strlen(bin_s_ptr)-1, 
	value = 0, decimal_to_sum = 0, decimal_num = 0;

	for(i = 0; i <= max; i++)
	{	
		digit = bin_s_ptr[i] - '0';

		if(digit == 1)
		{
			//shift to determine the power
			
		}

		printf("%d\n", exponent);
		exponent--;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	(void)argc; 
	(void)argv;

	struct gengetopt_args_info args;

	if(cmdline_parser(argc, argv, &args))
		ERROR(1, "Erro: execução de cmdline_parser\n");

	/*for(int i= 0; i < strlen(args.string_arg); i++)
	{
		if(strcmp(args.string_arg[i], "1") != 0 || strcmp(args.string_arg[i], "0") != 0)
		{
			ERROR(1, "\n\tinvalid binary string\n");
			exit(0);
		}
	}*/

	bin_to_decimal(args.string_arg);

	cmdline_parser_free(&args);

	return 0;
}

