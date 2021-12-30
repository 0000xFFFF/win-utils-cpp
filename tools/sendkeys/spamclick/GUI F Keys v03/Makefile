CC     = mingw32-gcc
CC32   = i686-w64-mingw32-gcc
CC64   = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Werror -Wextra -static -Os -s
LIBS   = -lgdi32 -mwindows
EXE    = SpamClicker

OBJ = main.c sendkeys.c

all: $(OBJ)
	windres resources.rc -O coff -o resources.res
	$(CC) $(OBJ) -o $(EXE) resources.res $(LIBS)

clean:
	del "*.o" "*.res" "*.exe"