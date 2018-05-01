#ifndef ARGON_OSAL_PLATFORMS_LINUX_WINDOWSYSTEM_HPP
#define ARGON_OSAL_PLATFORMS_LINUX_WINDOWSYSTEM_HPP

#include <argon/osal/targets.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

#include <argon/cpp_util.hpp>

#include <argon/osal/platforms/linux/linux.hpp>

#include <argon/memory/refcounted.hpp>
#include <argon/geometry/geometry.hpp>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <argon/ui/ui.hpp>

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
