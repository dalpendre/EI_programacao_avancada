/**
 * @brief Código auxiliar de threads
 * @author Rui Ferreira
 * @version 1.1 
 */
  
 //**********************************************************************
// 						 socket  UDP
//**********************************************************************

// includes
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


//----------------------------------------------------------------------
// 	UDP Client
//----------------------------------------------------------------------


//--- UDP Client :: ligação ------  ( ** não copiar este comentário ** )

	// UDP IPv4: cria socket
	int udp_client_socket;	
	if ((udp_client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ERROR(21, "Can't create udp_client_socket (IPv4)");
		
	// UDP IPv4: informação do servidor UDP
	socklen_t udp_server_endpoint_length = sizeof(struct sockaddr_in);	
	struct sockaddr_in udp_server_endpoint;
	memset(&udp_server_endpoint, 0, sizeof(struct sockaddr_in));
	udp_server_endpoint.sin_family = AF_INET;	
	switch (inet_pton(AF_INET, args.ip_arg / ? ? ? , &udp_server_endpoint.sin_addr.s_addr)) {
		case 0:
			fprintf(stderr, "[%s@%d] ERROR - Cannot convert IP address (IPv4): Invalid Network Address\n",
				__FILE__, __LINE__);
			exit(22);
		case -1:
			ERROR(22, "Cannot convert IP address (IPv4)");
	}
	udp_server_endpoint.sin_port = htons(args.port_arg/???);

	
	// aqui... a comunicação com o servidor


	// UDP IPv4: fecha socket (client)
	if (close(udp_client_socket) == -1)
		ERROR(23, "Can't close udp_client_socket (IPv4)");



//--- UDP Client :: comunicação --- ( ** não copiar este comentário ** )

	// UDP IPv4: variáveis auxiliares para sendto() / recvfrom()
	ssize_t udp_read_bytes, udp_sent_bytes;
	//char buffer[];
	//...

	// UDP IPv4: "sendto" para o servidor
	printf("a enviar dados para o servidor... "); fflush(stdout);
	if ((udp_sent_bytes = sendto(udp_client_socket, ???, sizeof/strlen(???), 0, (struct sockaddr *) &udp_server_endpoint, udp_server_endpoint_length)) == -1)
		ERROR(24, "Can't sendto server");
	printf("ok.  (%d bytes sent)\n", (int)udp_sent_bytes);

	// UDP IPv4: "recvfrom" do servidor (bloqueante)
	printf("à espera de dados do servidor... "); fflush(stdout);
	if ((udp_read_bytes = recvfrom(udp_client_socket, ???, sizeof(???), 0, (struct sockaddr *) &udp_server_endpoint, &udp_server_endpoint_length)) == -1)
		ERROR(25, "Can't recvfrom server");
	printf("ok.  (%d bytes received)\n", (int)udp_read_bytes);	

	
	
	
	
	
//----------------------------------------------------------------------
// 	UDP Server
//----------------------------------------------------------------------
	

//--- UDP Server :: ligação  ------ ( ** não copiar este comentário ** )

	// UDP IPv4: cria socket
	int udp_server_socket;
	if ((udp_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		ERROR(31, "Can't create udp_server_socket (IPv4)");

	// UDP IPv4: bind a IPv4/porto 
	struct sockaddr_in udp_server_endpoint;
	memset(&udp_server_endpoint, 0, sizeof(struct sockaddr_in));
	udp_server_endpoint.sin_family = AF_INET;
	udp_server_endpoint.sin_addr.s_addr = htonl(INADDR_ANY);  	// Todas as interfaces de rede
	udp_server_endpoint.sin_port = htons(args.port_arg/???);	// Server port
	if (bind(udp_server_socket, (struct sockaddr *) &udp_server_endpoint, sizeof(struct sockaddr_in)) == -1)
		ERROR(32, "Can't bind @udp_server_endpoint info");
		
	
	// aqui... a comunicação com o cliente
	

	// liberta recurso: socket UDP IPv4
	if (close(udp_server_socket) == -1)
		ERROR(33, "Can't close udp_server_socket (IPv4)");
	
	
	
	
//--- UDP Server :: comunicação --- ( ** não copiar este comentário ** )
	
	// UDP IPv4: variáveis auxiliares para sendto() / recvfrom()
	socklen_t udp_client_endpoint_length = sizeof(struct sockaddr_in);
	struct sockaddr_in udp_client_endpoint;
	ssize_t udp_read_bytes, udp_sent_bytes;
	//char buffer[];
	//...

	// UDP IPv4: "recvfrom" do cliente (bloqueante)
	printf("à espera de dados do cliente... "); fflush(stdout);
	if ((udp_read_bytes = recvfrom(udp_server_socket, ???, sizeof(???), 0, (struct sockaddr *) &udp_client_endpoint, &udp_client_endpoint_length)) == -1)
		ERROR(34, "Can't recvfrom client");
	printf("ok.  (%d bytes received)\n", (int)udp_read_bytes);

	// UDP IPv4: "sendto" para o cliente
	printf("a enviar dados para o cliente... "); fflush(stdout);
	if ((udp_sent_bytes = sendto(udp_server_socket, ???, sizeof/strlen(???), 0, (struct sockaddr *) &udp_client_endpoint, udp_client_endpoint_length)) == -1)
		ERROR(35, "Can't sendto client");
	printf("ok.  (%d bytes sent)\n", (int)udp_sent_bytes);



