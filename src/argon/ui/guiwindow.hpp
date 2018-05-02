#ifndef ARGON_UI_GUIWINDOW_HPP
#define ARGON_UI_GUIWINDOW_HPP

#include <stdint.h>

#include <argon/osal/targets.h>
#include <argon/osal/windowsystem.hpp>

#include <argon/rendering/context.hpp>

#include <argon/memory/refcounted.hpp>
#include <argon/geometry/geometry.hpp>

#include <argon/events/eventdispatcher.hpp>

namespace Argon::UI
{
	
	using Geometry::Rect;
	
	class GUIWindow : public Memory::RefCounted, public Argon::Events::EventDispatcher
	{
	public:
		
		typedef uint32_t GUIWindowStyle;
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
		static const GUIWindowStyle kstyle_minimizable = Argon::OSAL::MacOSX::MacWindow::kstyle_miniaturizable;
		static const GUIWindowStyle kstyle_resizable = Argon::OSAL::MacOSX::MacWindow::kstyle_resizable;
		static const GUIWindowStyle kstyle_titled = Argon::OSAL::MacOSX::MacWindow::kstyle_titled;
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
		static const GUIWindowStyle kstyle_minimizable = 0;
		static const GUIWindowStyle kstyle_resizable = 0;
		static const GUIWindowStyle kstyle_titled = 0;
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
		static const GUIWindowStyle kstyle_minimizable = OSAL::Windows::WinWindow::kstyle_minimizable;
		static const GUIWindowStyle kstyle_maximizable = OSAL::Windows::WinWindow::kstyle_maximizable;
		static const GUIWindowStyle kstyle_titled = OSAL::Windows::WinWindow::kstyle_titled;
		#else
		#endif
		
		static GUIWindow * create ( const Rect & content_frame, GUIWindowStyle style );
		
		void show ();
		void set_title ( const String & title );
		void set_fullscreen ( bool fullscreen );
		
		Rendering::Context * get_render_context ( bool temporary );
		
	private:
		
		static bool should_close_event_dispatcher ( void * data );
		static void will_close_event_dispatcher ( void * data );
		
		~GUIWindow ();
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
		
		GUIWindow ( OSAL::MacOSX::MacWindow * os_window );
		
		OSAL::MacOSX::MacWindow * os_window;
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		OSAL::MacOSX::MacGLView * gl_view;
		#endif
		
		Rendering::Context * rendering_context;
		
		#endif
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
		
		GUIWindow ( OSAL::Linux::LinuxWindow * os_window );
		
		OSAL::Linux::LinuxWindow * os_window;
		
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

		GUIWindow ( OSAL::Windows::WinWindow * os_window );

		OSAL::Windows::WinWindow * os_window;

		#else
		#endif
		
	};
	
};

#endif
