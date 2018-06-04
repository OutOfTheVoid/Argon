#include <argon/ui/guiwindow.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/ui/events/uievents.hpp>
#include <argon/rendering/context.hpp>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)

Argon::UI::GUIWindow * Argon::UI::GUIWindow::create ( const Rect & content_frame, GUIWindowStyle style )
{
	
	using OSAL::MacOSX::MacWindow;
	
	// This is only necessary before OS 10.10
	if ( OSAL::MacOSX::MacApplication::get_shared_instance () == nullptr )
		return nullptr;
	
	MacWindow * mac_window_instance = MacWindow::create ( content_frame, style | MacWindow::kstyle_closable );
	
	if ( mac_window_instance == nullptr )
		return nullptr;
	
	return new GUIWindow ( mac_window_instance );
	
};

Argon::UI::GUIWindow::GUIWindow ( Argon::OSAL::MacOSX::MacWindow * os_window ):
	RefCounted ( 1 ),
	EventDispatcher (),
	os_window ( os_window ),
	rendering_context ( nullptr )
#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
	,
	gl_view ( nullptr ),
	drawing_gl_context ( nullptr )
#endif
{
	
	os_window -> set_should_close_handler ( should_close_event_dispatcher, reinterpret_cast<void *> ( this ) );
	os_window -> set_will_close_handler ( will_close_event_dispatcher, reinterpret_cast<void *> ( this ) );
	
};

void Argon::UI::GUIWindow::show ()
{
	
	os_window -> make_key_and_order_front ();
	
};

void Argon::UI::GUIWindow::set_title ( const String & title )
{
	
	os_window -> set_title ( title );
	
};

void Argon::UI::GUIWindow::set_fullscreen ( bool fullscreen )
{
	
	os_window -> set_fullscreen ( fullscreen );
		
};

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
void Argon::UI::GUIWindow::backing_gl_view_render ( OSAL::MacOSX::MacGLView * gl_view, void * data )
{
	
	GUIWindow * this_window = reinterpret_cast <GUIWindow *> ( data );
	
	
	
}
#endif

Argon::Rendering::Context * Argon::UI::GUIWindow::get_render_context ( bool temporary )
{
	
	if ( rendering_context != nullptr )
		return rendering_context;
	
	#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
	if ( gl_view == nullptr )
		gl_view = OSAL::MacOSX::MacGLView::create ( OSAL::MacOSX::MacGLView::kversion_4_1, { { 0, 0 }, { 600, 600 } } );
	
	if ( ( drawing_gl_context == nullptr ) && ( gl_view != nullptr ) )
	{
		
		drawing_gl_context = OSAL::MacOSX::MacGLContextObj::create_share_context ( gl_view -> get_context_obj () );
		
		if ( drawing_gl_context != nullptr )
			gl_view -> set_draw_callback ( & backing_gl_view_render, reinterpret_cast<void *> ( this ) );
		
	}
	
	if ( ( gl_view == nullptr ) || ( drawing_gl_context == nullptr ) )
		return nullptr;
	else
		os_window -> set_view ( gl_view );
	
	rendering_context = Rendering::Context::create_from_gl_context ( & gl_view -> get_context_obj () );
	#endif
	
	if ( ( rendering_context != nullptr ) && ( ! temporary) )
		rendering_context -> Ref ();
	
	return rendering_context;
	
}

#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

#if (ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

Argon::UI::GUIWindow::GUIWindow ( OSAL::Linux::LinuxWindow * os_window ):
	RefCounted ( 1 ),
	EventDispatcher (),
	os_window ( os_window ),
	rendering_context ( nullptr )
{
};

Argon::UI::GUIWindow * Argon::UI::GUIWindow::create ( const Rect & content_frame, GUIWindowStyle style )
{
	
	using OSAL::Linux::LinuxWindow;
	using OSAL::Linux::LinuxGLContext;
	
	
	#if (ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
	LinuxWindow * os_window = LinuxWindow::create_gl ( content_frame, 0, LinuxGLContext::kversion_3_2 );
	#endif // TODO: Implement this for the dummy rendering backend...
	
	if ( os_window == nullptr )
		return nullptr;
	
	return new GUIWindow ( os_window );
	
}

void Argon::UI::GUIWindow::show ()
{
	
	os_window -> show ();
	
};

void Argon::UI::GUIWindow::set_title ( const String & title )
{
	
	os_window -> set_title ( title );
	
};

void Argon::UI::GUIWindow::set_fullscreen ( bool fullscreen )
{
	
	// TODO: Implement
	
};

Argon::Rendering::Context * Argon::UI::GUIWindow::get_render_context ( bool temporary )
{
	
	if ( rendering_context != nullptr )
		return rendering_context;
		
	#if (ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
	
	using OSAL::Linux::LinuxGLContext;
	
	LinuxGLContext * linxu_gl_context = os_window -> get_opengl_context ();
	
	if ( linxu_gl_context == nullptr)
		return nullptr;
	
	rendering_context = Argon::Rendering::Context::create_from_gl_context ( linxu_gl_context );
	return rendering_context;
	
	#else
	
	rendering_context = new Argon::Rendering::Context ();
	return rendering_context;
	
	#endif
	
}

#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

Argon::UI::GUIWindow * Argon::UI::GUIWindow::create(const Rect & content_frame, GUIWindowStyle style)
{
	
	using OSAL::Windows::WinWindow;

	WinWindow * os_window = WinWindow::create ( content_frame, 0 );

	if ( os_window != nullptr )
		return new GUIWindow ( os_window );

	return nullptr;

};

Argon::UI::GUIWindow::GUIWindow ( Argon::OSAL::Windows::WinWindow * os_window ):
	RefCounted ( 1 ),
	EventDispatcher (),
	os_window ( os_window )
{
};

void Argon::UI::GUIWindow::show()
{

	os_window -> show ( true );

};

void Argon::UI::GUIWindow::set_title(const String & title)
{

	os_window -> set_title ( title );

};

void Argon::UI::GUIWindow::set_fullscreen ( bool fullscreen )
{

	os_window -> set_fullscreen ( fullscreen );

};

#else
#endif

Argon::UI::GUIWindow::~GUIWindow ()
{
	
	os_window -> Deref (); // this should be all we ever need to do here.
	
	if ( rendering_context != nullptr )
		rendering_context -> Deref ();
	
	#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
	#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
	if ( gl_view != nullptr )
	{
		
		gl_view -> set_draw_callback ( nullptr, nullptr );
		gl_view -> Deref ();
		
	}
	#endif
	#endif
	
}

bool Argon::UI::GUIWindow::should_close_event_dispatcher ( void * data )
{
	
	GUIWindow * window = reinterpret_cast<GUIWindow *> ( data );
	
	UI::Events::WindowShouldCloseEvent * window_should_close_event = new UI::Events::WindowShouldCloseEvent ( window );
	
	window -> dispatch_event ( window_should_close_event );
	bool cancel = window_should_close_event -> was_close_cancelled ();
	window_should_close_event -> Deref ();
	
	return ! cancel;
	
}

void Argon::UI::GUIWindow::will_close_event_dispatcher ( void * data )
{
	
	GUIWindow * window = reinterpret_cast<GUIWindow *> ( data );
	
	UI::Events::WindowEvent * window_will_close_event = new UI::Events::WindowEvent ( & UI::Events::WindowEvent::kevent_will_close, window );
	
	window -> dispatch_event ( window_will_close_event );
	
	window_will_close_event -> Deref ();
	
}
