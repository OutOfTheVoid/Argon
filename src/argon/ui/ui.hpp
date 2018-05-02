#ifndef ARGON_UI_UI_HPP
#define ARGON_UI_UI_HPP

/*
*====================================================*
* Argon::UI namespace definition                     *
*====================================================*
* Argon::UI contains most of the things relevant to
* making a cross-plaform gui application, including
* a GUIWindow class, which abstracts os-specific
* window objects/handles.
* 
* The most important part of Argon::UI is the
* application_runloop() function, which defines the
* entry point for the cross-platform event loop. this
* is where the application starts interacting with
* the window-manager in order to display and manage
* windows, sound, input and other human-interaction
* related things, and is required for GUI apps to
* function properly, outside of using the os-
* specific backends.
* 
* Note ApplicationInitOptions, a struct which is
* passed to the runloop - it contains some general
* properties of the application that the os might use,
* such as the boolean foreground_app, which tells
* argon to tell the os that we want to operate in the
* foreground as a user-interactible application.
*
*/

namespace Argon::UI
{
	
	typedef struct ApplicationInitOptions_Struct
	{
		
		ApplicationInitOptions_Struct ():
			foreground_app ( true ),
			application_started_callback ( nullptr ),
			application_started_data ( nullptr )
		{
		};
		
		// whether or not we intend to interact with the user in any way
		bool foreground_app;
		
		// the callback called when the operating system has acknowledged our application
		// on some os's this is defined by the application framework, and on others, it happens
		// immediately before the runloop is entered. think of this as where you should begin interacting
		// with the window manager
		void ( * application_started_callback )( void * callback_data );
		void * application_started_data;
		
	} ApplicationInitOptions;
	
	// enter the runloop
	void application_runloop ( ApplicationInitOptions & init_options );
	void application_runloop_exit ();
	
}


#endif
