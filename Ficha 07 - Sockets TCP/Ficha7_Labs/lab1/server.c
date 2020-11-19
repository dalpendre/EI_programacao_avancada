#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../debug/debug.h"
#include "../cmdline/server_cmdline.h"


int main(int argc, char *argv[]) 
{
	struct gengetopt_args_info args;

	// cmdline_parser: deve ser a primeira linha de código no main
	if( cmdline_parser(argc, argv, &args) )
		ERROR(99, "Erro: execução de cmdline_parser\n");
	



	
	// libertar recurso (cmdline_parser)
	cmdline_parser_free(&args);	

	exit(0);
}	
