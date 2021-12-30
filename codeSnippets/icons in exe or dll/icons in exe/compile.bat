windres res.rc -O coff -o res.res
g++ main.cpp res.res -o main.exe