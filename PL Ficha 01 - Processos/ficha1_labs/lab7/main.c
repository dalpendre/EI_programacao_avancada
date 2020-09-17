#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug.h"

int main(void) 
{
    pid_t pid;
    switch (pid = fork()) 
    {
        case -1:
            /* erro */
            ERROR(1, "Erro na execução do fork()");
            /*break; aqui não teria qualquer efeito, ERROR irá terminar programa */

        case 0:
            /* filho */
            /*Como o execlp() tem um no variável de parâmetros o
            * último parâmetro tem de ser sempre NULL*/
            execlp("ls", "ls", "-lF", "-a", NULL);
            ERROR(1, "erro no execlp");
            /*break; aqui não teria qualquer efeito, ERROR irá terminar programa */

        default:
            /* pai */
            wait(NULL);
            printf("Fim da execução do comando ls –lF -a.\n");
            break;
    }
    
    return 0;
}
