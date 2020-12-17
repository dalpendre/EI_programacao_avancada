/**
 * @brief Código auxiliar de sinais
 * @author Rui Ferreira
 * @version 1.1 
 */
 
//**********************************************************************
// 						 socket  TCP
//**********************************************************************

// includes
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

//----------------------------------------------------------------------
// 	TCP Client  
//----------------------------------------------------------------------


//----- TCP cliente :: ligação -----  (** não copiar este comentário **)

	// TCP IPv4: cria socket
	int tcp_client_socket;
	if ((tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ERROR(41, "Can't create tcp_client_socket (IPv4)");

	// TCP IPv4: connect ao IP/porto do servidor
	struct sockaddr_in tcp_server_endpoint;
	memset(&tcp_server_endpoint, 0, sizeof(struct sockaddr_in));
	tcp_server_endpoint.sin_family = AF_INET;
	switch (inet_pton(AF_INET, args.ip_arg / ? ? ? , &tcp_server_endpoint.sin_addr)) {
		case 0:
			fprintf(stderr, "[%s@%d] ERROR - Cannot convert IP address (IPv4): Invalid Network Address\n",
				__FILE__, __LINE__);
			exit(22);
		case -1:
			ERROR(22, "Cannot convert IP address (IPv4)");
	}
	tcp_server_endpoint.sin_port = htons(args.port_arg/???);						// Server port

	printf("a ligar ao servidor... "); fflush(stdout);
	if (connect(tcp_client_socket, (struct sockaddr *) &tcp_server_endpoint, sizeof(struct sockaddr_in)) == -1)
		ERROR(43, "Can't connect @tcp_server_endpoint");
	printf("ok. \n");
	
	// TCP IPv4: informação sobre IP/porto do cliente (porto atribuído automaticamente)	
	struct sockaddr_in tcp_client_endpoint;
	socklen_t tcp_client_endpoint_length = sizeof(struct sockaddr_in);
	char tcp_client_string_ip[20];	
	if (getsockname(tcp_client_socket, (struct sockaddr *)&tcp_client_endpoint, &tcp_client_endpoint_length) == -1)
		ERROR(44, "Can't connect @tcp_server_endpoint");
	printf("cliente: %s@%d\n", inet_ntop(AF_INET, &tcp_client_endpoint.sin_addr, tcp_client_string_ip, sizeof(tcp_client_string_ip)), htons(tcp_client_endpoint.sin_port));

			

	// aqui... a comunicação com o servidor


	// TCP IPv4: fecha socket (client)
	if (close(tcp_client_socket) == -1)
		ERROR(45, "Can't close tcp_client_socket (IPv4)");
	printf("ligação fechada. ok. \n");





//----- TCP cliente :: comunicação -  (** não copiar este comentário **)
	
	// TCP IPv4: variáveis auxiliares para send() / recv()
	ssize_t tcp_read_bytes, tcp_sent_bytes;
	//char buffer[???];
	//...
			
	// TCP IPv4: "send" para o servidor
	printf("a enviar dados para o servidor... "); fflush(stdout);
	if ((tcp_sent_bytes = send(tcp_client_socket, ???, sizeof/strlen(???), 0)) == -1)
		ERROR(46, "Can't send to server"));
	printf("ok.  (%d bytes enviados)\n", (int)tcp_sent_bytes);

	// TCP IPv4: "recv" do servidor (bloqueante)
	printf("à espera de dados do servidor... "); fflush(stdout);
	if ((tcp_read_bytes = recv(tcp_client_socket, ???, sizeof(???), 0)) == -1)
		ERROR(47, "Can't recv from server");
	printf("ok.  (%d bytes recebidos)\n", (int)tcp_read_bytes);	
	
	
	
	
//----------------------------------------------------------------------
// 	TCP Server 
//----------------------------------------------------------------------
//	outras opções 
//	* (reutilizar um porto usado anteriormente (logo de seguida)) *:
//	int option = 1;	
//	setsockopt(tcp_server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));


	
//----- TCP servidor :: ligação  ---  (** não copiar este comentário **)

	// TCP IPv4: cria socket
	int tcp_server_socket;
	if ((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ERROR(51, "Can't create tcp_server_socket (IPv4)");

	// TCP IPv4: bind a IPv4/porto 	
	struct sockaddr_in tcp_server_endpoint;
	memset(&tcp_server_endpoint, 0, sizeof(struct sockaddr_in));  	
	tcp_server_endpoint.sin_family = AF_INET;
	tcp_server_endpoint.sin_addr.s_addr = htonl(INADDR_ANY); 		// Todas as interfaces de rede
	tcp_server_endpoint.sin_port = htons(args.port_arg/???);		// Server port
	if (bind(tcp_server_socket, (struct sockaddr *) &tcp_server_endpoint, sizeof(struct sockaddr_in)) == -1)
		ERROR(52, "Can't bind @tcp_server_endpoint");

	// TCP IPv4: "listen" por clientes
	int tcp_max_simultaneous_clients = 1;			
    if (listen(tcp_server_socket, tcp_max_simultaneous_clients)  == -1)
		ERROR(53, "Can't listen for %d clients", tcp_max_simultaneous_clients);

	// TCP IPv4: "accept" 1 cliente (bloqueante)
	char tcp_client_string_ip[20];
	struct sockaddr_in tcp_client_endpoint;
	socklen_t tcp_client_endpoint_length = sizeof(struct sockaddr_in);
	int tcp_client_socket;
	printf("à espera da ligação do cliente... "); fflush(stdout);
	if ((tcp_client_socket = accept(tcp_server_socket, (struct sockaddr *) &tcp_client_endpoint, &tcp_client_endpoint_length)) == -1)
		ERROR(54, "Can't accept client");
	printf("ok. \n");			
	printf("cliente: %s@%d\n", inet_ntop(AF_INET, &tcp_client_endpoint.sin_addr, tcp_client_string_ip, sizeof(tcp_client_string_ip)), htons(tcp_client_endpoint.sin_port));


	// aqui... a comunicação com o cliente	


	// TCP IPv4: fecha socket (client)
	if (close(tcp_client_socket) == -1)
		ERROR(55, "Can't close tcp_client_socket (IPv4)");
			
	// TCP IPv4: fecha socket (server)
	if (close(tcp_server_socket) == -1)
		ERROR(56, "Can't close tcp_server_socket (IPv4)");	
	printf("ligação fechada. ok. \n");
	
	
	
//----- TCP servidor :: comunicação  -  (** não copiar este comentário **)
	
	// TCP IPv4: variáveis auxiliares para send() / recv()
	ssize_t tcp_read_bytes, tcp_sent_bytes;
	//char buffer[???];
	//...
			
	// TCP IPv4: "recv" do cliente (bloqueante)
	printf("à espera de dados do cliente... "); fflush(stdout);
	if ((tcp_read_bytes = recv(tcp_client_socket, ???, sizeof(???), 0)) == -1)
		ERROR(57, "Can't recv from client");
	printf("ok.  (%d bytes sent)\n", (int)tcp_read_bytes);		

	// TCP IPv4: "send" para o cliente
	printf("a enviar dados para o cliente... "); fflush(stdout);
	if ((tcp_sent_bytes = send(tcp_client_socket, ???, sizeof/strlen(???), 0)) == -1)
		ERROR(58, "Can't send to client");
	printf("ok.  (%d bytes received)\n", (int)tcp_sent_bytes);

	
