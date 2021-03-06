#include <argon/osal/targets.h>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)

#include <argon/osal/platforms/macosx/windowsystem.hpp>
#include <argon/osal/platforms/macosx/windowsystem_common.h>

extern "C" void argon_osal_macosx_windowsystem_release ( ObjcID object );

extern "C" ObjcID argon_osal_macosx_macapplication_getsharedinstance ( ObjcID * delegate_instance );
extern "C" void argon_osal_macosx_macapplication_set_activation_policy ( unsigned int activation_policy );
extern "C" void argon_osal_macosx_macapplication_set_did_finish_launching_callback ( void ( * callback ) ( void * ), void * data );
extern "C" void argon_osal_macosx_macapplication_run ();
extern "C" void argon_osal_macosx_macapplication_stop ();

extern "C" ObjcID argon_osal_macosx_macmenu_create_0 ();
extern "C" ObjcID argon_osal_macosx_macmenu_create_1 ( const char * title );

extern "C" ObjcID argon_osal_macosx_macwindow_create_1 ( Argon_OSAL_MacOSX_WindowSystem_Rect content_rect, uint32_t style_flags, ObjcID * window_controller_instance, ObjcID * window_delegate_instance );
extern "C" void argon_osal_macosx_macwindow_order_front ( ObjcID ns_window_instance, bool regardless_of_application_focus );
extern "C" void argon_osal_macosx_macwindow_make_key_and_order_front ( ObjcID ns_window_instance );
extern "C" void argon_osal_macosx_macwindow_set_view ( ObjcID ns_window_instance, ObjcID view_instance );
extern "C" void argon_osal_macosx_macwindow_set_title ( ObjcID ns_window_instance, const char * title );
extern "C" void argon_osal_macosx_macwindow_get_frame ( ObjcID ns_window_instance, Argon_OSAL_MacOSX_WindowSystem_Rect * frame_rect );
extern "C" void argon_osal_macosx_macwindow_set_frame ( ObjcID ns_window_instance, Argon_OSAL_MacOSX_WindowSystem_Rect frame_rect );
extern "C" void argon_osal_macosx_macwindow_set_window_level_plus ( ObjcID ns_window_instance, uint32_t level, uint32_t addition );
extern "C" void argon_osal_macosx_macwindow_set_frame_to_screen ( ObjcID ns_window_instance );
extern "C" void argon_osal_macosx_macwindow_set_hides_on_deactivate ( id ns_window_instance, bool hides_on_deactivate );

extern "C" void argon_osal_macosx_macwindow_delegate_set_callbacks ( ObjcID ns_window_delegate_instance, const Argon_OSAL_MacOSX_WindowSystem_WindowDelegate_Event_Callbacks * callbacks );

extern "C" ObjcID argon_osal_macosx_openglview_create ( unsigned int version, Argon_OSAL_MacOSX_WindowSystem_Rect frame_rect, ObjcID * ns_opengl_context_obj_instance );
extern "C" void argon_osal_macosx_openglview_set_draw_callback ( ObjcID ns_opengl_view_instance, void ( * callback )( void * ), void * callback_data );
extern "C" void argon_osal_macosx_openglview_set_resize_callback ( id ns_opengl_view_instance, void ( * callback )( void *, GLint, GLint, GLsizei, GLsizei ), void * callback_data );
extern "C" void argon_osal_macosx_openglview_update ( ObjcID ns_opengl_view_instance );

extern "C" void argon_osal_macosx_opengl_context_make_current ( ObjcID ns_opengl_context_obj_instance );
extern "C" void argon_osal_macosx_opengl_context_flush ( ObjcID ns_opengl_context_obj_instance );
extern "C" ObjcID argon_osal_macosx_opengl_context_create_share ( ObjcID ns_opengl_context_obj_share );

Argon::OSAL::MacOSX::MacApplication * Argon::OSAL::MacOSX::MacApplication::shared_instance = nullptr;

Argon::OSAL::MacOSX::MacApplication::MacApplication ( ObjcID ns_application_instance, ObjcID application_delegate_instance ):
	ns_application_instance ( ns_application_instance ),
	application_delegate_instance ( application_delegate_instance )
{
};

Argon::OSAL::MacOSX::MacApplication::~MacApplication ()
{
	
	argon_osal_macosx_windowsystem_release ( application_delegate_instance );
	
};

void Argon::OSAL::MacOSX::MacApplication::set_activation_policy ( ActivationPolicy activation_policy )
{
	
	argon_osal_macosx_macapplication_set_activation_policy ( static_cast<unsigned int> ( activation_policy ) );
	
}

