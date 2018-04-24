#include <argon/argon.h>
#include <argon/ui/guiwindow.h>
#include <argon/ui/ui.h>

void ApplicationLaunched ( void * Data );

using Argon::UI::GUIWindow;

GUIWindow * main_window = nullptr;

void AppEntry ()
{
	
	Argon::UI::ApplicationInitOptions init_options;
	init_options.foreground_app = true;
	init_options.application_started_callback = ApplicationLaunched;
	init_options.application_started_data = nullptr;
	
	Argon::UI::application_runloop ( init_options );
	
	main_window -> Deref ();
	
}

void ApplicationLaunched ( void * Data )
{
	
	main_window = GUIWindow::create (
		{ { 500, 500 }, { 600, 400 } },
		GUIWindow::kstyle_closable | GUIWindow::kstyle_minimizable | GUIWindow::kstyle_resizable | GUIWindow::kstyle_framed
	);
	main_window -> set_title ( "Hello world!" );
	main_window -> show ();
	
}

OSAL_BUILD_MAIN_METHOD( AppEntry );
