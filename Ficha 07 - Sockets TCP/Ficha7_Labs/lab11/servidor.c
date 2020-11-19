#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "debug.h"
#include "comum.h"
#include "servidor_opt.h"

void processaCliente(int fd);

int main(int argc, char *argv[])
{
    int ser_fd, cli_fd;
	socklen_t cli_len;
    struct sockaddr_in ser_addr, cli_addr;

    /* Processa os parâmetros da linha de comando */
    struct gengetopt_args_info args_info;
    if (cmdline_parser(argc, argv, &args_info) != 0){
	    fprintf(stderr, "ERROR: cmdline_parser");
	    exit(C_ERRO_CMDLINE);
    }

    /* cria um socket */
    if ((ser_fd = socket(AF_INET, SOCK_STREAM, 0)) == 1)
        ERROR(C_ERRO_SOCKET, "socket");

    /* preenche estrutura: ip/porto do servidor */
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(args_info.porto_arg);

    /* disponibiliza o porto para escuta */
    if (bind(ser_fd, (struct sockaddr *) &ser_addr, sizeof(ser_addr)) == -1)
        ERROR(C_ERRO_BIND, "bind");
    if (listen(ser_fd, 5) == 1)
        ERROR(C_ERRO_LISTEN, "Listen");
    printf("Servidor %s no porto %d\n", argv[0], args_info.porto_arg);

    /* ciclo infinito para atender todos os clientes */
    while (1) {
	cli_len = sizeof(struct sockaddr);
        /* accept - bloqueante */
        cli_fd = accept(ser_fd, (struct sockaddr *) &cli_addr, &cli_len);
        if (cli_fd < 0){
            ERROR(C_ERRO_ACCEPT, "Accept");
	}

	/* mostra informação sobre o cliente e processa pedido */
	char ip[20];
	DEBUG("cliente [%s@%d]",
	  inet_ntop(AF_INET, &cli_addr.sin_addr, ip, sizeof(ip)),
	                                   ntohs(cli_addr.sin_port));
        processaCliente(cli_fd);
        
        /* liberta recursos utilizados com este cliente*/
        close(cli_fd);
    }

    return (0);
}



void processaCliente(int fd) 
{
    uint16_t  n_cli, n_serv, res;

    srand(time(NULL));
    n_serv = 1 + (uint16_t) (100.0 * rand() / (RAND_MAX + 1.0));
    DEBUG("número escolhido: %d\n", n_serv);

    do {
        /* recebe dados do cliente - chamada bloqueante */
        if (recv(fd, &n_cli, sizeof(uint16_t), 0) == -1)
            ERROR(C_ERRO_RECV, "recv");

        n_cli = ntohs(n_cli);

        if (n_cli == n_serv)
            res = IGUAL;
        else if (n_cli < n_serv)
            res = MENOR;
        else
            res = MAIOR;

        res = htons(res);

        /* envia resposta ao cliente */
        if (send(fd, &res, sizeof(uint16_t), 0) == -1)
            ERROR(C_ERRO_SEND, "send");
            
    } while (n_cli != n_serv);
}