void Argon::OSAL::MacOSX::MacApplication::run () const
{
	
	argon_osal_macosx_macapplication_run ();
	
};

void Argon::OSAL::MacOSX::MacApplication::stop () const
{
	
	argon_osal_macosx_macapplication_stop ();
	
}

Argon::OSAL::MacOSX::MacApplication * Argon::OSAL::MacOSX::MacApplication::get_shared_instance ()
{
	
	if ( shared_instance == nullptr )
	{
		
		ObjcID application_delegate_instance = nullptr;
		ObjcID ns_application_instance = argon_osal_macosx_macapplication_getsharedinstance ( & application_delegate_instance );
		
		if ( ns_application_instance == nullptr )
			return nullptr;
		
		shared_instance = new MacApplication ( ns_application_instance, application_delegate_instance );
		
	}
	
	return shared_instance;
	
};

void Argon::OSAL::MacOSX::MacApplication::set_application_did_finish_launching_callback ( void ( * callback ) ( void * ), void * data )
{
	
	argon_osal_macosx_macapplication_set_did_finish_launching_callback ( callback, data );
	
};

Argon::OSAL::MacOSX::MacMenu::MacMenu ()
{
	
	ns_menu_instance = argon_osal_macosx_macmenu_create_0 ();
	
};

Argon::OSAL::MacOSX::MacMenu::MacMenu ( String & title )
{
	
	std::string std_string_title = title;
	ns_menu_instance = argon_osal_macosx_macmenu_create_1 ( std_string_title.c_str () );
	
};

Argon::OSAL::MacOSX::MacMenu::~MacMenu ()
{
	
	argon_osal_macosx_windowsystem_release ( ns_menu_instance );
	
};

Argon::OSAL::MacOSX::MacWindow * Argon::OSAL::MacOSX::MacWindow::create ( const Rect & window_rect, uint32_t style_mask )
{
	
	Argon_OSAL_MacOSX_WindowSystem_Rect objc_window_rect;
	objc_window_rect.x = window_rect.origin.x;
	objc_window_rect.y = window_rect.origin.y;
	objc_window_rect.width = window_rect.size.x;
	objc_window_rect.height = window_rect.size.y;
	
	Argon_OSAL_MacOSX_WindowSystem_WindowDelegate_Event_Callbacks callbacks;
	callbacks.window_should_close_handler = nullptr;
	callbacks.window_should_close_handler_data = nullptr;
	
	ObjcID ns_window_controller_instance = nullptr;
	ObjcID ns_window_delegate_instance = nullptr;
	ObjcID ns_window_instance = argon_osal_macosx_macwindow_create_1 ( objc_window_rect, style_mask, & ns_window_controller_instance, & ns_window_delegate_instance );
	
	if ( ns_window_instance == nullptr )
		return nullptr;
		
	return new MacWindow ( ns_window_instance, ns_window_controller_instance, ns_window_delegate_instance );
	
};

void Argon::OSAL::MacOSX::MacWindow::order_front ( bool regardless_of_application_focus )
{
	
	argon_osal_macosx_macwindow_order_front ( ns_window_instance, regardless_of_application_focus );
	
};

void Argon::OSAL::MacOSX::MacWindow::make_key_and_order_front ()
{
	
	argon_osal_macosx_macwindow_make_key_and_order_front ( ns_window_instance );
	
};

void Argon::OSAL::MacOSX::MacWindow::set_view ( IMacWindowView * view_virt )
{
	
	ObjcID view_instance = nullptr;
	
	if ( this -> view != nullptr )
	{
		
		this -> view -> deref ();
		this -> view = nullptr;
		
	}
	
	switch ( view_virt -> get_view_type () )
	{
		
		case IMacWindowView::ktype_gl:
		{
			
			this -> view = view_virt;
			
			MacGLView * gl_view = dynamic_cast<MacGLView *> ( view_virt );
			
			gl_view -> ref ();
			
			view_instance = gl_view -> ns_opengl_view_instance;
			
		}
		break;
			
		default:
			return;
		
	}
	
	argon_osal_macosx_macwindow_set_view ( ns_window_instance, view_instance );
	
};

