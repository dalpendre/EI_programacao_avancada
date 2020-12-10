#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../debug/debug.h"
#include "../cmdline/client_cmdline.h"
#include <time.h>
#include "common.h"

int main(int argc, char *argv[]) 
{
	struct gengetopt_args_info args;

	// cmdline_parser: deve ser a primeira linha de código no main
	if( cmdline_parser(argc, argv, &args) )
		ERROR(99, "Erro: execução de cmdline_parser\n");
		
	

	pid_t pid;
		
	// processo pai cria N processos
	for(int i = 0; i < 5; i++){
		pid = fork();
		if (pid == 0) {			// Processo filho 
			printf("Filho %d \n", i + 1);
			
			exit(0);			// Termina processo filho (para este não criar novos processos)
		} else if (pid > 0) {	// Processo pai
			int tcp_client_socket;
			if ((tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
				ERROR(41, "Can't create tcp_client_socket (IPv4)");

			// TCP IPv4: connect ao IP/porto do servidor
			struct sockaddr_in tcp_server_endpoint;
			memset(&tcp_server_endpoint, 0, sizeof(struct sockaddr_in));
			tcp_server_endpoint.sin_family = AF_INET;
			switch (inet_pton(AF_INET, args.ip_arg, &tcp_server_endpoint.sin_addr)) {
				case 0:
					fprintf(stderr, "[%s@%d] ERROR - Cannot convert IP address (IPv4): Invalid Network Address\n",
						__FILE__, __LINE__);
					exit(22);
				case -1:
					ERROR(22, "Cannot convert IP address (IPv4)");
			}
			tcp_server_endpoint.sin_port = htons(args.porto_arg);						//Server port

			printf("a ligar ao servidor... "); fflush(stdout);
			if (connect(tcp_client_socket, (struct sockaddr *) &tcp_server_endpoint, sizeof(struct sockaddr_in)) == -1)
				ERROR(43, "Can't connect @tcp_server_endpoint");
			printf("ok. \n");
			
			// TCP IPv4: informação sobre IP/porto do cliente (porto atribuído automaticamente)	
			struct sockaddr_in tcp_client_endpoint;
			socklen_t tcp_client_endpoint_length = sizeof(struct sockaddr_in);
			char tcp_client_string_ip[20];	
			if (getsockname(tcp_client_socket, (struct sockaddr *)&tcp_client_endpoint, &tcp_client_endpoint_length) == -1)
				ERROR(44, "Can't connect @tcp_server_endpoint");
			printf("cliente: %s@%d\n", inet_ntop(AF_INET, &tcp_client_endpoint.sin_addr, tcp_client_string_ip, sizeof(tcp_client_string_ip)), htons(tcp_client_endpoint.sin_port));

			// TCP IPv4: variáveis auxiliares para send() / recv()
		    ssize_t tcp_read_bytes, tcp_sent_bytes;
		    uint8_t resposta = 0;

		    // TCP IPv4: "send" para o servidor
		    printf("a enviar dados para o servidor... "); fflush(stdout);
		    if ((tcp_sent_bytes = send(tcp_client_socket, &resposta, sizeof(resposta), 0)) == -1)
		        ERROR(46, "Can't send to server");
		    printf("ok.  (%d bytes enviados)\n", (int)tcp_sent_bytes);

		    char string[64];

		    // TCP IPv4: "recv" do servidor (bloqueante)
		    printf("à espera de dados do servidor... "); fflush(stdout);
		    if ((tcp_read_bytes = recv(tcp_client_socket, &string, sizeof(string), 0)) == -1)
		        ERROR(47, "Can't recv from server");
		    printf("ok.  (%d bytes recebidos)\n", (int)tcp_read_bytes);

		    if (resposta == 0)
		        printf("Data/hora: %s\n", string);
		    else if (resposta == 1)
		        printf("Data: %s\n", string);
		    else printf("hora: %s\n", string);
			
			// TCP IPv4: fecha socket (client)
			if (close(tcp_client_socket) == -1)
				ERROR(45, "Can't close tcp_client_socket (IPv4)");
			printf("ligação fechada. ok. \n");
		} else					// < 0 - erro
			ERROR(2, "Erro na execucao do fork()");
	}

	// libertar recurso (cmdline_parser)
	cmdline_parser_free(&args);	
		
	exit(0);
}	
