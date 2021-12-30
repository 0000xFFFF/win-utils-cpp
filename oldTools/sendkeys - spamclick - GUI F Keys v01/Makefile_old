CC    = mingw32-g++
FLAGS = -Wall -Werror -Wextra -static -Os -s
LIB   = -lgdi32 -mwindows
EXE   = SpamClicker

all:
	windres resources.rc -O coff -o resources.res
	$(CC) $(FLAGS) main.cpp -o $(EXE) resources.res $(LIB)

clean:
	del "*.res" "*.exe"