Argon::OSAL::MacOSX::MacWindow::MacWindow ( ObjcID ns_window_instance, ObjcID ns_window_controller_instance, ObjcID ns_window_delegate_instnace ):
	RefCounted ( 1 ),
	ns_window_instance ( ns_window_instance ),
	ns_window_controller_instance ( ns_window_controller_instance ),
	ns_window_delegate_instance ( ns_window_delegate_instnace ),
	non_fullscreen_rect (),
	fullscreen ( false ),
	view ( nullptr ),
	should_close_event_handler ( nullptr ),
	should_close_event_handler_data ( nullptr )
{
	
	Argon_OSAL_MacOSX_WindowSystem_WindowDelegate_Event_Callbacks callbacks;
	callbacks.window_should_close_handler = & should_close_handler;
	callbacks.window_should_close_handler_data = reinterpret_cast <void *> ( this );
	callbacks.window_will_close_handler = & will_close_handler;
	callbacks.window_will_close_handler_data = reinterpret_cast <void *> ( this );
	
	argon_osal_macosx_macwindow_delegate_set_callbacks ( ns_window_delegate_instance, & callbacks );
	
};

Argon::OSAL::MacOSX::MacWindow::~MacWindow ()
{
	
	if ( view != nullptr )
	{
		
		view -> deref ();
		view = nullptr;
		
	}
	
	argon_osal_macosx_windowsystem_release ( ns_window_controller_instance );
	argon_osal_macosx_windowsystem_release ( ns_window_instance );
	argon_osal_macosx_windowsystem_release ( ns_window_delegate_instance );
	
};

void Argon::OSAL::MacOSX::MacWindow::set_title ( const String & title )
{
	
	std::string std_string_title ( title );
	argon_osal_macosx_macwindow_set_title ( ns_window_instance, std_string_title.c_str () );
	
}

void Argon::OSAL::MacOSX::MacWindow::set_fullscreen ( bool fullscreen )
{
	
	if ( this -> fullscreen != fullscreen )
	{
		
		if ( fullscreen )
		{
			
			argon_osal_macosx_macwindow_get_frame ( ns_window_instance, & non_fullscreen_rect );
			argon_osal_macosx_macwindow_set_window_level_plus ( ns_window_instance, MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_MAIN_MENU, 1 );
			argon_osal_macosx_macwindow_set_frame_to_screen ( ns_window_instance );
			argon_osal_macosx_macwindow_set_hides_on_deactivate ( ns_window_instance, true );
			
		}
		else
		{
			
			argon_osal_macosx_macwindow_set_window_level_plus ( ns_window_instance, MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_NORMAL, 0 );
			argon_osal_macosx_macwindow_set_frame ( ns_window_instance, non_fullscreen_rect );
			argon_osal_macosx_macwindow_set_hides_on_deactivate ( ns_window_instance, false );
			
		}
		
	}
	
}

void Argon::OSAL::MacOSX::MacWindow::set_should_close_handler ( bool ( * handler ) ( void * data ), void * handler_data )
{
	
	should_close_event_handler = handler;
	should_close_event_handler_data = handler_data;
	
}

bool Argon::OSAL::MacOSX::MacWindow::should_close_handler ( void * data )
{
	
	MacWindow * window = reinterpret_cast<MacWindow *> ( data );
	
	if ( window -> should_close_event_handler )
		return window -> should_close_event_handler ( window -> should_close_event_handler_data );
	
	return true;
	
}

void Argon::OSAL::MacOSX::MacWindow::set_will_close_handler ( void ( * handler ) ( void * data ), void * handler_data )
{
	
	will_close_event_handler = handler;
	will_close_event_handler_data = handler_data;
	
}

void Argon::OSAL::MacOSX::MacWindow::will_close_handler ( void * data )
{
	
	MacWindow * window = reinterpret_cast<MacWindow *> ( data );
	
	if ( window -> will_close_event_handler )
		return window -> will_close_event_handler ( window -> will_close_event_handler_data );
	
}

Argon::OSAL::MacOSX::MacGLView * Argon::OSAL::MacOSX::MacGLView::create ( Version version, Rect frame )
{
	
	Argon_OSAL_MacOSX_WindowSystem_Rect objc_frame_rect;
	objc_frame_rect.x = frame.origin.x;
	objc_frame_rect.y = frame.origin.y;
	objc_frame_rect.width = frame.size.x;
	objc_frame_rect.height = frame.size.y;
	
	ObjcID ns_opengl_context_obj_instance = nullptr;
	ObjcID ns_opengl_view_instance = argon_osal_macosx_openglview_create ( version, objc_frame_rect, & ns_opengl_context_obj_instance );
	
	if ( ns_opengl_view_instance == nullptr )
		return nullptr;
	
	MacGLView * view_instance = new MacGLView ( ns_opengl_view_instance, ns_opengl_context_obj_instance );
		
	argon_osal_macosx_openglview_set_draw_callback ( ns_opengl_view_instance, & draw_callback_marshaller, reinterpret_cast <void *> ( view_instance ) );
	argon_osal_macosx_openglview_set_resize_callback ( ns_opengl_view_instance, & resize_callback_marshaller, reinterpret_cast <void *> ( view_instance ) );
	
	return view_instance;
	
};

