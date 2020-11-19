#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include "debug.h"
#include "comum.h"
#include "cliente_opt.h"

void adivinhaNum(int fd);

int main(int argc, char *argv[])
{
    int sock_fd;
    struct sockaddr_in ser_addr;

    /* Processa os parâmetros da linha de comando */
    struct gengetopt_args_info args_info;
    if (cmdline_parser(argc, argv, &args_info) != 0){
	    fprintf(stderr,"ERROR: cmdline_parser\n");
	    exit(C_ERRO_CMDLINE);
    }

	/* preenche estrutura: ip/porto do servidor */
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(args_info.porto_arg);
    if (inet_pton(AF_INET, args_info.ip_arg, &ser_addr.sin_addr) <= 0)
        ERROR(C_ERRO_INET_PTON, "inet_pton");      
		
    /* cria um socket */
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        ERROR(C_ERRO_SOCKET, "socket");

    /* faz ligação ao servidor */
    if (connect(sock_fd, (struct sockaddr *) &ser_addr, sizeof(ser_addr)) == -1)
        ERROR(C_ERRO_CONNECT, "Nao conseguiu ligaçao");

	/* jogo */
    adivinhaNum(sock_fd);

	/* liberta recursos utilizados */
	close(sock_fd);
    
    return (0);
}


void adivinhaNum(int fd) 
{
    uint16_t num, res;

    do {
        printf("\nIntroduza um número entre 1 e 100:  ");        
        scanf("%hu", &num);  // hu - unsigned short (half) int

        num=htons(num);

		/* envia número ao servidor */
        if (send(fd, &num, sizeof(uint16_t), 0) < 0)
            ERROR(C_ERRO_SEND, "write");

		/* recebe a resposta do servidor - chamada bloqueante */ 
        if (recv(fd, &res, sizeof(uint16_t), 0) < 0)
            ERROR(C_ERRO_RECV, "read");

        res=ntohs(res);
        if (res == IGUAL)
            printf("Parabens! Acertou\n\n");
        else if (res == MENOR)
            printf("O número do servidor é MAIOR\n");
        else
            printf("O número do servidor é MENOR\n");

    } while (res != IGUAL);
}
