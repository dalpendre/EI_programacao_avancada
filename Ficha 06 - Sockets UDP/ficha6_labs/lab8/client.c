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
#include "client_args.h"

void adivinha_num(int fd, struct sockaddr_in ser_addr);

int main(int argc, char *argv[]) {
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser(argc, argv, &args_info) != 0)
        return 1;

    int sock_fd;
    /* Cria o socket */
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        ERROR(2, "Criacao do socket");

    struct sockaddr_in ser_addr;
    /* Preenche a estrutura */
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(args_info.porto_arg);

    /* Utiliza a funcao inet_pton para preencher o endereco */
    switch (inet_pton(AF_INET, args_info.ip_arg, &ser_addr.sin_addr)) {
    case 0:
        printf("O endereco IP %s nao e' valido\n\n", args_info.ip_arg);
        cmdline_parser_print_help();
        return 2;
    case -1:
        printf("Endereco IP desconhecido: %s\n\n", args_info.ip_arg);
        cmdline_parser_print_help();
        return 2;
    }

    adivinha_num(sock_fd, ser_addr);

    close(sock_fd);
    return 0;
}

void adivinha_num(int fd, struct sockaddr_in ser_addr) {
    uint16_t num, res;
    do {
        printf("\nIntroduza um numero entre 1 e 100: ");
        scanf("%hu", &num);

        num = htons(num);

        socklen_t len = sizeof(struct sockaddr_in);

        if (sendto(fd, &num, sizeof(num), 0, (struct sockaddr *)&ser_addr,
                   len) < 0)
            ERROR(3, "sendto");

        if (recvfrom(fd, &res, sizeof(res), 0, (struct sockaddr *)&ser_addr,
                     &len) < 0)
            ERROR(4, "recvfrom");

        res = ntohs(res);

        if (res == IGUAL)
            printf("Parabens! Acertou\n\n");
        else if (res == MENOR)
            printf("O numero do servidor e' MAIOR\n");
        else
            printf("O numero do servidor e' MENOR\n");

    } while (res != IGUAL);
}
