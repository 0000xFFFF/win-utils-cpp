CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
EXE    = tee_test

OBJ = main.c tee.c

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

clean:
	del "*.o" "*.exe" "*.log"