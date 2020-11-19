/**
 * @file: client.c
 * @date: 2016-11-17
 * @author: autor
 */
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "memory.h"
#include "debug.h"
#include "common.h"
#include "client_opt.h"

int main(int argc, char *argv[])
{
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if(cmdline_parser(argc, argv, &args_info) != 0){
	    exit(ERR_ARGS);
    }

    /*
     * Inserir codigo do cliente
     */

    if(args_info.port_arg < 1 || args_info.port_arg > USHRT_MAX)
    {
        ERROR(ERR_ARGS, "porto inválido. [1 - 65535]\n");
    }

    int udp_client_socket;	
	if ((udp_client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ERROR(21, "Can't create udp_client_socket (IPv4)");

    srand(time(NULL));
    uint16_t number = rand() % 100 + 1; //0 to 99+1 (0 to 100)

    #ifdef SHOW_DEBUG
    DEBUG("number: %hu", number);
    #endif

    socklen_t udp_server_endpoint_length = sizeof(struct sockaddr_in);	
	struct sockaddr_in udp_server_endpoint;
	memset(&udp_server_endpoint, 0, sizeof(struct sockaddr_in));
	udp_server_endpoint.sin_family = AF_INET;	
	switch (inet_pton(AF_INET, args_info.ip_arg, &udp_server_endpoint.sin_addr.s_addr)) 
    {
		case 0:
			fprintf(stderr, "[%s@%d] ERROR - Cannot convert IP address (IPv4): Invalid Network Address\n",
				__FILE__, __LINE__);
			exit(22);
		case -1:
			ERROR(22, "Cannot convert IP address (IPv4)");
	}
	udp_server_endpoint.sin_port = htons(args_info.port_arg);

    number = htons(number);

    //socklen_t udp_client_endpoint_length = sizeof(struct sockaddr_in);
	//struct sockaddr_in udp_client_endpoint;
	ssize_t udp_read_bytes, udp_sent_bytes;

    printf("a enviar dados para o servidor... "); 
    fflush(stdout);
	if ((udp_sent_bytes = sendto(udp_client_socket, &number, sizeof(number), 0, (struct sockaddr *) &udp_server_endpoint, udp_server_endpoint_length)) == -1)
		ERROR(24, "Can't sendto server");
	printf("ok.  (%d bytes sent)\n", (int)udp_sent_bytes);

    char buffer[MAX_MSG_SIZE];

    printf("à espera de dados do servidor... "); 
    fflush(stdout);
	if((udp_read_bytes = recvfrom(udp_client_socket, buffer, sizeof(buffer), 0, (struct sockaddr *) &udp_server_endpoint, &udp_server_endpoint_length)) == -1)
		ERROR(25, "Can't recvfrom server");
	printf("ok.  (%d bytes received)\n", (int)udp_read_bytes);	

    buffer[udp_read_bytes] = '\0';

    if (close(udp_client_socket) == -1)
		ERROR(33, "Can't close udp_server_socket (IPv4)");

    cmdline_parser_free(&args_info);

    return 0;
}
