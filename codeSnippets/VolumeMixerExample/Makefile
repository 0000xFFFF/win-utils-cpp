CC     = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS   = -lwinmm -lole32 -loleaut32
EXE    = test2

OBJ = main.c gotoxy.c

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LIBS)

clean:
	del "*.o" "*.exe"