void Argon::OSAL::MacOSX::MacGLView::draw_callback_marshaller ( void * data )
{
	
	MacGLView * view = reinterpret_cast <MacGLView *> ( data );
	
	if ( view -> draw_callback )
		view -> draw_callback ( view, view -> draw_callback_data );
	
};

#include <iostream>

void Argon::OSAL::MacOSX::MacGLView::resize_callback_marshaller ( void * data, GLint x, GLint y, GLsizei width, GLsizei height )
{
	
	std :: cout << "resize_callback_marshaller" << std :: endl;
	
	MacGLView * view = reinterpret_cast <MacGLView *> ( data );
	
	if ( view -> resize_callback )
		view -> resize_callback ( view, x, y, width, height, view -> resize_callback_data );
	
}

Argon::OSAL::MacOSX::MacGLView::~MacGLView ()
{
	
	argon_osal_macosx_windowsystem_release ( ns_opengl_view_instance );
	
};

Argon::OSAL::MacOSX::MacGLView::MacGLView ( ObjcID ns_opengl_view_instance, ObjcID ns_opengl_context_obj_instance ):
	RefCounted ( 1 ),
	ns_opengl_view_instance ( ns_opengl_view_instance ),
	gl_context_obj ( ns_opengl_context_obj_instance ),
	draw_callback_data ( nullptr ),
	draw_callback ( nullptr ),
	resize_callback_data ( nullptr ),
	resize_callback ( nullptr )
{
};

Argon::OSAL::MacOSX::MacGLContextObj & Argon::OSAL::MacOSX::MacGLView::get_context_obj ()
{
	
	return gl_context_obj;
	
};

const Argon::OSAL::MacOSX::MacGLContextObj & Argon::OSAL::MacOSX::MacGLView::get_context_obj () const
{
	
	return gl_context_obj;
	
};

Argon::OSAL::MacOSX::IMacWindowView::Type Argon::OSAL::MacOSX::MacGLView::get_view_type () const
{
	
	return IMacWindowView::ktype_gl;
	
};

void Argon::OSAL::MacOSX::MacGLView::set_draw_callback ( void ( * callback )( MacGLView * gl_view, void * data ), void * data )
{
	
	this -> draw_callback_data = data;
	this -> draw_callback = callback;
	
}


void Argon::OSAL::MacOSX::MacGLView::set_resize_callback ( void ( * callback )( MacGLView * gl_view, GLint x, GLint y, GLsizei width, GLsizei height, void * data ), void * data )
{
	
	this -> resize_callback_data = data;
	this -> resize_callback = callback;
	
}

void Argon::OSAL::MacOSX::MacGLView::update ()
{
	
	argon_osal_macosx_openglview_update ( ns_opengl_view_instance );
	
}

Argon::OSAL::MacOSX::MacGLContextObj::MacGLContextObj ( ObjcID ns_opengl_context_obj_instance ):
	RefCounted ( 1 ),
	ns_opengl_context_obj_instance ( ns_opengl_context_obj_instance )
{
};

Argon::OSAL::MacOSX::MacGLContextObj::~MacGLContextObj ()
{
};

void Argon::OSAL::MacOSX::MacGLContextObj::make_current () const
{
	
	argon_osal_macosx_opengl_context_make_current ( ns_opengl_context_obj_instance );
	
}

void Argon::OSAL::MacOSX::MacGLContextObj::flush_back_buffer () const
{
	
	argon_osal_macosx_opengl_context_flush ( ns_opengl_context_obj_instance );
	
}

Argon::OSAL::MacOSX::MacGLContextObj * Argon::OSAL::MacOSX::MacGLContextObj::create_share_context ( Argon::OSAL::MacOSX::MacGLContextObj & share )
{
	
	ObjcID new_context_id = argon_osal_macosx_opengl_context_create_share ( share.ns_opengl_context_obj_instance );
	
	if ( new_context_id == nullptr )
		return nullptr;
	
	return new MacGLContextObj ( new_context_id );
	
}

#include <dlfcn.h>
#include <iostream>

void * Argon::OSAL::MacOSX::MacGLContextObj::void_gl_get_proc_address ( const String & gl_symbol ) const
{
	
	std::string std_string_gl_symbol = gl_symbol;
	
	static void * opengl_lib_image = nullptr;
	
	if ( opengl_lib_image == nullptr )
	{
		
		opengl_lib_image = dlopen ( "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY );
	
		if ( opengl_lib_image == nullptr )
			return nullptr;
			
	}
	
	return dlsym ( opengl_lib_image, std_string_gl_symbol.c_str () );
	
}

#endif
