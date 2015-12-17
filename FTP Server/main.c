// MY OWN ACTIVE FTP SERVER

#include "ftp.h"


int main(int argc, char** argv)
{
	
	if (argc < 2)
	{
		printf("User needs to enter a port number.\nIt can be any number greater than 1023.\n");
		exit(0);
	}
	// In active mode FTP the client connects from a random unprivileged port (N > 1023) to the FTP server's command port, port 21
	// User must pass as only parameter a random port N > 1023
	int PORT_NUMBER = atoi(argv[1]);
		
	// Specify a local or remote endpoint address to which to connect a socket.
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
		
	// Create a socket(Internet, TCP, Protocol)
	int door_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(door_socket < 0)
		perror("Error while creating socket.\n");
	bzero((char *) &server_address, sizeof(server_address));

	// code for the address family
	server_address.sin_family = AF_INET; 
	// htons() converts a port number in host byte order to a port number in network byte order 
	server_address.sin_port = htons(PORT_NUMBER); 
	// INADDR_ANY gets IP address of the machine on which the server is running
	server_address.sin_addr.s_addr = INADDR_ANY; 
	
	// Associate a socket with a port and address
	// bind() assigns a name to unnamed socket
	if(bind(door_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)  
	{	
		perror("Error on binding");
		exit(0);
	}
	
	// Establish queue for connection requests 
	listen(door_socket,5); // 5 is the maximum size of the backlog queue permitted by most systems
	 	
	socklen_t clientAddress =  sizeof(client_address); //stores size of address of the client

	int new_socket, pid;
	// Accept a connection request
	while(1)
	{
		new_socket = accept(door_socket, (struct sockaddr *) &client_address, &clientAddress);
	    	if (new_socket < 0) 
		{
			perror("Error on accept");
			exit(0);
		}

		// Handles 1+ clients at the same time
		pid = fork();
		if(pid < 0)
			perror("Error on fork");
		if(pid == 0)
		{
			close(door_socket);
			handle_client(new_socket); // send/recv processes ought to be handled in a fn outside of main
			close(new_socket); //In case it is still open 
			exit(0);
		}
		else
			close(new_socket);
	}
	return 0;

}


