#include <argon/osal/targets.h>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

#include <argon/osal/platforms/windows/windowsystem.h>

WNDCLASSEX Argon::OSAL::Windows::WinWindow::window_class_inst = { 0 };
bool Argon::OSAL::Windows::WinWindow::window_class_inst_initialized = false;
ATOM Argon::OSAL::Windows::WinWindow::window_class_atom;

const wchar_t ARGON_OSAL_PLATFORMS_WINDOWS_WINDOW_CLASS_NAME []  = L"Argon_OSAL_Windows_WinWindow";

WNDCLASSEX & Argon::OSAL::Windows::WinWindow::get_window_class_instance()
{

	if ( ! window_class_inst_initialized )
	{

		memset ( (void *) &window_class_inst, 0, sizeof ( window_class_inst ) );

		window_class_inst.cbSize = sizeof ( WNDCLASSEX );
		window_class_inst.style         = 0;
		window_class_inst.cbClsExtra    = 0;
		window_class_inst.cbWndExtra    = 0;
		window_class_inst.lpfnWndProc = & window_proc;
		window_class_inst.hInstance = argon_osal_platforms_windows_get_application_hinstance ();
		window_class_inst.lpszClassName = ARGON_OSAL_PLATFORMS_WINDOWS_WINDOW_CLASS_NAME;

		RegisterClassEx ( & window_class_inst );

		window_class_inst_initialized = true;

	}

	return window_class_inst;

};

Argon::OSAL::Windows::WinWindow * Argon::OSAL::Windows::WinWindow::create ( Argon::Geometry::Rect content_rect, uint32_t style_flags )
{

	get_window_class_instance ();

	WinWindow * window_instance = new WinWindow ();

	window_instance -> ex_style_flags = WS_EX_CLIENTEDGE;
	window_instance -> style_flags = WS_OVERLAPPEDWINDOW;

	HWND window_handle = CreateWindowExW (
		window_instance -> ex_style_flags,
		ARGON_OSAL_PLATFORMS_WINDOWS_WINDOW_CLASS_NAME,
		L"Argon",
		window_instance -> style_flags,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, argon_osal_platforms_windows_get_application_hinstance (), NULL
	);

	if ( window_handle == NULL )
	{

		delete window_instance;
		return nullptr;

	}

	window_instance -> window_handle = window_handle;

	return window_instance;

};

Argon::OSAL::Windows::WinWindow::WinWindow ():
	RefCounted ( 1 ),
	window_handle ( nullptr ),
	fullscreen ( false ),
	style_flags ( 0 ),
	ex_style_flags ( 0 ),
	window_rect ()
{
};

Argon::OSAL::Windows::WinWindow::~WinWindow ()
{

	DestroyWindow ( window_handle );

};

void Argon::OSAL::Windows::WinWindow::show ( bool activating )
{

	if ( activating )
		ShowWindow ( window_handle, SW_SHOWNORMAL );
	else
		ShowWindow ( window_handle, SW_SHOWNOACTIVATE );

};

void Argon::OSAL::Windows::WinWindow::set_title ( const Argon::String & title )
{

	std::basic_string<char16_t> std_str_title ( title );
	SetWindowText ( window_handle, (LPCWSTR) std_str_title.c_str () );

}

bool Argon::OSAL::Windows::WinWindow::set_fullscreen ( bool fullscreen )
{

	if ( this->fullscreen == fullscreen )
		return true;

	if ( fullscreen )
	{

		style_flags = GetWindowLong ( window_handle, GWL_STYLE );
		ex_style_flags = GetWindowLong ( window_handle, GWL_EXSTYLE );
		GetWindowRect ( window_handle, & window_rect );

		SetWindowLong ( window_handle, GWL_STYLE, ( style_flags | WS_POPUP | WS_VISIBLE ) & ~ ( WS_CAPTION | WS_THICKFRAME ) );
		SetWindowLong ( window_handle, GWL_EXSTYLE, ex_style_flags & ~ ( WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_STATICEDGE ) );

		HMONITOR monitor = MonitorFromWindow ( window_handle, MONITOR_DEFAULTTONEAREST );
		MONITORINFO monitor_info;
		monitor_info.cbSize = sizeof ( monitor_info );
		GetMonitorInfo ( monitor, & monitor_info );

		RECT window_rect = monitor_info.rcMonitor;
		SetWindowPos ( window_handle, NULL, window_rect.left, window_rect.top, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED );

	}
	else
	{

		SetWindowLong ( window_handle, GWL_STYLE, style_flags );
		SetWindowLong ( window_handle, GWL_EXSTYLE, ex_style_flags );
		SetWindowPos ( window_handle, NULL, window_rect.left, window_rect.top, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED );

	}

};

LRESULT CALLBACK Argon::OSAL::Windows::WinWindow::window_proc ( HWND window_handle, UINT message, WPARAM message_w_param, LPARAM message_l_param )
{

	return DefWindowProc ( window_handle, message, message_w_param, message_l_param );

};

#endif
