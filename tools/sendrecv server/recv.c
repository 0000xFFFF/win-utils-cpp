#include <stdio.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include <windows.h>

int main(int argc, char** argv) {
	
	// check args
	if (argc != 4) {
		printf("USAGE: %s <ip> <port> <file>\n", argv[0]);
		return 1;
	}
	
	// initialize winsock
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) { fprintf(stderr, "ERROR: failed to initialize winsock\n"); return INVALID_SOCKET; }
	
	// create socket
	//SOCKET sock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) { fprintf(stderr, "ERROR: failed to create socket\n"); return 1; }
	
	// bind socket to ip:port
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	
	// bind & listen
	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) { fprintf(stderr, "ERROR: failed to bind socket\n"); closesocket(sock); return INVALID_SOCKET; }
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)                           { fprintf(stderr, "ERROR: failed to listen\n");      closesocket(sock); return INVALID_SOCKET; }
	
	printf("# Waiting for a connection...\n");
	// wait for a client
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	int clientSize = sizeof(client);
	SOCKET clientSocket = accept(sock, (struct sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET) { fprintf(stderr, "ERROR: failed to accept %d\n", WSAGetLastError()); closesocket(sock); return INVALID_SOCKET; }
	printf("# %s:%d\n", inet_ntoa(client.sin_addr), htons(client.sin_port));
	closesocket(sock);
	
	// set timeout for recv
	DWORD timeout = 3000;
	setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	
	// recv file
	printf("# Opening file...\n"); 
	FILE* f = fopen(argv[3], "wb");
	if (!f) {
		fprintf(stderr, "ERROR: failed to open file\n");
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	
	printf("# Receiving file...\n"); 
	#define KSIZ 1024
	char buff[KSIZ] = {0};
	int result = 0;
	size_t total = 0;
	while ((result = recv(clientSocket, buff, KSIZ, 0)) > 0) {
		fwrite(buff, sizeof(char), result, f);
		total += result;
		printf("\r# recv: %d", total);
	}
	printf("\n");
	
	// cleanup
	fclose(f);
	closesocket(clientSocket);
	WSACleanup();
	
	return 0;
}