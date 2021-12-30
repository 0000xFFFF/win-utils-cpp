CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS   = -lws2_32

OBJ = send.c recv.c

all: $(OBJ)
	$(CC) $(CFLAGS) send.c -o sends $(LIBS)
	$(CC) $(CFLAGS) recv.c -o recvs $(LIBS)

clean:
	del "*.o" "*.exe"