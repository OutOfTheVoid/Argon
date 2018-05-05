#include <argon/osal/targets.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

#include <argon/osal/platforms/linux/windowsystem.hpp>


Argon::OSAL::Linux::LinuxWindow::LinuxWindow ( Window window_instance, Display * display, GLXFBConfig framebuffer_config, LinuxGLContext::Version gl_version ):
	RefCounted ( 1 ),
	window_instance ( window_instance ),
	display ( display ),
	framebuffer_config ( framebuffer_config ),
	gl_version ( gl_version ),
	gl_context ( nullptr )
{
};

Argon::OSAL::Linux::LinuxWindow::~LinuxWindow ()
{
	
	XDestroyWindow ( display, window_instance );
	
};

#include <iostream>

Argon::OSAL::Linux::LinuxWindow * Argon::OSAL::Linux::LinuxWindow::create_gl ( const Rect & content_rect, unsigned int style_flags, LinuxGLContext::Version gl_version_minimum, BackBufferDepth back_buffer_depth )
{
	
	LinuxApplication * application_instance = LinuxApplication::get_shared_instance ();
	
	std :: cout << "application_instance: " << application_instance << std :: endl;
	
	if ( application_instance == nullptr )
		return nullptr;
	
	GLint gl_attributes [] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	
	/*==============================================================================*/
	/* Choosing the XVisualInfo                                                     */
	/*------------------------------------------------------------------------------*/
	static int visual_attribs [] = 
	{
		
		GLX_X_RENDERABLE, True,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, back_buffer_depth,
		GLX_STENCIL_SIZE, 8,
		GLX_DOUBLEBUFFER, True,
		None
		
	};
	
	int frame_buffer_config_count = 0;
	GLXFBConfig * frame_buffer_configs = glXChooseFBConfig ( application_instance -> display, application_instance -> default_screen, visual_attribs, & frame_buffer_config_count );
	
	if ( ( frame_buffer_configs == nullptr ) || ( frame_buffer_config_count == 0 ) )
		return nullptr;
		
	int best_framebuffer_index = 0;
	bool multisample_buffers_available = false;
	int best_sample_count = 0;
	
	for ( int i = 0; i < frame_buffer_config_count; i ++ )
	{
		
		XVisualInfo * visual_info = glXGetVisualFromFBConfig ( application_instance -> display, frame_buffer_configs [ i ] );
		
		if ( visual_info )
		{
			
			int sample_buffers = 0;
			int samples = 0;
			
			glXGetFBConfigAttrib ( application_instance -> display, frame_buffer_configs [ i ], GLX_SAMPLE_BUFFERS, & sample_buffers );
			glXGetFBConfigAttrib ( application_instance -> display, frame_buffer_configs [ i ], GLX_SAMPLES, & samples );
			
			if ( sample_buffers != 0 )
			{
				
				if ( samples > best_sample_count )
				{
					
					best_sample_count = samples;
					best_framebuffer_index = i;
					
				}
				
			}
			
		}
		
		XFree ( visual_info );
		
	}
	
	GLXFBConfig best_framebuffer_config = frame_buffer_configs [ best_framebuffer_index ];
	
	/*==============================================================================*/
	
	XVisualInfo * visual_info = glXGetVisualFromFBConfig ( application_instance -> display, best_framebuffer_config );
	Colormap color_map = XCreateColormap ( application_instance -> display, application_instance -> root_window, visual_info -> visual, AllocNone );
	
	XSetWindowAttributes window_attributes;
	window_attributes.colormap = color_map;
	window_attributes.event_mask = ExposureMask | KeyPressMask;
	
	Window window_instance = XCreateWindow (
		application_instance -> display,
		application_instance -> root_window,
		0, 0,
		400, 400,
		0, visual_info -> depth, InputOutput, visual_info -> visual, CWColormap | CWEventMask, & window_attributes );
	
	
	return new LinuxWindow ( window_instance, application_instance -> display, best_framebuffer_config, gl_version_minimum );
	
};

Argon::OSAL::Linux::LinuxGLContext * Argon::OSAL::Linux::LinuxWindow::get_opengl_context ()
{
	
	if ( gl_context == nullptr )
		gl_context = LinuxGLContext::create ( gl_version, framebuffer_config );
	
	return gl_context;
	
}

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
		
		int default_screen = DefaultScreen ( display );
		Window root_window = DefaultRootWindow ( display );
		
		shared_instance = new LinuxApplication ( display, root_window, default_screen );
		
	}
	
	return shared_instance;
	
};

Argon::OSAL::Linux::LinuxApplication::LinuxApplication ( Display * display, Window root_window, int default_screen ):
	display ( display ),
	root_window ( root_window ),
	default_screen ( default_screen )
{
};

Argon::OSAL::Linux::LinuxApplication::~LinuxApplication ()
{
	
	XCloseDisplay ( display );
	
};

#include <iostream>

Argon::OSAL::Linux::LinuxGLContext * Argon::OSAL::Linux::LinuxGLContext::create ( Version version, GLXFBConfig framebuffer_config )
{
	
	LinuxApplication * application_instance = LinuxApplication::get_shared_instance ();
	
	std :: cout << "a" << std :: endl;
	
	int version_major = 0;
	int version_minor = 0;
	
	switch ( version )
	{
		
		case kversion_legacy:
		{
			
			version_major = 2;
			version_minor = 0;
			
		}
		break;
		
		case kversion_3_2:
		{
			
			version_major = 3;
			version_minor = 2;
			
		}
		break;
		
		case kversion_4_1:
		{
			
			version_major = 4;
			version_minor = 1;
			
		}
		break;
		
		default:
			return nullptr;
		
	}
	
	int glx_version_major = 0;
	int glx_version_minor = 0;
	
	if ( ! glXQueryVersion ( application_instance -> display, & glx_version_major, & glx_version_minor ) )
		return nullptr;
		
	std :: cout << "b: " << glx_version_major << ", " << glx_version_minor << std :: endl;
	
	if ( ( glx_version_major < version_major ) || ( ( glx_version_minor < version_minor ) && ( glx_version_major == version_major ) ) )
		return nullptr;
		
	std :: cout << "c" << std :: endl;
	
	PFNGLXCREATECONTEXTATTRIBSARBPROC create_context_attribs_fn = nullptr;
	create_context_attribs_fn = reinterpret_cast <PFNGLXCREATECONTEXTATTRIBSARBPROC> ( glXGetProcAddressARB ( reinterpret_cast<const GLubyte *> ("glXCreateContextAttribsARB" ) ) );
	
	if ( create_context_attribs_fn != nullptr )
	{
		
		String extension_string ( reinterpret_cast<const char *> ( glXQueryExtensionsString ( application_instance -> display, application_instance -> default_screen ) ) );
		Array<String> extension_strings = extension_string.split ( " " );
		
		for ( int i = 0; i < extension_strings.get_length (); i ++ )
			std :: cout << "GLX Extension string: " << std :: endl;
		
	}
	else
	{
		
		std :: cout << "glXCreateContextAttribsARB null" << std :: endl;
		
	}
	
	//String extension_string ( glXQueryExtensionsString ( application_instance -> display, DefaultScreen ( Display ) ) );
	
	return nullptr;
	
}

#endif
