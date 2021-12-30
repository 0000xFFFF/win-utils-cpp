CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -c -DBUILD_DLL
XFLAGS = -Wall -shared
DLL    = crash

all: main.c
	$(CC)   $(CFLAGS) main.c -o main.o
	$(CC)   $(XFLAGS) main.o -o $(DLL).dll
	$(CC32) $(CFLAGS) main.c -o main32.o
	$(CC32) $(XFLAGS) main32.o -o $(DLL)32.dll
	$(CC64) $(CFLAGS) main.c -o main64.o
	$(CC64) $(XFLAGS) main64.o -o $(DLL)64.dll
	
clean:
	del "*.o" "*.dll"