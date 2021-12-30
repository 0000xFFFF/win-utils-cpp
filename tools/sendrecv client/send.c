#include <stdio.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include <windows.h>

int main(int argc, char** argv) {
	
	if (argc != 4) {
		printf("USAGE: %s <ip> <port> <file>\n", argv[0]);
		return 1;
	}
	
	// init winsock
	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) { fprintf(stderr, "ERROR: failed to init winsock\n"); return 1; }
	
	// make socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) { fprintf(stderr, "ERROR: failed to create socket\n"); closesocket(sock); return 1; }
	
	// set ip:port
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	
	// connect
	printf("# connecting...\n");
	if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) { fprintf(stderr, "ERROR: failed to connect\n"); closesocket(sock); return 1; }
	
	FILE* f = fopen(argv[3], "rb");
	if (!f) {
		fprintf(stderr, "ERROR: failed to open file\n");
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	
	printf("# sending...\n");

	// get file size
	fseek(f, 0L, SEEK_END);
	long fileSize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	int retval = 0;

	// send data (file)
	#define KSIZ 1024
	char buff[KSIZ] = {0};
	int result = 0;
	size_t total = 0;
	int lastp = 0;
	while ((result = fread(buff, 1, KSIZ, f)) > 0) {
		int toadd = 0;
		if ((toadd = send(sock, buff, result, 0)) == SOCKET_ERROR) {
			fprintf(stderr, "ERROR: send error\n");
			retval = 1;
			break;
		}
		total += toadd;

		int p = ((float)total / (float)fileSize * 100.0f);
		if (p != lastp) { lastp = p; printf("> %d %% (%d/%ld)\n", p, total, fileSize); }

		
	}
	printf("# sent: %d\n", total);
	
	fclose(f);
	closesocket(sock);
	WSACleanup();
	return retval;
}