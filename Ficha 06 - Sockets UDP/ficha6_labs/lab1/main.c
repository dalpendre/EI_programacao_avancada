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
#include <assert.h>

#include "debug.h"
#include "memory.h"
#include "args.h"

int main(int argc, char *argv[]) {
    /* Receber endereço IPv4 em formato texto */
    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);

    /* Converter e mostrar endereço em formato: byte.byte.byte.byte */

    /* Libertar memória alocada pelo gengetopt */
    cmdline_parser_free(&args);
    return 0;
}
