#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

const char html[] = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-type: text/html\r\n"
                    "\r\n"
                    "<html>\r\n"
                    "<head>\r\n"
                    "<title>TITLE</title>\r\n"
                    "</head>\r\n"
                    "<body>\r\n"
                    "<h1>HELLO WORLD</h1>\r\n"
                    "</body>\r\n"
                    "</html>\r\n\r\n";

int main(int argc, char* argv[]) {
	
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa ) != 0) {
		std::cerr << "failed to initialize winsock" << std::endl;
		return 1;
	}

    addrinfo* res = NULL;
    addrinfo hints;

    ZeroMemory(&hints, sizeof(hints)); // clear buffer
	
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, "80", &hints, &res ) != 0) {
		std::cerr << "using port" << std::endl;
		return 1;
	}
	
    SOCKET s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (s == INVALID_SOCKET) {
		std::cerr << "invalid socket" << std::endl;
		return 1;
	}

	if (bind(s, res->ai_addr, (int)res->ai_addrlen) == SOCKET_ERROR) {
		std::cerr << "can't bind port" << std::endl;
		return 1;
	}

    if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "can't listen to port" << std::endl;
		return 1;
	}

    SOCKET client = accept(s, NULL, NULL);

	if (client == INVALID_SOCKET) {
		std::cerr << "invalid client" << std::endl;
		return 1;
	}

    char buffer[512];
    int bytes;

    bytes = recv(client, buffer, 512, 0);
    for (int i = 0; i < bytes; ++i) {
        std::cout << buffer[i];
    }

	if (send(client, html, strlen(html) - 1, 0) < 0) {
		std::cerr << "sent less than 0 bytes" << std::endl;
		return 1;
	}
	
	if (shutdown(client, SD_BOTH) == SOCKET_ERROR) {
		std::cerr << "failed to shutdown" << std::endl;
		return 1;
	}

	// close & clean
    closesocket(client);
    WSACleanup();

    return 0;
}