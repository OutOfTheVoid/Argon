#ifndef ARGON_UI_GUIWINDOW_H
#define ARGON_UI_GUIWINDOW_H

#include <argon/memory/refcounted.h>
#include <argon/geometry/geometry.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
	#include <argon/osal/platforms/macosx/windowsystem.h>
#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
#else
#endif

namespace Argon::UI
{
	
	using Geometry::Rect;
	
	class GUIWindow : public Argon::Memory::RefCounted
	{
	public:
		
		typedef uint32_t GUIWindowStyle;
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
			static const GUIWindowStyle kstyle_closable = Argon::OSAL::MacOSX::MacWindow::kstyle_closable;
			static const GUIWindowStyle kstyle_minimizable = Argon::OSAL::MacOSX::MacWindow::kstyle_miniaturizable;
			static const GUIWindowStyle kstyle_resizable = Argon::OSAL::MacOSX::MacWindow::kstyle_resizable;
			static const GUIWindowStyle kstyle_framed = Argon::OSAL::MacOSX::MacWindow::kstyle_titled;
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
		#else
		#endif
		
		static GUIWindow * create ( const Rect & content_frame, GUIWindowStyle style );
		
		void show ();
		void set_title ( const String & title );
		
	private:
		
		~GUIWindow ();
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
		
		GUIWindow ( OSAL::MacOSX::MacWindow * os_window );
		
		OSAL::MacOSX::MacWindow * os_window;
		
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
		#else
		#endif
		
	};
	
};

#endif
