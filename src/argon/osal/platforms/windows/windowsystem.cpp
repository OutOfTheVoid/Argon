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

	HWND window_handle = CreateWindowExW (
		WS_EX_CLIENTEDGE,
		ARGON_OSAL_PLATFORMS_WINDOWS_WINDOW_CLASS_NAME,
		L"Argon",
		WS_OVERLAPPEDWINDOW,
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
	window_handle ( nullptr )
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

LRESULT CALLBACK Argon::OSAL::Windows::WinWindow::window_proc ( HWND window_handle, UINT message, WPARAM message_w_param, LPARAM message_l_param )
{

	return DefWindowProc ( window_handle, message, message_w_param, message_l_param );

};
