/**
 * @file: server.c
 * @date: 2016-11-17
 * @author: autor
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "debug.h"
#include "common.h"
#include "server_opt.h"

int main(int argc, char *argv[])
{
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser (argc, argv, &args_info) != 0)
    {
        exit(ERR_ARGS);
    }

    int udp_server_socket;
	if ((udp_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ERROR(31, "Can't create udp_server_socket (IPv4)");

    struct sockaddr_in udp_server_endpoint;
	memset(&udp_server_endpoint, 0, sizeof(struct sockaddr_in));
	udp_server_endpoint.sin_family = AF_INET;   //Para endereços IPv4
	udp_server_endpoint.sin_addr.s_addr = htonl(INADDR_ANY);  	// Todas as interfaces de rede
	udp_server_endpoint.sin_port = htons(args_info.port_arg);	// Server port

    if (bind(udp_server_socket, (struct sockaddr *) &udp_server_endpoint, 
    sizeof(struct sockaddr_in)) == -1)
		ERROR(32, "Can't bind @udp_server_endpoint info");

    char filename[MAX_FILENAME_SIZE];

	socklen_t udp_client_endpoint_length = sizeof(struct sockaddr_in);
	struct sockaddr_in udp_client_endpoint;
	ssize_t udp_read_bytes, udp_sent_bytes;

    while(1)
    {
        //Recebe string do cliente
        printf("à espera de dados do cliente... "); 
        fflush(stdout);
        if ((udp_read_bytes = recvfrom(udp_server_socket, filename, MAX_FILENAME_SIZE, 0,
        (struct sockaddr *) &udp_client_endpoint, &udp_client_endpoint_length)) == -1)
            ERROR(34, "Can't recvfrom client");            
        printf("ok.  (%d bytes received)\n", (int)udp_read_bytes);

        printf("\n\tMensagem recebida: %s\n", filename);
        FILE *fptr = fopen(filename, "r");
        if(fptr == NULL)
        {
            printf("\n\tO ficheiro %s não existe\n", filename);
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
            printf("\tLast Access: <%s>\n", lastAccess);
            localtime_r(&st.st_mtime, &lt);
            strftime(lastModified, sizeof(lastModified), "%a, %d %b %Y %T", &lt);
            printf("\tLast Modified: <%s>\n", lastModified);
            localtime_r(&st.st_ctime, &lt);
            strftime(lastChanged, sizeof(lastChanged), "%a, %d %b %Y %T", &lt);
            printf("\tLast Changed: <%s>\n", lastChanged);
        }

        // UDP IPv4: "sendto" para o cliente
        printf("a enviar dados para o cliente... "); 
        fflush(stdout);
        if ((udp_sent_bytes = sendto(udp_server_socket, filename, MAX_FILENAME_SIZE, 0, 
        (struct sockaddr *) &udp_client_endpoint, udp_client_endpoint_length)) == -1)
            ERROR(35, "Can't sendto client");
            
        printf("ok.  (%d bytes sent)\n", (int)udp_sent_bytes);
    }

    if (close(udp_server_socket) == -1)
	    ERROR(33, "Can't close udp_server_socket (IPv4)");

    cmdline_parser_free(&args_info);

    return 0;
}