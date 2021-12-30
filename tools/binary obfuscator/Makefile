CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
EXE    = binob

OBJ = main.c main2.c

all: $(OBJ)
	$(CC) $(CFLAGS) main.c -o $(EXE)
	$(CC) $(CFLAGS) main2.c -o $(EXE)s

clean:
	del "*.o" "*.exe"