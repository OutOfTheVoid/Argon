#include <argon/ui/events/uievents.hpp>
#include <argon/ui/guiwindow.hpp>
#include <argon/rendering/context.hpp>

const Argon::Events::EventDefinition Argon::UI::Events::WindowShouldCloseEvent::kevent_should_close ( "gw_should_close" );
const Argon::Events::EventDefinition Argon::UI::Events::WindowEvent::kevent_will_close ( "gw_will_close" );
const Argon::Events::EventDefinition Argon::UI::Events::RenderEvent::kevent_render ( "ui_render" );

Argon::UI::Events::WindowShouldCloseEvent::WindowShouldCloseEvent ( GUIWindow * source_window ):
	WindowEvent ( & kevent_should_close, source_window ),
	close_canceled ( false )
{
};

Argon::UI::Events::WindowShouldCloseEvent::~WindowShouldCloseEvent ()
{
}

void Argon::UI::Events::WindowShouldCloseEvent::cancel_close ()
{
	
	close_canceled = true;
	
}

bool Argon::UI::Events::WindowShouldCloseEvent::was_close_cancelled () const
{
	
	return close_canceled;
	
}

Argon::UI::Events::WindowEvent::WindowEvent ( const EventDefinition * definition, GUIWindow * source_window ):
	Event ( definition ),
	source_window ( source_window )
{
	
	if ( source_window != nullptr )
		source_window -> ref ();
	
}

Argon::UI::Events::WindowEvent::~WindowEvent ()
{
	
	if ( source_window != nullptr )
		source_window -> deref ();
	
}

Argon::UI::GUIWindow * Argon::UI::Events::WindowEvent::get_source_window ()
{
	
	return source_window;
	
}

const Argon::UI::GUIWindow * Argon::UI::Events::WindowEvent::get_source_window () const
{
	
	return source_window;
	
}

Argon::UI::Events::RenderEvent::RenderEvent ( GUIWindow * source_window, Context * source_context ):
	WindowEvent ( & kevent_render, source_window ),
	source_context ( source_context )
{
		
	if ( source_context != nullptr )
		source_context -> ref ();
	
};

Argon::UI::Events::RenderEvent::~RenderEvent ()
{
		
	if ( source_context != nullptr )
		source_context -> deref ();
	
}

Argon::Rendering::Context * Argon::UI::Events::RenderEvent::get_source_context ()
{
	
	return source_context;
	
}

const Argon::Rendering::Context * Argon::UI::Events::RenderEvent::get_source_context () const
{
	
	return source_context;
	
}
