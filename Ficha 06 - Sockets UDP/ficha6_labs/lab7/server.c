/**
 * @file: server.c
 * @date: 2016-11-17
 * @author: autor
 */
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "debug.h"
#include "common.h"
#include "server_opt.h"


int main(int argc, char *argv[]){
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser (argc, argv, &args_info) != 0){
        exit(ERR_ARGS);
    }

    /*
     * Inserir codigo do servidor
     */

    if(args_info.port_arg < 1 || args_info.port_arg > USHRT_MAX)
    {
        ERROR(ERR_ARGS, "porto inválido. [1 - 65535]\n");
    }

    int udp_server_socket;
	if ((udp_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ERROR(31, "Can't create udp_server_socket (IPv4)");

	// UDP IPv4: bind a IPv4/porto 
	struct sockaddr_in udp_server_endpoint;
	memset(&udp_server_endpoint, 0, sizeof(struct sockaddr_in));
	udp_server_endpoint.sin_family = AF_INET;   //Para endereços IPv4
	udp_server_endpoint.sin_addr.s_addr = htonl(INADDR_ANY);  	// Todas as interfaces de rede
	udp_server_endpoint.sin_port = htons(args_info.port_arg);	// Server port

    if (bind(udp_server_socket, (struct sockaddr *) &udp_server_endpoint, sizeof(struct sockaddr_in)) == -1)
		ERROR(32, "Can't bind @udp_server_endpoint info");

    while(1)
    {
        socklen_t udp_client_endpoint_length = sizeof(struct sockaddr_in);
	    struct sockaddr_in udp_client_endpoint;
	    ssize_t udp_read_bytes, udp_sent_bytes;
        uint16_t number;

        printf("\n\tÁ espera de dados do cliente...\n");
        fflush(stdout);

        if ((udp_read_bytes = recvfrom(udp_server_socket, &number, sizeof(number), 0, (struct sockaddr *) &udp_client_endpoint, &udp_client_endpoint_length)) == -1)
		    ERROR(34, "Can't recvfrom client");

        printf("ok.  (%d bytes received)\n", (int)udp_read_bytes);

        number = ntohs(number);

        DEBUG("number: %hu\n", number);

        double result = sqrt(number);
        char buffer[MAX_MSG_SIZE];
        snprintf(buffer, MAX_MSG_SIZE, "%.2lf", result);

        DEBUG("str result: %s", buffer);

        printf("a enviar dados para o cliente... "); 
        fflush(stdout);
        if ((udp_sent_bytes = sendto(udp_server_socket, buffer, strlen(buffer), 0, 
        (struct sockaddr *) &udp_client_endpoint, udp_client_endpoint_length)) == -1)
            ERROR(35, "Can't send to client");
        printf("ok.  (%d bytes sent)\n", (int)udp_sent_bytes);
    }

    cmdline_parser_free(&args_info);

    return 0;
}
