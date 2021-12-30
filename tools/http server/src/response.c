#include <stdio.h>
#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include <shlwapi.h>
#include "server.h"

BOOL FileExists(LPCTSTR szPath) {
	DWORD dwAttrib = GetFileAttributes(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL TrashFile(const char* file) {
	SHFILEOPSTRUCT fileop;
    memset(&fileop, 0, sizeof(fileop));
    fileop.wFunc = FO_DELETE;
    fileop.pFrom = file;
    fileop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
    return SHFileOperation(&fileop) == 0;
}

char* get_content_type(const char* path) {
    //char* extension = strchr(name, '.');
	char* extension = PathFindExtension(path);
	if (extension == NULL)           { return "*/*";             }
    if (StrStrI(extension, ".html")) { return "text/html";       }
    if (StrStrI(extension, ".css"))  { return "text/css";        }
	if (StrStrI(extension, ".js"))   { return "text/javascript"; }

	if (StrStrI(extension, ".ico"))  { return "image/webp"; }
	if (StrStrI(extension, ".apng")) { return "image/apng"; }
	if (StrStrI(extension, ".avif")) { return "image/avif"; }
	if (StrStrI(extension, ".gif"))  { return "image/gif";  }
	if (StrStrI(extension, ".jpg")
	||  StrStrI(extension, ".jpeg")
	||  StrStrI(extension, ".jfif")
	||  StrStrI(extension, ".pjpeg")
	||  StrStrI(extension, ".pjp"))  { return "image/jpeg";    }
	if (StrStrI(extension, ".png"))  { return "image/png";     }
	if (StrStrI(extension, ".svg"))  { return "image/svg+xml"; }
	if (StrStrI(extension, ".webp")) { return "image/webp";    }

    return "*/*";
}

const char* DEFAULT_ERROR_400 = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
const char* DEFAULT_ERROR_403 = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>403 Forbidden</title></head><body><h1>Forbidden</h1>The requested URL is forbidden.</body></html>";
const char* DEFAULT_ERROR_404 = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>404 Not Found</title></head><body><h1>Not Found</h1>The requested URL was not found on this server.</body></html>";
const char* DEFAULT_ERROR_500 = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
const char* DEFAULT_ERROR_501 = "HTTP/1.1 501 Not Implemented\r\nContent-Length: 0\r\n\r\n";

int SendDefHeader(SOCKET sock, int code) {
	
	int ret = 0;
	tee(" -> ");
	switch (code) {
		case 400: ret = send(sock, DEFAULT_ERROR_400, strlen(DEFAULT_ERROR_400), 0); break;
		case 403: ret = send(sock, DEFAULT_ERROR_403, strlen(DEFAULT_ERROR_403), 0); break;
		case 404: ret = send(sock, DEFAULT_ERROR_404, strlen(DEFAULT_ERROR_404), 0); break;
		case 500: ret = send(sock, DEFAULT_ERROR_500, strlen(DEFAULT_ERROR_500), 0); break;
		case 501: ret = send(sock, DEFAULT_ERROR_501, strlen(DEFAULT_ERROR_501), 0); break;
	}
	tee("%d", code);
	flog(">> RETURN CODE: %d\n", code);
	
	return ret != SOCKET_ERROR && ret != 0;
}

int Respond_GET(SOCKET sock, REQUEST* request) {
	
	// make req buffer
	char REQ[MAX_PATH] = {0};
	
	// get cwd
	char CWD[MAX_PATH] = {0};
	getcwd(CWD, MAX_PATH-1);
	
	// cwd\request
	strcat(REQ, CWD);
	if (!strcmp(request->value, "/")) { strcat(REQ, "\\index.html"); }
	else { strcat(REQ, request->value); }
	
	// get full file path
	char FullFilePath[MAX_PATH] = {0};
	GetFullPathName(REQ, MAX_PATH, FullFilePath, NULL);
	
	// test if file exists
	if (!FileExists(FullFilePath)) { return SendDefHeader(sock, 404); }
	
	// open file
	FILE* f = fopen(FullFilePath, "rb");
	if (!f) { return SendDefHeader(sock, 500); }
	
	// send 200 header
	char header[MIDSIZ];
	sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", get_content_type(request->value));
	tee(" -> ");
	int s = send(sock, header, strlen(header), 0);
	if (s == SOCKET_ERROR) { return s; }
	tee("200");
	flog(">> RETURN CODE: 200\n");
	
	// send data (file)
	char buf[KSIZ] = {0};
	int result = 0;
	while ((result = fread(buf, 1, KSIZ, f)) > 0) {
		int msg_len = send(sock, buf, result, 0);
		if (msg_len == SOCKET_ERROR || msg_len == 0) {
			fclose(f);
			tee(" -- reset");
			flog(">> RESET...\n");
			return SOCKET_ERROR;
		}
	}
	fclose(f);
	
	tee(" -> sent: '%s'", FullFilePath);
	flog(">> FILE SENT.: '%s'\n", FullFilePath);
	
	return 1;
}

int Respond_HEAD(SOCKET sock, REQUEST* request) {
	UNUSED(request);
	tee(" -- unimplemented request type: HEAD");
	return SendDefHeader(sock, 501);
}

int Respond_POST(SOCKET sock, REQUEST* request) {
	// make req buffer
	char REQ[MAX_PATH] = {0};
	
	// get cwd
	char CWD[MAX_PATH] = {0};
	getcwd(CWD, MAX_PATH-1);
	
	// cwd\edit_folder\request
	strcat(REQ, CWD);
	strcat(REQ, "\\");
	strcat(REQ, EDIT_FOLDER);
	strcat(REQ, "\\");
	strcat(REQ, request->value);
	
	// get full file path
	char FullFilePath[MAX_PATH] = {0};
	GetFullPathName(REQ, MAX_PATH, FullFilePath, NULL);
	
	// open file
	FILE* f = fopen(FullFilePath, "a");
	if (!f) { return SendDefHeader(sock, 500); }

	// send 200 header
	char header[MIDSIZ];
	sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", get_content_type(request->value));
	tee(" -> ");
	int s = send(sock, header, strlen(header), 0);
	if (s == SOCKET_ERROR) { return s; }
	tee("200");
	flog(">> RETURN CODE: 200\n");
	
	// post
	if (request->data != NULL) { fprintf(f, "%s\n", request->data); }
	fclose(f);
	
	tee(" -> posted: '%s'", FullFilePath);
	flog(">> POSTED: '%s'\n", FullFilePath);
	return 1;
}

int Respond_PUT(SOCKET sock, REQUEST* request) {
	UNUSED(request);
	tee(" -- unimplemented request type: PUT");
	return SendDefHeader(sock, 501);
}

int Respond_DELETE(SOCKET sock, REQUEST* request) {
	// make req buffer
	char REQ[MAX_PATH] = {0};
	
	// get cwd
	char CWD[MAX_PATH] = {0};
	getcwd(CWD, MAX_PATH-1);
	
	// cwd\edit_folder\request
	strcat(REQ, CWD);
	strcat(REQ, "\\");
	strcat(REQ, EDIT_FOLDER);
	strcat(REQ, "\\");
	strcat(REQ, request->value);
	
	// get full file path
	char FullFilePath[MAX_PATH] = {0};
	GetFullPathName(REQ, MAX_PATH, FullFilePath, NULL);
	
	// send 200 header
	char header[MIDSIZ];
	sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", get_content_type(request->value));
	
	tee(" -> ");
	int s = send(sock, header, strlen(header), 0);
	if (s == SOCKET_ERROR) { return s; }
	tee("200");
	flog(">> RETURN CODE: 200\n");
	
	if (TrashFile(FullFilePath)) {
		tee(" -> deleted: '%s'", FullFilePath);
		flog(">> DELETED: '%s'\n", FullFilePath);
    }
	else {
		tee(" -> failed to delete: '%s'", FullFilePath);
		flog(">> FAILED TO DELETE: '%s'\n", FullFilePath);
	}

	
	return 1;
}

int Respond_CONNECT(SOCKET sock, REQUEST* request) {
	UNUSED(request);
	tee(" -- unimplemented request type: CONNECT");
	return SendDefHeader(sock, 501);
}

int Respond_OPTIONS(SOCKET sock, REQUEST* request) {
	UNUSED(request);
	tee(" -- unimplemented request type: OPTIONS");
	return SendDefHeader(sock, 501);;
}

int Respond_TRACE(SOCKET sock, REQUEST* request) {
	UNUSED(request);
	tee(" -- unimplemented request type: TRACE");
	return SendDefHeader(sock, 501);
}

int Respond_PATCH(SOCKET sock, REQUEST* request) {
	UNUSED(request);
	tee(" -- unimplemented request type: PATCH");
	return SendDefHeader(sock, 501);
}

int Respond(SOCKET sock, REQUEST* request) {
	
	switch (request->type) {
		case RT_GET:     return Respond_GET    (sock, request); break;
		case RT_HEAD:    return Respond_HEAD   (sock, request); break;
		case RT_POST:    return Respond_POST   (sock, request); break;
		case RT_PUT:     return Respond_PUT    (sock, request); break;
		case RT_DELETE:  return Respond_DELETE (sock, request); break;
		case RT_CONNECT: return Respond_CONNECT(sock, request); break;
		case RT_OPTIONS: return Respond_OPTIONS(sock, request); break;
		case RT_TRACE:   return Respond_TRACE  (sock, request); break;
		case RT_PATCH:   return Respond_PATCH  (sock, request); break;
		
		case RT_UNK:
		default: tee(" -- unknown request"); break;
	}
	
	return 0;
}