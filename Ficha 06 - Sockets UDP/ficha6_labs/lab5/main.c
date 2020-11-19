#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/socket.h>

#include <assert.h>

#include "debug.h"
#include "memory.h"
#include "args.h"

int main(int argc, char *argv[]) {
    /* Receber porto a registar */
    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);

    /* Criar e registar socket UDP IPv4 */
    int socket_udp_v4 = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_udp_v4 == -1)
    {
        ERROR(1, "socket v4 failed\n");
    }

    /* Registo local - bind */
    struct sockaddr_in serv_addr;   //address do socket
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(args.port_arg);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(socket_udp_v4, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_in)) == -1)
    {
        ERROR(1, "bind() failed to port %hd", args.port_arg);
    }

    printf("Servidor à escuta no porto %hd\n", args.port_arg);

    while(1){}  //Para não acabar programa

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
