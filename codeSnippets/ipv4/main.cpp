#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

int main() {
	
	// Init WinSock
	WSADATA wsa_Data;
	int wsa_ReturnCode = WSAStartup(0x101, &wsa_Data);
	
	// Get the local hostname
	char szHostName[255];
	gethostname(szHostName, 255);
	struct hostent *host_entry;
	host_entry = gethostbyname(szHostName);
	char* ip;
	ip = inet_ntoa(*(struct in_addr*)*host_entry->h_addr_list);
	WSACleanup();
	
	std::cout << ip << std::endl;
	
	return 0;
}
