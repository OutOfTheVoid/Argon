#include <argon/argon.h>
#include <argon/ui/guiwindow.h>
#include <argon/ui/ui.h>

void ApplicationLaunched ( void * Data );

using Argon::UI::GUIWindow;

GUIWindow * main_window = nullptr;

void AppEntry ()
{
	
	Argon::UI::ApplicationInitOptions app_init_options;

	GUIWindow * main_window;

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

	if ( ( * main_window_ptr ) != nullptr )
	{
		
		( * main_window_ptr ) -> show ();
		( * main_window_ptr ) -> set_title ( "Hello world!" );
		
	}
	
};

OSAL_BUILD_MAIN_METHOD( AppEntry );
