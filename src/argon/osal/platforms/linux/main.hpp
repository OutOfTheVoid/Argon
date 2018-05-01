#ifndef ARGON_OSAL_LINUX_MAIN_HPP
#define ARGON_OSAL_LINUX_MAIN_HPP

#include <argon/osal/osal.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

#include <argon/argon.h>

#define OSAL_BUILD_MAIN_METHOD(EntryFunction)\
int main ( int argc, const char * argv [] )\
{\
	Argon::Array<Argon::String> ProgramArgs ( argc );\
	for ( int i = 0; i < argc; i ++ )\
		ProgramArgs [ i ] = std::move ( Argon::String ( argv [ i ] ) );\
	Argon::lib_init ( std::move ( ProgramArgs ) );\
	EntryFunction();\
	Argon::lib_deinit ();\
	return 0;\
}

#endif
#endif
