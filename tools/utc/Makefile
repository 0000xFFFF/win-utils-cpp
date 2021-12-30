CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s

all: $(OBJ)
	$(CC) $(CFLAGS) utc.c  -o utc
	$(CC) $(CFLAGS) utch.c -o utch
	$(CC) $(CFLAGS) localtime.c -o localtime

clean:
	del "*.o" "*.exe"