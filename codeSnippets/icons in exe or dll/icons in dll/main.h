#ifndef MAIN_H
#define MAIN_H

#include <windows.h>

#ifdef BUILD_DLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT __declspec(dllimport)
#endif

#endif // MAIN_H
