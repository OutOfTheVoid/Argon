#ifndef ARGON_OSAL_PLATFORMS_WINDOWS_MAIN_H
#define ARGON_OSAL_PLATFORMS_WINDOWS_MAIN_H

#include <argon/argon.h>

#define OSAL_BUILD_MAIN_METHOD(EntryFunction) \
#include <Windows.h> \
int CALLBACK WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) \
{\
	Argon::LibInit ();\
	EntryFunction();\
	Argon::LibDeInit ();\
	return 0;\
};

#endif
