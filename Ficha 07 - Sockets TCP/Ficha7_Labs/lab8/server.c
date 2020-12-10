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
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>

#include "../debug/debug.h"
#include "../cmdline/server_cmdline.h"
#include "common.h"


int main(int argc, char *argv[]){
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser (argc, argv, &args) != 0){
        exit(ERR_ARGS);
    }

    /*
     * Inserir codigo do servidor
     */
    // TCP IPv4: cria socket
	int tcp_server_socket;
	if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ERROR(51, "Can't create tcp_server_socket (IPv4)");

	// TCP IPv4: bind a IPv4/porto 	
	struct sockaddr_in tcp_server_endpoint;
	memset(&tcp_server_endpoint, 0, sizeof(struct sockaddr_in));  	
	tcp_server_endpoint.sin_family = AF_INET;
	tcp_server_endpoint.sin_addr.s_addr = htonl(INADDR_ANY); 		// Todas as interfaces de rede
	tcp_server_endpoint.sin_port = htons(args.porto_arg);		// Server port
	if (bind(tcp_server_socket, (struct sockaddr *) &tcp_server_endpoint, sizeof(struct sockaddr_in)) == -1)
		ERROR(52, "Can't bind @tcp_server_endpoint");

	// TCP IPv4: "listen" por clientes
	int tcp_max_simultaneous_clients = 1;			
    if (listen(tcp_server_socket, tcp_max_simultaneous_clients)  == -1)
		ERROR(53, "Can't listen for %d clients", tcp_max_simultaneous_clients);

	// TCP IPv4: "accept" 1 cliente (bloqueante)
	char tcp_client_string_ip[20];
	struct sockaddr_in tcp_client_endpoint;
	socklen_t tcp_client_endpoint_length = sizeof(struct sockaddr_in);
	int tcp_client_socket;
	
	while(1){
		printf("à espera da ligação do cliente... "); fflush(stdout);
		if ((tcp_client_socket = accept(tcp_server_socket, (struct sockaddr *) &tcp_client_endpoint, &tcp_client_endpoint_length)) == -1)
			ERROR(54, "Can't accept client");
		printf("ok. \n");			
		printf("cliente: %s@%d\n", inet_ntop(AF_INET, &tcp_client_endpoint.sin_addr, tcp_client_string_ip, sizeof(tcp_client_string_ip)), htons(tcp_client_endpoint.sin_port));


		// aqui... a comunicação com o cliente	
		// TCP IPv4: variáveis auxiliares para send() / recv()
		ssize_t tcp_read_bytes, tcp_sent_bytes;
		uint8_t resposta;

		// TCP IPv4: "recv" do cliente (bloqueante)
		printf("à espera de dados do cliente... "); fflush(stdout);
		if ((tcp_read_bytes = recv(tcp_client_socket, &resposta, sizeof(resposta), 0)) == -1)
			ERROR(57, "Can't recv from client");
		printf("ok.  (%d bytes sent)\n", (int)tcp_read_bytes);	

		printf("resposta: %d\n", resposta);	

		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);

  		//printf("Data/hora: %d-%02d-%02d_%02d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  		char string[64];
		if (resposta == 0){
			sprintf(string, "%d-%02d-%02d_%02d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 
			//printf("%s\n", string);
		}
		else if (resposta == 1){
			sprintf(string, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday); 
		}
		else if (resposta == 2){
			sprintf(string, "%02d-%02d-%02d", tm.tm_hour, tm.tm_min, tm.tm_sec); 
		}
		else{
			ERROR(21, "Tem de ser um numero (0, 1 ou 2)");
		}

		sleep(3);

		// TCP IPv4: "send" para o cliente
		printf("a enviar dados para o cliente... \n"); fflush(stdout);
		if ((tcp_sent_bytes = send(tcp_client_socket, &string, sizeof(string), 0)) == -1)
			ERROR(58, "Can't send to client");
		printf("ok.  (%d bytes received)\n", (int)tcp_sent_bytes);

		// TCP IPv4: fecha socket (client)
		if (close(tcp_client_socket) == -1)
			ERROR(55, "Can't close tcp_client_socket (IPv4)");
	}
			
	// TCP IPv4: fecha socket (server)
	if (close(tcp_server_socket) == -1)
		ERROR(56, "Can't close tcp_server_socket (IPv4)");	
		printf("ligação fechada. ok. \n");



    cmdline_parser_free(&args);

    return 0;
}
