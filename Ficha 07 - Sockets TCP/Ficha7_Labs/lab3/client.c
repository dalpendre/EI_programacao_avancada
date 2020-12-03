#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
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
    if (cmdline_parser (argc, argv, &args_info) != 0)
    {
	    exit(ERR_ARGS);
    }
    
    int tcp_client_socket;
	if ((tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ERROR(41, "Can't create tcp_client_socket (IPv4)");

    // TCP IPv4: connect ao IP/porto do servidor
	struct sockaddr_in tcp_server_endpoint;
	memset(&tcp_server_endpoint, 0, sizeof(struct sockaddr_in));
	tcp_server_endpoint.sin_family = AF_INET;
	switch (inet_pton(AF_INET, args_info.ip_arg, &tcp_server_endpoint.sin_addr)) 
    {
		case 0:
			fprintf(stderr, "[%s@%d] ERROR - Cannot convert IP address (IPv4): Invalid Network Address\n",
				__FILE__, __LINE__);
			exit(22);
		case -1:
			ERROR(22, "Cannot convert IP address (IPv4)");
	}
	tcp_server_endpoint.sin_port = htons(args_info.port_arg);	// Server port

    printf("a ligar ao servidor... "); 
	fflush(stdout);
	if (connect(tcp_client_socket, (struct sockaddr *) &tcp_server_endpoint, 
	sizeof(struct sockaddr_in)) == -1)
		ERROR(43, "Can't connect @tcp_server_endpoint");
	printf("ok. \n");

	srand(time(NULL));
	uint32_t number = 1 + (rand() % 9999);

	printf("numero gerado: %u\n", number);

	char str_numero[MAX_STR_NUM];
	snprintf(str_numero, MAX_STR_NUM, "%u", number);

	printf("string enviada: %s\n", str_numero);

	ssize_t tcp_read_bytes, tcp_sent_bytes;

	printf("a enviar dados para o servidor... "); 
	fflush(stdout);
	if((tcp_sent_bytes = send(tcp_client_socket, str_numero, strlen(str_numero) + 1, 0)) == -1)
		ERROR(46, "Can't send to server");
	printf("ok.  (%d bytes enviados)\n", (int)tcp_sent_bytes);

	printf("à espera de dados do servidor... "); 
	fflush(stdout);
	if ((tcp_read_bytes = recv(tcp_client_socket, &number, sizeof(number), 0)) == -1)
		ERROR(47, "Can't recv from server");
	printf("ok.  (%d bytes recebidos)\n", (int)tcp_read_bytes);	

	number = ntohl(number);
	printf("numero recebido: %u\n", number);

    if (close(tcp_client_socket) == -1)
		ERROR(45, "Can't close tcp_client_socket (IPv4)");
	printf("ligação fechada. ok. \n");

    cmdline_parser_free(&args_info);

    return 0;
}
