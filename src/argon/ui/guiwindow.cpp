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

#include <iostream>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
void Argon::UI::GUIWindow::backing_gl_view_render ( OSAL::MacOSX::MacGLView * gl_view, void * data )
{
	
	GUIWindow * this_window = reinterpret_cast <GUIWindow *> ( data );
	
	OSAL::MacOSX::MacGLContextObj & gl_view_gl_context = this_window -> gl_view -> get_context_obj ();
	
	gl_view_gl_context.make_current ();
	this_window -> gl_bind_framebuffer ( GL_DRAW_FRAMEBUFFER, 0 );
	this_window -> gl_bind_framebuffer ( GL_READ_FRAMEBUFFER, this_window -> transfer_framebuffer );
	this_window -> gl_blit_framebuffers ( 0, 0, this_window -> transfer_framebuffer_width, this_window -> transfer_framebuffer_height, 0, 0, this_window -> transfer_framebuffer_width, this_window -> transfer_framebuffer_height, GL_COLOR_BUFFER_BIT, GL_NEAREST );
	this_window -> gl_bind_framebuffer ( GL_READ_FRAMEBUFFER, 0 );
	gl_view_gl_context.flush_back_buffer ();
	
	this_window -> rendering_context -> register_external_framebuffer_bind_read_write ();
	
}

void Argon::UI::GUIWindow::backing_gl_view_resize ( OSAL::MacOSX::MacGLView * gl_view, GLint x, GLint y, GLsizei width, GLsizei height, void * data )
{
	
	GUIWindow * this_window = reinterpret_cast <GUIWindow *> ( data );
	
	OSAL::MacOSX::MacGLContextObj & gl_view_gl_context = this_window -> gl_view -> get_context_obj ();
	
	gl_view_gl_context.make_current ();
	this_window -> gl_bind_renderbuffer ( GL_RENDERBUFFER, this_window -> transfer_framebuffer_depth_renderbuffer );
	this_window -> gl_renderbuffer_storage ( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height );
	this_window -> gl_bind_renderbuffer ( GL_RENDERBUFFER, 0 );
	this_window -> gl_bind_texture ( GL_TEXTURE_2D, this_window -> transfer_framebuffer_texture );
	this_window -> gl_tex_image_2d ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 );
	this_window -> gl_viewport ( x, y, width, height );
	
	this_window -> transfer_framebuffer_width = width;
	this_window -> transfer_framebuffer_height = height;
	
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
	
		OSAL::MacOSX::MacGLContextObj & gl_view_gl_context = gl_view -> get_context_obj ();
		
		drawing_gl_context = OSAL::MacOSX::MacGLContextObj::create_share_context ( gl_view_gl_context );
		
		if ( drawing_gl_context == nullptr )
			return nullptr;
		
		drawing_gl_context -> make_current ();
		
		gl_gen_framebuffers = drawing_gl_context -> get_proc_address<decltype ( gl_gen_framebuffers )> ( "glGenFramebuffers" );
		gl_bind_framebuffer = drawing_gl_context -> get_proc_address <decltype ( gl_bind_framebuffer )> ( "glBindFramebuffer" );
		gl_gen_textures = drawing_gl_context -> get_proc_address <decltype ( gl_gen_textures )> ( "glGenTextures" );
		gl_bind_texture = drawing_gl_context -> get_proc_address <decltype ( gl_bind_texture )> ( "glBindTexture" );
		gl_tex_image_2d = drawing_gl_context -> get_proc_address <decltype ( gl_tex_image_2d )> ( "glTexImage2D" );
		gl_tex_parameter_i = drawing_gl_context -> get_proc_address <decltype ( gl_tex_parameter_i )> ( "glTexParameteri" );
		gl_gen_renderbuffers = drawing_gl_context -> get_proc_address <decltype ( gl_gen_renderbuffers )> ( "glGenRenderbuffers" );
		gl_bind_renderbuffer = drawing_gl_context -> get_proc_address <decltype ( gl_bind_renderbuffer )> ( "glBindRenderbuffer" );
		gl_renderbuffer_storage = drawing_gl_context -> get_proc_address <decltype ( gl_renderbuffer_storage )> ( "glRenderbufferStorage" );
		gl_framebuffer_renderbuffer = drawing_gl_context -> get_proc_address <decltype ( gl_framebuffer_renderbuffer )> ( "glFramebufferRenderbuffer" );
		gl_framebuffer_texture = drawing_gl_context -> get_proc_address <decltype ( gl_framebuffer_texture )> ( "glFramebufferTexture" );
		gl_draw_buffers = drawing_gl_context -> get_proc_address <decltype ( gl_draw_buffers )> ( "glDrawBuffers" );
		gl_blit_framebuffers = drawing_gl_context -> get_proc_address <decltype ( gl_blit_framebuffers )> ( "glBlitFramebuffer" );
		gl_check_framebuffer_status = drawing_gl_context -> get_proc_address <decltype ( gl_check_framebuffer_status )> ( "glCheckFramebufferStatus" );
		gl_get_error = drawing_gl_context -> get_proc_address <decltype ( gl_get_error )> ( "glGetError" );
		gl_viewport = drawing_gl_context -> get_proc_address <decltype( gl_viewport )> ( "glViewport" );
		
		gl_gen_framebuffers ( 1, & transfer_framebuffer );
		gl_bind_framebuffer ( GL_FRAMEBUFFER, transfer_framebuffer );
		
		gl_gen_textures ( 1, & transfer_framebuffer_texture );
		gl_bind_texture ( GL_TEXTURE_2D, transfer_framebuffer_texture );
		gl_tex_image_2d ( GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 );
		gl_tex_parameter_i ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		gl_tex_parameter_i ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		
		transfer_framebuffer_width = 600;
		transfer_framebuffer_height = 600;
		
		gl_gen_renderbuffers ( 1, & transfer_framebuffer_depth_renderbuffer );
		gl_bind_renderbuffer ( GL_RENDERBUFFER, transfer_framebuffer_depth_renderbuffer );
		gl_renderbuffer_storage ( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 600, 600 );
		gl_bind_renderbuffer ( GL_RENDERBUFFER, 0 );
		
		gl_framebuffer_renderbuffer ( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, transfer_framebuffer_depth_renderbuffer );
		gl_framebuffer_texture ( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, transfer_framebuffer_texture, 0 );
		
		GLenum draw_buffers [ 1 ] = { GL_COLOR_ATTACHMENT0 };
		gl_draw_buffers ( 1, draw_buffers );
		
	}
	
	if ( ( gl_view == nullptr ) || ( drawing_gl_context == nullptr ) )
		return nullptr;
	else
		os_window -> set_view ( gl_view );
	
	rendering_context = Argon::Rendering::Context::create_from_gl_context ( drawing_gl_context, transfer_framebuffer_texture );
	#endif
	
	if ( ( rendering_context != nullptr ) && ( ! temporary ) )
		rendering_context -> Ref ();
	
	gl_view -> set_draw_callback ( & backing_gl_view_render, reinterpret_cast<void *> ( this ) );
	gl_view -> set_resize_callback ( & backing_gl_view_resize, reinterpret_cast<void *> ( this ) );
	
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
