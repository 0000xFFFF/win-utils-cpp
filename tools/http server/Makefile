CC     = gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS   = -lws2_32 -lshlwapi
EXE    = http-server
OBJ    = src/tee.o src/request.o src/response.o src/server.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LIBS)

clean:
	del "src\*.o" "$(EXE).exe" "*.log"