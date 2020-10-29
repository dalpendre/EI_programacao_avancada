#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <time.h>

#include "debug.h"
#include "common.h"
#include "server_args.h"

int processa_pedido(int fd, uint16_t n_serv);

int main(int argc, char *argv[]) {
    /* Estrutura gerada pelo utilitario gengetopt para
     guardar os parametros de entrada */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser(argc, argv, &args_info) != 0)
        return 1;

    int sock_fd;
    /* Cria o socket */
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        ERROR(2, "Criaçao do socket");

    struct sockaddr_in ser_addr;
    /* Preenche a estrutura */
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_addr.sin_port = htons(args_info.porto_arg);

    /* Efetua o registo */
    if (bind(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
        ERROR(3, "bind server");

    srand(time(NULL));
    while (1) {
        uint16_t gerado = 1 + (uint16_t)(rand() % 100);
#ifdef SHOW_DEBUG
        DEBUG("Numero aleatório = %hu", gerado);
#endif
        /* Apenas sai do ciclo se o numero foi adivinhado */
        while (!processa_pedido(sock_fd, gerado))
            ;
    }
    return 0;
}

int processa_pedido(int fd, uint16_t n_serv) {
    uint16_t n_cli;
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof(cli_addr);
    if (recvfrom(fd, &n_cli, sizeof(n_cli), 0, (struct sockaddr *)&cli_addr,
                 &len) == -1)
        ERROR(4, "recvfrom");
#ifdef SHOW_DEBUG
    char ip[20];
    DEBUG("cliente [%s@%d]",
          inet_ntop(AF_INET, &cli_addr.sin_addr, ip, sizeof(ip)),
          htons(cli_addr.sin_port));
#endif

    n_cli = ntohs(n_cli);

    uint16_t res;
    if (n_cli == n_serv)
        res = IGUAL;
    else if (n_cli < n_serv)
        res = MENOR;
    else
        res = MAIOR;

    res = htons(res);

    if (sendto(fd, &res, sizeof(res), 0, (struct sockaddr *)&cli_addr, len) < 0)
        ERROR(5, "sendto");

    return n_cli == n_serv;
}
