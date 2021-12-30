CC32   = mingw32-gcc
CC     = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
EXE    = program
LIBS   = -lole32

OBJ = main.c

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LIBS)

clean:
	del "*.o" "*.exe"