#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"

int main(void) {
    pid_t pid = fork();
    if (pid == 0) { /* Processo filho */
        printf("Filho: %d\n", getpid());
    } else if (pid > 0) { /* Processo pai */
        pid_t pid_retorno = wait(NULL);
        printf("Pai: Terminou o processo %d\n", pid_retorno);
    } else /* < 0 -- erro */
        ERROR(1, "Erro na execução do fork()");

    return 0;
}
