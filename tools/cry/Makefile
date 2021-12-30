CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s

OBJ = cry.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) file.c -o cry_file
	$(CC) $(CFLAGS) $(OBJ) str.c -o cry_str

clean:
	del "*.o" "*.exe"