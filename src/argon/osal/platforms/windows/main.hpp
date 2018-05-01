#ifndef ARGON_OSAL_PLATFORMS_WINDOWS_MAIN_HPP
#define ARGON_OSAL_PLATFORMS_WINDOWS_MAIN_HPP

#include <argon/osal/osal.hpp>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

#include <argon/argon.h>

#include <Windows.h>

#define OSAL_BUILD_MAIN_METHOD(EntryFunction)\
int main () \
{\
	int argc = 0;\
	LPWSTR * argv = CommandLineToArgvW ( GetCommandLine (), & argc ); \
	if (argv == NULL)\
		argc = 0;\
	Argon::Array<Argon::String> program_args ( argc );\
	if ( argv != NULL )\
	{\
		for ( int i = 0; i < argc; i ++ )\
		{\
			Argon::String argument ( reinterpret_cast<char16_t *> ( argv [ i ] ) );\
			program_args [ i ] = std::move ( argument );\
		}\
	}\
	Argon::lib_init ( std::move ( program_args ) ); \
	LocalFree ( argv );\
	EntryFunction();\
	Argon::lib_deinit ();\
	return 0;\
};\

#endif
#endif
