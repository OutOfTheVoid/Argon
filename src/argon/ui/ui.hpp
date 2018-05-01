#ifndef ARGON_UI_UI_HPP
#define ARGON_UI_UI_HPP

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
		
		bool foreground_app;
		
		void ( * application_started_callback )( void * callback_data );
		void * application_started_data;
		
	} ApplicationInitOptions;
	
	void application_runloop ( ApplicationInitOptions & init_options );
	
}


#endif
