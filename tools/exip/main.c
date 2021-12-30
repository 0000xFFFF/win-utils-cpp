#include <stdio.h>
#include <windows.h>
#include <wininet.h>

int main() {
    HINTERNET net = InternetOpen("external ip retriever", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HINTERNET conn = InternetOpenUrl(net, "http://myexternalip.com/raw", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    char buf[4096];
    DWORD rSize;
    InternetReadFile(conn, buf, sizeof(buf), &rSize);
	buf[rSize] = '\0';
	InternetCloseHandle(conn);
    InternetCloseHandle(net);
	printf("%s\n", buf);
	return 0;
}