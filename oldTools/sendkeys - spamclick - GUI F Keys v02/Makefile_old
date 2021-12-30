CC    = mingw32-g++
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIB   = -lgdi32 -mwindows
EXE   = SpamClicker

OBJ = sendkeys.o

all: $(OBJ)
	windres resources.rc -O coff -o resources.res
	$(CC) $(FLAGS) $(OBJ) main.cpp -o $(EXE) resources.res $(LIB)

clean:
	del "*.o" "*.res" "*.exe"