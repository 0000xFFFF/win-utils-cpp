CC    = mingw32-gcc
CC32  = i686-w64-mingw32-gcc
CC64  = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -static -Os -s
EXE = ldll

all: main.c 
	$(CC)   $(CFLAGS) main.c -o $(EXE)
	$(CC32) $(CFLAGS) main.c -o $(EXE)32
	$(CC64) $(CFLAGS) main.c -o $(EXE)64
	
clean:
	del "*.exe"