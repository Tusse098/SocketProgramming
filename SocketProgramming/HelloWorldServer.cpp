#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
//#include <iostream>

#pragma comment(lib,"WS2_32")

#define PORT "3960"
#define BACKLOG 10
#define MSG "Hello World"

int main(int argc, char* argv[]) {
	WSAData wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		fprintf(stderr, "WSAStartup failed");
		exit(1);
	}

	struct addrinfo *servinfo, hints, * p;
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int connectionsocket;
	char yes = 1;

	char ipstr[INET_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (int rv = getaddrinfo(NULL, PORT, &hints, &servinfo) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	};

	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((connectionsocket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(connectionsocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == 1) {
			perror("server: setsockopt");
			exit(1);
		}

		if (bind(connectionsocket, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
			perror("server: bind");
			closesocket(connectionsocket);
			continue;
		}

		break;
	}
	
	
	listen(connectionsocket, BACKLOG);


	const char *msg = MSG;
	int msg_size = sizeof MSG;
	int sin_size;
	while (1) {
		sin_size = sizeof their_addr;
		if (int newfd = accept(connectionsocket, (struct sockaddr*)&their_addr, &sin_size)) {
			//if (std::thread()) {

			//}
			printf("Sending message\n");
			send(newfd, msg, msg_size, 0);
		}
	}

	return 0;
}