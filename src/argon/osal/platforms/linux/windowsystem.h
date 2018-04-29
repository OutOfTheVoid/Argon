#ifndef ARGON_OSAL_PLATFORMS_LINUX_WINDOWSYSTEM_H
#define ARGON_OSAL_PLATFORMS_LINUX_WINDOWSYSTEM_H

#include <argon/osal/osal.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

#include <argon/cpp_util.h>

#include <argon/osal/platforms/linux/linux.h>

#include <argon/memory/refcounted.h>
#include <argon/geometry/geometry.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <argon/ui/ui.h>

namespace Argon::OSAL::Linux
{
	
	using Argon::Memory::RefCounted;
	using Argon::Geometry::Rect;
	
	class LinuxWindow : public RefCounted, private cpp_nocopy
	{
	public:
		
		static LinuxWindow * create ( const Rect & content_rect, unsigned int style_flags );
		
		void set_title ( const String & title );
		void show ();
		void set_fullscreen ( bool fullscreen );
		
	private:
		
		LinuxWindow ( Window window_instance, Display * display );
		~LinuxWindow ();
		
		Window window_instance;
		Display * display;
		
	};
	
	class LinuxApplication : private cpp_nocopy
	{
	public:
		
		static LinuxApplication * get_shared_instance ();
		
	private:
		
		friend class LinuxWindow;
		friend void Argon::UI::application_runloop ( ApplicationInitOptions & init_options );
		
		LinuxApplication ( const LinuxApplication & copy ) = delete;
		
		LinuxApplication ( Display * display, Window root_window );
		~LinuxApplication ();
		
		Display * display;
		Window root_window;
		
		static LinuxApplication * shared_instance;
		
	};
	
}

#endif
#endif
