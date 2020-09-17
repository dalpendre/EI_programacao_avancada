#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"

int main(void) 
{
    //printf("PID=%d (%d)\n", getpid(), getppid());

    for (int i = 0; i < 2; i++) 
    {
        pid_t pid = fork();
        if (pid == -1)
            ERROR(1, "Erro na execução do fork");
        else
            printf("PID: (%d) | PPID (%d)\n", getpid(), getppid());
    }

    return 0;
}