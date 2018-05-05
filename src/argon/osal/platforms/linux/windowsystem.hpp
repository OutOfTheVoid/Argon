#ifndef ARGON_OSAL_PLATFORMS_LINUX_WINDOWSYSTEM_HPP
#define ARGON_OSAL_PLATFORMS_LINUX_WINDOWSYSTEM_HPP

#include <argon/osal/targets.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

#include <argon/cpp_util.hpp>

#include <argon/osal/platforms/linux/linux.hpp>

#include <argon/memory/refcounted.hpp>
#include <argon/geometry/geometry.hpp>
#include <argon/rendering/backends/opengl/opengl.hpp>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <argon/ui/ui.hpp>

namespace Argon::OSAL::Linux
{
	
	using Argon::Memory::RefCounted;
	using Argon::Geometry::Rect;
	
	class LinuxGLContext : private cpp_nocopy, public RefCounted, public virtual Rendering::OpenGL::IGLContext/*, public virtual Rendering::OpenGL::IGLContext*/
	{
	public:
		
		enum Version
		{
			
			kversion_legacy,
			kversion_3_2,
			kversion_4_1
			
		};
		
		static LinuxGLContext * create ( Version version, GLXFBConfig framebuffer_config );
		
	private:
		
		LinuxGLContext ( GLXContext context );
		
		GLXContext context;
		
	};
	
	class LinuxWindow : public RefCounted, private cpp_nocopy
	{
	public:
		
		enum BackBufferDepth
		{
			
			kbackbuffer_depth_0 = 0,
			kbackbuffer_depth_16 = 16,
			kbackbuffer_depth_24 = 24
			
		};
		
		static LinuxWindow * create_gl ( const Rect & content_rect, unsigned int style_flags, LinuxGLContext::Version gl_version_minimum, BackBufferDepth back_buffer_depth = kbackbuffer_depth_24 );
		
		void set_title ( const String & title );
		void show ();
		void set_fullscreen ( bool fullscreen );
		
		LinuxGLContext * get_opengl_context ();
		
	private:
		
		LinuxWindow ( Window window_instance, Display * display, GLXFBConfig framebuffer_config, LinuxGLContext::Version gl_version );
		~LinuxWindow ();
		
		Window window_instance;
		Display * display;
		GLXFBConfig framebuffer_config;
		LinuxGLContext::Version gl_version;
		LinuxGLContext * gl_context;
		
	};
	
	class LinuxGLContext;
	
	class LinuxApplication : private cpp_nocopy
	{
	public:
		
		static LinuxApplication * get_shared_instance ();
		
	private:
		
		friend class LinuxGLContext;
		friend class LinuxWindow;
		friend void Argon::UI::application_runloop ( ApplicationInitOptions & init_options );
		
		LinuxApplication ( const LinuxApplication & copy ) = delete;
		
		LinuxApplication ( Display * display, Window root_window, int default_screen );
		~LinuxApplication ();
		
		Display * display;
		Window root_window;
		int default_screen;
		
		static LinuxApplication * shared_instance;
		
	};
	
}

#endif
#endif
