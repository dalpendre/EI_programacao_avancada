#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <arpa/inet.h>

#include "debug.h"
#include "memory.h"

int main(void) 
{
    /* Verificar tamanho do tipo short */
    if(sizeof(short) != 2)      //assert(sizeof(short) == 2))
    {
        WARNING("short size não é 2 bytes\n");
    }

    /* Determinar endianess da máquina local */
    unsigned short num = 0x1122;

    if(htons(num) == num)
    {
        printf("\n\tMy system is big endian\n");
    }
    else
    {
        printf("\n\tMy system is little endian\n");
    }

    return 0;
}
