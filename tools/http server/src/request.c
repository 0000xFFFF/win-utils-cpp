#include <stdio.h>
#include <winsock2.h>
#include "server.h"

int get_1n2(const char* buff, char* str1, char* str2) {
	int sawSpace = 0;
	int i1 = 0;
	int i2 = 0;
	for (size_t i = 0; i < strlen(buff); i++) {
		if (!sawSpace && buff[i] == ' ') { sawSpace = 1; continue; }
		if (sawSpace) { str2[i2] = buff[i]; i2++; }
		else          { str1[i1] = buff[i]; i1++; }
	}
	return 1;
}

const char* request2str(const int* val) {
	switch (*val) {
		case RT_GET:     return "GET";     break;
		case RT_HEAD:    return "HEAD";    break;
		case RT_POST:    return "POST";    break;
		case RT_PUT:     return "PUT";     break;
		case RT_DELETE:  return "DELETE";  break;
		case RT_CONNECT: return "CONNECT"; break;
		case RT_OPTIONS: return "OPTIONS"; break;
		case RT_TRACE:   return "TRACE";   break;
		case RT_PATCH:   return "PATCH";   break;
	}
	return "UNK";
}

REQUEST* GetRequest(SOCKET sock) {
	// get req
	char buf[REQUEST_SIZE] = {0};
	flog(">> Receiving...\n");
	int msg_len = recv(sock, buf, REQUEST_SIZE, 0);
	tee(" -> '%d'b -> ", msg_len);
	flog(">> RECV BUFF.: %d\n", msg_len);
	if (msg_len == 0 || msg_len == SOCKET_ERROR) {
		tee("SOCKET_ERROR");
		return NULL;
	}
	
	// log it
	int c = 0;
	char buf2[REQUEST_SIZE] = {0};
	for (int i = 0; i < REQUEST_SIZE; i++) {
		if (buf[i] == '\r') { continue; }
		buf2[c++] = buf[i];
	}
	flog("%s", buf2);
	
	// make req
	REQUEST* request = malloc(sizeof(REQUEST));
	request->buff_len = msg_len;
	request->type = RT_UNK;
	request->value = NULL;
	request->data = NULL;
	
	// get request
	#define REQBUFFSIZ 10
	char str1[REQBUFFSIZ] = {0};
	char str2[MAX_PATH] = {0};
	char format[32] = {0};
	sprintf(format, "%%%ds %%%ds", REQBUFFSIZ-1, MAX_PATH-1);
	sscanf(buf, format, str1, str2);
	//if (str2[strlen(str2)-1] == '/') { strcat(str2, "index.html"); }
	
	if      (!strcmp(str1, "GET"))     { request->type = RT_GET;     }
	else if (!strcmp(str1, "HEAD"))    { request->type = RT_HEAD;    }
	else if (!strcmp(str1, "POST"))    { request->type = RT_POST;    }
	else if (!strcmp(str1, "PUT"))     { request->type = RT_PUT;     }
	else if (!strcmp(str1, "DELETE"))  { request->type = RT_DELETE;  }
	else if (!strcmp(str1, "CONNECT")) { request->type = RT_CONNECT; }
	else if (!strcmp(str1, "OPTIONS")) { request->type = RT_OPTIONS; }
	else if (!strcmp(str1, "TRACE"))   { request->type = RT_TRACE;   }
	else if (!strcmp(str1, "PATCH"))   { request->type = RT_PATCH;   }
	
	request->value = strdup(str2);
	
	// get end of line data
	char* end = strstr(buf, "\r\n\r\n");
	if (end != NULL) {
		end += 4;
		request->data = strdup(end);
	}
	
	return request;
}