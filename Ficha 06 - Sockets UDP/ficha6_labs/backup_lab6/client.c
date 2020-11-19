#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "memory.h"
#include "debug.h"
#include "common.h"
#include "client_opt.h"

int main(int argc, char *argv[]) 
{
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser(argc, argv, &args_info) != 0) {
        exit(ERR_ARGS);
    }

    if(args_info.port_arg < 1 || args_info.port_arg > USHRT_MAX)
    {
        ERROR(ERR_ARGS, "porto inválido. [1 - 65535]");
    }
    
    /*Inserir codigo do cliente*/

    int udp_client_socket;	

    //Criar socket
	if ((udp_client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ERROR(21, "Can't create udp_client_socket (IPv4)");

    //Envio para o servidor
    ssize_t udp_read_bytes, udp_sent_bytes;

    //Fecha socket
	if (close(udp_client_socket) == -1)
		ERROR(23, "Can't close udp_client_socket (IPv4)");

    cmdline_parser_free(&args_info);

    return 0;
}
