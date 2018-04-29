#include <argon/ui/guiwindow.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)

Argon::UI::GUIWindow * Argon::UI::GUIWindow::create ( const Rect & content_frame, GUIWindowStyle style )
{
	
	using OSAL::MacOSX::MacWindow;
	
	// This is only necessary before OS 10.10
	if ( OSAL::MacOSX::MacApplication::get_shared_instance () == nullptr )
		return nullptr;
	
	MacWindow * mac_window_instance = MacWindow::create ( content_frame, style | MacWindow::kstyle_closable );
	
	if ( mac_window_instance == nullptr )
		return nullptr;
	
	return new GUIWindow ( mac_window_instance );
	
};

Argon::UI::GUIWindow::GUIWindow ( Argon::OSAL::MacOSX::MacWindow * os_window ):
	RefCounted ( 1 ),
	os_window ( os_window )
{
};

void Argon::UI::GUIWindow::show ()
{
	
	os_window -> make_key_and_order_front ();
	
};

void Argon::UI::GUIWindow::set_title ( const String & title )
{
	
	os_window -> set_title ( title );
	
};

void Argon::UI::GUIWindow::set_fullscreen ( bool fullscreen )
{
	
	os_window -> set_fullscreen ( fullscreen );
	
};

#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)

Argon::UI::GUIWindow::GUIWindow ( OSAL::Linux::LinuxWindow * os_window ):
	RefCounted ( 1 ),
	os_window ( os_window )
{
};

Argon::UI::GUIWindow * Argon::UI::GUIWindow::create ( const Rect & content_frame, GUIWindowStyle style )
{
	
	using OSAL::Linux::LinuxWindow;
	
	LinuxWindow * os_window = LinuxWindow::create ( content_frame, 0 );
	
	if ( os_window == nullptr )
		return nullptr;
	
	return new GUIWindow ( os_window );
	
}

void Argon::UI::GUIWindow::show ()
{
	
	os_window -> show ();
	
};

void Argon::UI::GUIWindow::set_title ( const String & title )
{
	
	os_window -> set_title ( title );
	
};

void Argon::UI::GUIWindow::set_fullscreen ( bool fullscreen )
{
	
	// TODO: Implement
	
};

#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

Argon::UI::GUIWindow * Argon::UI::GUIWindow::create(const Rect & content_frame, GUIWindowStyle style)
{
	
	using OSAL::Windows::WinWindow;

	WinWindow * os_window = WinWindow::create ( content_frame, 0 );

	if ( os_window != nullptr )
		return new GUIWindow ( os_window );

	return nullptr;

};

Argon::UI::GUIWindow::GUIWindow ( Argon::OSAL::Windows::WinWindow * os_window ):
	RefCounted ( 1 ),
	os_window ( os_window )
{
};

void Argon::UI::GUIWindow::show()
{

	os_window -> show ( true );

};

void Argon::UI::GUIWindow::set_title(const String & title)
{

	os_window -> set_title ( title );

};

void Argon::UI::GUIWindow::set_fullscreen ( bool fullscreen )
{

	os_window -> set_fullscreen ( fullscreen );

};

#else
#endif

Argon::UI::GUIWindow :: ~GUIWindow ()
{
	
	os_window -> Deref (); // this should be all we ever need to do here.
	
}


