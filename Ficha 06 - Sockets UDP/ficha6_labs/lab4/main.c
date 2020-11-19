#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <assert.h>

#include "debug.h"
#include "memory.h"

int main(void) {

    /* a) Criar um socket UDP / IPv4 */
    int socket_v4 = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_v4 == -1)
    {
        ERROR(1, "socket v4 failed\n");
    }

    /* b) Criar um socket UDP / IPv6 */
    int socket_v6 = socket(AF_INET6, SOCK_DGRAM, 0);

     if(socket_v6 == -1)
    {
        ERROR(1, "socket v6 failed\n");
    }

    /* c) Mostrar descritores dos sockets */
    printf("\n\tsocket UDP IPv4: %d\n", socket_v4);
    printf("\tsocket UDP IPv4: %d\n", socket_v6);

    /* d) Fechar os descritores dos sockets */
    close(socket_v4);
    close(socket_v6);

    return 0;
}
