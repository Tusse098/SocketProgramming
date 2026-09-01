#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

// Socket to create a file pointer thingy?
// Bind to bind this socket/file pointer thingy to a port
//

#define MYPORT "9995"
#define BACKLOG 10

int main() {

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		return 0;
	}

	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int sockfd, new_fd;
	struct addrinfo hints, * res;


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, MYPORT, &hints, &res);


	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(sockfd, res->ai_addr, res->ai_addrlen);
	listen(sockfd, BACKLOG);


	addr_size = sizeof their_addr;
	new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &addr_size);


	freeaddrinfo(res);
	WSACleanup();
	return 0;
}