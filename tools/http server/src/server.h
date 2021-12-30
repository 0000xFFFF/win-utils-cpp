#ifndef SERVER_H
#define SERVER_H

enum REQUEST_TYPES { RT_UNK, RT_GET, RT_HEAD, RT_POST, RT_PUT, RT_DELETE, RT_CONNECT, RT_OPTIONS, RT_TRACE, RT_PATCH };

typedef struct {
	int buff_len;
    int type;
    char* value;
	char* data;
} REQUEST;

#define BIGSIZ    8192
#define MIDSIZ    4096
#define KSIZ      1024
#define SMALLSIZ   256
#define TINYSIZ     64

#define REQUEST_SIZE 4096
#define DEFAULT_PORT 80
#define SERVER_RECV_TIMEOUT 240000 //4min

#define EDIT_FOLDER "edit"

// logging system
#include "tee.h"

extern REQUEST* GetRequest(SOCKET);
extern int Respond(SOCKET, REQUEST*);
extern const char* request2str(const int*);

#include "debug.h"

#endif // SERVER_H