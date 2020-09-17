#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "args.h"

int main(int argc, char *argv[]) 
{
    struct gengetopt_args_info args_info;

    if(cmdline_parser(argc, argv, &args_info))
    {
        return 1;
    } 

    printf("\n\t%d\n", getpid());
    

    return 0;
}