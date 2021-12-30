CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS   = -lws2_32
EXE    = sbm

OBJ = main.c

debug: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)_debug $(LIBS) -D DEBUG 

release: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)_release $(LIBS) -mwindows

release_admin: $(OBJ)
	windres resources.rc -O coff -o resources.res
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)_release_admin $(LIBS) -mwindows resources.res

all: debug release release_admin

clean:
	del "*.o" "*.res" "*.exe"