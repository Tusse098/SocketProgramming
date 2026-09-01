#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <thread>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <iostream>

#pragma comment(lib,"WS2_32")

#define PORT "3960"
#define BACKLOG 10
#define ADDRESS "127.0.0.1"
#define MAXDATASIZE 100

int main(int argc, char* argv[]) {
	WSAData wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		fprintf(stderr, "WSAStartup failed");
		exit(1);
	}

	//char* serveraddr = argv[1];
	
	struct addrinfo hints, * servinfo, *p;
	struct sockaddr_storage *their_addr;
	char buf[MAXDATASIZE];
	int sockfd;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(ADDRESS, PORT, &hints, &servinfo);

	for (p = servinfo; p != NULL; p = p->ai_next) {
		printf("Looping\n");
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}
		if (p->ai_family == AF_INET6) {
			printf("IPv6 Skipped\n");
			continue;
		}
		if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
			perror("client: connect");
			continue;
		}
		break;

	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect");
		return 2;
	}

	recv(sockfd, buf, MAXDATASIZE - 1, 0);

	printf(buf);

	return 0;

}