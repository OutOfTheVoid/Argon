#include <argon/ui/ui.h>

#include <argon/osal/osal.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
	#include <argon/osal/platforms/macosx/windowsystem.h>
#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
#else
#endif

void Argon::UI::application_runloop ( ApplicationInitOptions & init_options )
{
	
	#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
	
	using OSAL::MacOSX::MacApplication;
	
	MacApplication::get_shared_instance () -> set_activation_policy ( init_options.foreground_app ? MacApplication::kactivation_policy_regular : MacApplication::kactivation_policy_prohibited );
	MacApplication::get_shared_instance () -> set_application_did_finish_launching_callback ( init_options.application_started_callback, init_options.application_started_data );
	MacApplication::get_shared_instance () -> run ();
	
	#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
	#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
	#else
	#endif
	
}
