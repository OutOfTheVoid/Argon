#include <argon/osal/platforms/windows/windows.h>

HINSTANCE argon_osal_platforms_windows_get_application_hinstance ()
{

	static HINSTANCE hinstance_value = NULL;

	if ( hinstance_value == NULL )
		hinstance_value = GetModuleHandleW ( NULL );

	return hinstance_value;

}
