CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS   = -lgdi32 -lgdiplus
EXE    = ss

OBJ = main.c

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LIBS)

clean:
	del "*.o" "*.exe"