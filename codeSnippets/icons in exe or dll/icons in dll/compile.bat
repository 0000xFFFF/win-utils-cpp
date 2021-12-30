windres res.rc -O coff -o res.res
g++ -c -DBUILD_DLL main.cpp
g++ -shared res.res main.o -Wl,--out-implib,libmessage.a -o main.dll