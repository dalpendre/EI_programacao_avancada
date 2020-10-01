#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"

int main(void) 
{
    printf("PID = (%d) | PPID = (%d)\n", getpid(), getppid());

    pid_t pid = fork();

    if(pid == 0)
        printf("PID do processo filho = %d\n", getpid());
    else if(pid > 0)
        printf("PID do processo pai = %d | PID do processo filho = %d\n", getpid(), pid);
    else
        ERROR(1, "Erro na execução do fork\n");  

    printf("O processo %d terminou\n", getpid());

    /*for (int i = 0; i < 2; i++) 
    {
        pid_t pid = fork();
        if (pid == -1)
            ERROR(1, "Erro na execução do fork");
        else
            printf("PID: (%d) | PPID (%d)\n", getpid(), getppid());
    }*/

    return 0;
}