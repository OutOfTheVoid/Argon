#include <argon/osal/osal.h>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

#include <argon/osal/platforms/windows/windows.h>

HINSTANCE argon_osal_platforms_windows_get_application_hinstance ()
{

	static HINSTANCE hinstance_value = NULL;

	if ( hinstance_value == NULL )
		hinstance_value = GetModuleHandleW ( NULL );

	return hinstance_value;

}

#endif
