#ifndef ARGON_OSAL_LINUX_MAIN_H
#define ARGON_OSAL_LINUX_MAIN_H

#include <argon/argon.h>

#define OSAL_BUILD_MAIN_METHOD(EntryFunction)\
int main ( int argc, const char * argv [] )\
{\
	Argon::LibInit ();\
	EntryFunction();\
	Argon::LibDeInit ();\
	return 0;\
}

#endif
