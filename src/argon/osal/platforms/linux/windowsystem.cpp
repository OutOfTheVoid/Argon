#include <argon/osal/osal.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

#include <argon/osal/platforms/linux/windowsystem.h>


Argon::OSAL::Linux::LinuxWindow::LinuxWindow ( Window window_instance, Display * display ):
	RefCounted ( 1 ),
	window_instance ( window_instance ),
	display ( display )
{
};

Argon::OSAL::Linux::LinuxWindow::~LinuxWindow ()
{
	
	XDestroyWindow ( display, window_instance );
	
};

#include <iostream>

Argon::OSAL::Linux::LinuxWindow * Argon::OSAL::Linux::LinuxWindow::create ( const Argon::Geometry::Rect & content_rect, unsigned int style_flags )
{
	
	LinuxApplication * application_instance = LinuxApplication::get_shared_instance ();
	
	std :: cout << "application_instance: " << application_instance << std :: endl;
	
	if ( application_instance == nullptr )
		return nullptr;
	
	int screen = DefaultScreen ( application_instance -> display );
	
	GLint gl_attributes [] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, True };
	
	XVisualInfo * visual_info = glXChooseVisual ( application_instance -> display, screen, gl_attributes );
	
	Colormap color_map = XCreateColormap ( application_instance -> display, application_instance -> root_window, visual_info -> visual, AllocNone );
	
	XSetWindowAttributes window_attributes;
	window_attributes.event_mask = ExposureMask | KeyPressMask;
	window_attributes.colormap = color_map;
	
	Window window_instance = XCreateWindow (
		application_instance -> display,
		application_instance -> root_window,
		0, 0,
		400, 400,
		0, visual_info -> depth, InputOutput, visual_info -> visual, CWColormap | CWEventMask, & window_attributes );
	
	
	return new LinuxWindow ( 0, application_instance -> display );
	
};

void Argon::OSAL::Linux::LinuxWindow::set_title ( const String & title )
{
	
	std::string std_str_title = title;
	
	XStoreName ( display, window_instance, std_str_title.c_str () );
	
};

void Argon::OSAL::Linux::LinuxWindow::show ()
{
	
	XMapWindow ( display, window_instance );
	
};

void Argon::OSAL::Linux::LinuxWindow::set_fullscreen ( bool fullscreen )
{
	
	
	
};

Argon::OSAL::Linux::LinuxApplication * Argon::OSAL::Linux::LinuxApplication::shared_instance = nullptr;

Argon::OSAL::Linux::LinuxApplication * Argon::OSAL::Linux::LinuxApplication::get_shared_instance ()
{
	
	if ( shared_instance == nullptr )
	{
		
		Display * display = XOpenDisplay ( NULL );
		
		if ( display == nullptr )
			return nullptr;
		
		Window root_window = DefaultRootWindow ( display );
		
		shared_instance = new LinuxApplication ( display, root_window );
		
	}
	
	return shared_instance;
	
};

Argon::OSAL::Linux::LinuxApplication::LinuxApplication ( Display * display, Window root_window ):
	display ( display ),
	root_window ( root_window )
{
};

Argon::OSAL::Linux::LinuxApplication::~LinuxApplication ()
{
	
	XCloseDisplay ( display );
	
};

#endif
