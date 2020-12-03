/**
 * @file: client.c
 * @date: 2016-11-17
 * @author: autor
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "memory.h"
#include "debug.h"
#include "common.h"
#include "client_opt.h"

char* formatdate(char* str, time_t val);

int main(int argc, char *argv[])
{
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser (argc, argv, &args_info) != 0)
    {
	    exit(ERR_ARGS);
    }

    int udp_client_socket;	
    if ((udp_client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        ERROR(21, "Can't create udp_client_socket (IPv4)");        

    // UDP IPv4: informação do servidor UDP
    socklen_t udp_server_endpoint_length = sizeof(struct sockaddr_in);	
    struct sockaddr_in udp_server_endpoint;
    memset(&udp_server_endpoint, 0, sizeof(struct sockaddr_in));
    udp_server_endpoint.sin_family = AF_INET;	
    switch (inet_pton(AF_INET, args_info.ip_arg, &udp_server_endpoint.sin_addr.s_addr)) 
    {
        case 0:
            fprintf(stderr, "[%s@%d] ERROR - Cannot convert IP address (IPv4): Invalid Network Address\n",
            __FILE__, __LINE__);
            exit(22);
        case -1:
            ERROR(22, "Cannot convert IP address (IPv4)");
    }
    udp_server_endpoint.sin_port = htons(args_info.port_arg);

    char filename[MAX_FILENAME_SIZE];
    ssize_t /*udp_read_bytes,*/ udp_sent_bytes;

    do
    {
        printf("\n\tIndique o nome de um ficheiro no seu sistema: ");
		if(fgets(filename, MAX_FILENAME_SIZE-1, stdin) == NULL)
		{
			if(feof(stdin))
			{
				break;
			}
		}
		filename[strlen(filename)-1] = '\0';

		if(strlen(filename) == 0)
			continue;

        //Opens file on client and shows stats to verify server info
        FILE *fptr = fopen(filename, "r");
        if(fptr == NULL)
        {
            /*printf("\n\tO ficheiro %s não existe\n", filename);*/
        }
        else
        {
            struct stat st;
            stat(filename, &st);

            //printf("\n\tSize: <%ld> bytes\n", st.st_size);
            
            char lastAccess[MAX_DATE], lastModified[MAX_DATE], lastChanged[MAX_DATE];
            time_t t = st.st_mtime; /*st_mtime is type time_t */
            
            struct tm lt;
            localtime_r(&st.st_atime, &lt); /* converts to struct tm */
            strftime(lastAccess, sizeof(lastAccess), "%a, %d %b %Y %T", &lt);
            //printf("\tLast Access: <%s>\n", lastAccess);
            localtime_r(&st.st_mtime, &lt);
            strftime(lastModified, sizeof(lastModified), "%a, %d %b %Y %T", &lt);
            //printf("\tLast Modified: <%s>\n", lastModified);
            localtime_r(&st.st_ctime, &lt);
            strftime(lastChanged, sizeof(lastChanged), "%a, %d %b %Y %T", &lt);
            //printf("\tLast Changed: <%s>\n", lastChanged);
        }

        printf("\n\ta enviar dados para o servidor... "); 
        fflush(stdout);

        //Send filename to be verified in server and there all the stats
        if((udp_sent_bytes = sendto(udp_client_socket, filename, MAX_FILENAME_SIZE, 0, (struct sockaddr *) &udp_server_endpoint, udp_server_endpoint_length)) == -1)
            ERROR(24, "Can't send to server");
        printf("\n\n\tok.  (%d bytes sent)\n", (int)udp_sent_bytes);
    }while(1);

   	// UDP IPv4: fecha socket (client)
	if (close(udp_client_socket) == -1)
		ERROR(23, "Can't close udp_client_socket (IPv4)");

    cmdline_parser_free(&args_info);

    return 0;
}