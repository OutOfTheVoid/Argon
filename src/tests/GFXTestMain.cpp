#include <argon/argon.hpp>
#include <argon/ui/guiwindow.hpp>
#include <argon/ui/ui.hpp>
#include <argon/rendering/context.hpp>
#include <argon/rendering/framebuffer.hpp>
#include <argon/events/events.hpp>
#include <argon/ui/events/uievents.hpp>

#include <iostream>

void ApplicationLaunched ( void * Data );

using Argon::UI::GUIWindow;
using Argon::Rendering::Context;
using Argon::Rendering::FrameBuffer;

GUIWindow * main_window = nullptr;

void AppEntry ()
{
	
	Argon::UI::ApplicationInitOptions app_init_options;

	app_init_options.application_started_callback = ApplicationLaunched;
	app_init_options.application_started_data = reinterpret_cast <void *> ( & main_window );

	Argon::UI::application_runloop ( app_init_options );

	if ( main_window != nullptr )
		main_window -> deref ();
	
};

int stop_count = 0;

void WindowShouldClose ( Argon::Events::Event * event, void * data )
{
	
	using Argon::UI::Events::WindowShouldCloseEvent;
	
	std :: cout << "Window should close!" << std :: endl;
	
	WindowShouldCloseEvent * window_should_close_event = dynamic_cast <WindowShouldCloseEvent *> ( event );
	
	if ( window_should_close_event == nullptr )
		return;
	
	if ( stop_count < 2 )
		window_should_close_event -> cancel_close ();
		
	stop_count ++;
	
}

void WindowWillClose ( Argon::Events::Event * event, void * data )
{
	
	using Argon::UI::Events::WindowEvent;
	
	std :: cout << "Window will close!" << std :: endl;
	
	WindowEvent * will_close_event = dynamic_cast <WindowEvent *> ( event );
	
	if ( will_close_event == nullptr )
		return;
	
	Argon::UI::application_runloop_exit ();
	
}

void ApplicationLaunched ( void * data )
{
	
	GUIWindow ** main_window_ptr = reinterpret_cast <GUIWindow **> ( data );

	* main_window_ptr = GUIWindow::create ( { { 400, 400 }, { 600, 600 } }, GUIWindow::kstyle_titled | GUIWindow::kstyle_resizable | GUIWindow::kstyle_minimizable );
	
	std :: cout << "window: " << ( * main_window_ptr ) << std :: endl;

	if ( ( * main_window_ptr ) != nullptr )
	{
		
		std :: cout << "window allocated successfully!" << std :: endl;
		
		( * main_window_ptr ) -> show ();
		( * main_window_ptr ) -> set_title ( "Hello world!" );
		( * main_window_ptr ) -> add_event_listener ( & Argon::UI::Events::WindowShouldCloseEvent::kevent_should_close, & WindowShouldClose, nullptr );
		( * main_window_ptr ) -> add_event_listener ( & Argon::UI::Events::WindowEvent::kevent_will_close, & WindowWillClose, nullptr );
		
		Context * render_context = ( * main_window_ptr ) -> get_render_context ( true );
		
		if ( render_context != nullptr )
		{
			
			std :: cout << "render" << std :: endl;
			
			render_context -> make_current ();
			
			FrameBuffer * framebuffer = render_context -> get_default_framebuffer ();
			
			FrameBuffer::ClearOptions clear_options;
			clear_options.clear_color_buffer = true;
			clear_options.clear_depth_buffer = false;
			clear_options.red = 0.0;
			clear_options.green = 0.0;
			clear_options.blue = 1.0;
			clear_options.alpha = 1.0;
			framebuffer -> clear ( clear_options );
			
			render_context -> flush_back_buffer ();
			
			framebuffer -> deref ();
			
		}
		
	}
	
};

OSAL_BUILD_MAIN_METHOD( AppEntry );
