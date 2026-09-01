#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char* argv[]) {
	WSAData wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		fprintf(stderr, "WSAStartup failed");
		exit(1);
	}

	// Get server address

	// Loop for accept
		// if(!fork()) run child logic

}