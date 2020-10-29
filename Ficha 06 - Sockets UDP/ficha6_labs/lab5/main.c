#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#include "debug.h"
#include "memory.h"
#include "args.h"

int main(int argc, char *argv[]) {
    /* Receber porto a registar */
    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);

    /* Criar e registar socket UDP IPv4 */

    /* Registo local - bind */

    /* Liberta memória */
    cmdline_parser_free(&args);

    return 0;
}

/*
 * Perguntas:
 *  a)  O que sucede quando é indicado um porto entre 1 e 1023 (inclusive)?
 *  b)  O que sucede quando se tenta registar um porto que já está registado?
 *      Nota: é possível obter uma lista dos portos UDP registados no sistema
 * através do utilitário netstat, executado da seguinte forma: netstat -u -l
 */
