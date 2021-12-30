CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
EXE    = sudo

OBJ = main.c

all: $(OBJ)
	windres resources.rc -O coff -o resources.res
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) resources.res

clean:
	del "*.o" "*.res" "*.exe"