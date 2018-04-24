#include <argon/ui/guiwindow.h>

#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)

Argon::UI::GUIWindow * Argon::UI::GUIWindow::create ( const Rect & content_frame, GUIWindowStyle style )
{
	
	using OSAL::MacOSX::MacWindow;
	
	// This is only necessary before OS 10.10
	if ( OSAL::MacOSX::MacApplication::get_shared_instance () == nullptr )
		return nullptr;
	
	MacWindow * mac_window_instance = MacWindow::create ( content_frame, style );
	
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

#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
#else
#endif

Argon::UI::GUIWindow :: ~GUIWindow ()
{
	
	os_window -> Deref (); // this should be all we ever need to do here.
	
}


