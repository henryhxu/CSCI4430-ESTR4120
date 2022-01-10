#include <arpa/inet.h>		// ntohs()
#include <stdio.h>		// printf(), perror()
#include <stdlib.h>		// atoi()
#include <string.h>		// strlen()
#include <sys/socket.h>		// socket(), connect(), send(), recv()
#include <unistd.h>		// close()

#include "helpers.h"		// make_client_sockaddr()

static const int MAX_MESSAGE_SIZE = 256;

/**
 * Sends a string message to the server.
 *
 * Parameters:
 *		hostname: 	Remote hostname of the server.
 *		port: 		Remote port of the server.
 * 		message: 	The message to send, as a C-string.
 * Returns:
 *		0 on success, -1 on failure.
 */
int send_message(const char *hostname, int port, const char *message) {
	if (strlen(message) > MAX_MESSAGE_SIZE) {
		perror("Error: Message exceeds maximum length\n");
		return -1;
	}

	// (1) Create a socket

	// (2) Create a sockaddr_in to specify remote host and port
	struct sockaddr_in addr;
	if (make_client_sockaddr(&addr, hostname, port) == -1) {
		return -1;
	}

	// (3) Connect to remote server
	
	// (4) Send message to remote server

	// (5) Close connection

	return 0;
}

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc != 4) {
		printf("Usage: ./client hostname port_num message\n");
		return 1;
	}
	const char *hostname = argv[1];
	int port = atoi(argv[2]);
	const char *message = argv[3];

	printf("Sending message %s to %s:%d\n", message, hostname, port);
	if (send_message(hostname, port, message) == -1) {
		return 1;
	}

	return 0;
}
