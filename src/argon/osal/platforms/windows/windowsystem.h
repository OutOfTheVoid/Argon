#ifndef ARGON_OSAL_PLATFORMS_WINDOWS_WINDOWSYSTEM_H
#define ARGON_OSAL_PLATFORMS_WINDOWS_WINDOWSYSTEM_H

#include <argon/osal/platforms/windows/windows.h>

#include <argon/geometry/geometry.h>
#include <argon/memory/refcounted.h>

namespace Argon::OSAL::Windows
{

	class WinWindow : public Argon::Memory::RefCounted
	{
	public:

		static const uint32_t kstyle_thin_border = WS_BORDER;
		static const uint32_t kstyle_maximizable = WS_MAXIMIZEBOX;
		static const uint32_t kstyle_minimizable = WS_MINIMIZEBOX;
		static const uint32_t kstyle_titled = WS_SYSMENU;

		static WinWindow * create ( Argon::Geometry::Rect content_rect, uint32_t style_flags );

		void show ( bool activating );
		void set_title ( const String & title );
		bool set_fullscreen ( bool fullscreen );

	private:

		WinWindow ();
		~WinWindow ();
		
		HWND window_handle;

		DWORD style_flags;
		DWORD ex_style_flags;
		RECT window_rect;
		bool fullscreen;

		static LRESULT CALLBACK window_proc ( HWND window_handle, UINT message, WPARAM message_w_param, LPARAM message_l_param );

		static WNDCLASSEX & get_window_class_instance ();
		static WNDCLASSEX window_class_inst;
		static bool window_class_inst_initialized;
		static ATOM window_class_atom;

	};

}

#endif
