#include <argon/ui/ui.hpp>

#include <argon/osal/osal.hpp>
#include <argon/osal/windowsystem.hpp>


void Argon::UI::application_runloop ( ApplicationInitOptions & init_options )
{
	
	#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
	
	using OSAL::MacOSX::MacApplication;
	
	MacApplication::get_shared_instance () -> set_activation_policy ( init_options.foreground_app ? MacApplication::kactivation_policy_regular : MacApplication::kactivation_policy_prohibited );
	MacApplication::get_shared_instance () -> set_application_did_finish_launching_callback ( init_options.application_started_callback, init_options.application_started_data );
	MacApplication::get_shared_instance () -> run ();
	
	#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
	
	using OSAL::Linux::LinuxApplication;
	
	LinuxApplication * application_instance = LinuxApplication::get_shared_instance ();
	
	XEvent x_event;
	
	if ( init_options.application_started_callback != nullptr )
		init_options.application_started_callback ( init_options.application_started_data );
	
	while ( true )
	{
		
		while ( XPending ( application_instance -> display ) )
		{
			
			XNextEvent ( application_instance -> display, & x_event );
			
			// Handle events..
			
		}
		
	}
	
	#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

	if ( init_options.application_started_callback != nullptr )
		init_options.application_started_callback ( init_options.application_started_data );

	while ( true )
	{

		MSG windows_message;
		BOOL get_message_status = GetMessage ( & windows_message, NULL, 0, 0 );

		if ( get_message_status == FALSE )
			break;

		if ( get_message_status == - 1 )
		{

			// TODO: Handle error...

		}
		else
		{

			// handle the message...

			TranslateMessage ( & windows_message );
			DispatchMessage ( & windows_message );

		}

	}

	#else
	#endif
	
}
