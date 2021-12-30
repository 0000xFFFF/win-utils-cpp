windres res.rc -O coff -o res.res
g++ main.cpp -static-libgcc -static-libstdc++ res.res -o main.exe
