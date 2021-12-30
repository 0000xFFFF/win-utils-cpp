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
	
	// send file
	printf("# Opening file...\n"); 
	FILE* f = fopen(argv[3], "rb");
	if (!f) {
		fprintf(stderr, "ERROR: failed to open file\n");
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	
	// get file size
	fseek(f, 0L, SEEK_END);
	long fileSize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	printf("# Sending file...\n");
	#define KSIZ 1024
	char buff[KSIZ] = {0};
	int result = 0;
	size_t total = 0;
	int lastp = 0;
	while ((result = fread(buff, 1, KSIZ, f)) > 0) {
		int r = 0;
		if ((r = send(clientSocket, buff, result, 0)) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: send failed\n");
			fclose(f);
			return 0;
		}
		total += r;
		
		int p = ((float)total / (float)fileSize * 100.0f);
		if (p != lastp) { lastp = p; printf("> %d %% (%d/%ld)\n", p, total, fileSize); }
	}
	
	// cleanup
	fclose(f);
	closesocket(clientSocket);
	WSACleanup();
	
	return 0;
}