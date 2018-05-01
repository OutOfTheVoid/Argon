#include <argon/argon.hpp>
#include <argon/ui/guiwindow.hpp>
#include <argon/ui/ui.hpp>

#include <iostream>

void ApplicationLaunched ( void * Data );

using Argon::UI::GUIWindow;

GUIWindow * main_window = nullptr;

void AppEntry ()
{
	
	Argon::UI::ApplicationInitOptions app_init_options;

	app_init_options.application_started_callback = ApplicationLaunched;
	app_init_options.application_started_data = reinterpret_cast <void *> ( & main_window );

	Argon::UI::application_runloop ( app_init_options );

	if ( main_window != nullptr )
		main_window -> Deref ();
	
};

void ApplicationLaunched ( void * data )
{
	
	GUIWindow ** main_window_ptr = reinterpret_cast <GUIWindow **> ( data );

	* main_window_ptr = GUIWindow::create ( { { 400, 400 }, { 600, 0 } }, GUIWindow::kstyle_titled | GUIWindow::kstyle_resizable | GUIWindow::kstyle_minimizable );
	
	std :: cout << "window: " << ( * main_window_ptr ) << std :: endl;

	if ( ( * main_window_ptr ) != nullptr )
	{
		
		std :: cout << "window allocated successfully!" << std :: endl;
		
		( * main_window_ptr ) -> show ();
		( * main_window_ptr ) -> set_title ( "Hello world!" );
		
	}
	
};

OSAL_BUILD_MAIN_METHOD( AppEntry );
