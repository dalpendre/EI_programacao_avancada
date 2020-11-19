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
#include <arpa/inet.h>

#include "debug.h"
#include "memory.h"
#include "args.h"

void show_addr_bytes(unsigned char* end, size_t size);

int main(int argc, char *argv[]) {
    /* Receber endereço IPv4 em formato texto */
    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);

    struct in_addr end_ipv4;

    /* Converter e mostrar endereço em formato: byte.byte.byte.byte */
    switch(inet_pton(AF_INET, args.address_arg, &end_ipv4))
    {
        case -1:
            ERROR(1, "af inválida\n");
            break;

        case 0:
            ERROR(1, "Endereço ipv4 %s inválido\n", args.address_arg);
            break;

        default:
            show_addr_bytes((unsigned char*) &end_ipv4, sizeof(struct in_addr));
            break;
    }

    /* Libertar memória alocada pelo gengetopt */
    cmdline_parser_free(&args);
    return 0;
}

void show_addr_bytes(unsigned char* end, size_t size)
{
    printf("0x");
    for(int i = 0; i < size; ++i)
    {
        printf("%02x\n", end[i]);
    }
    printf("\n");
}