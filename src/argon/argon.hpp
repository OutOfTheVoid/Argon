#ifndef ARGON_ARGON_HPP
#define ARGON_ARGON_HPP

#include <argon/array.hpp>
#include <argon/error.hpp>
#include <argon/result.hpp>
#include <argon/string.hpp>
#include <argon/vector.hpp>
#include <argon/osal/osal.hpp>
#include <argon/memory/memory.hpp>

/*
*=================================================*
* Argon namespace definition                      *
*=================================================*
* This is the top-level namespace that argon lives
* in. It contains a few utility functions, but the
* core functionality is in lib_init() and
* lib_deinit(), which initialize core components of
* the engine before application logic takes over, 
* and free resources when the appication quits.
*
* Normally, the end-user will not call these
* themselves, instead using the 
* 	OSAL_BUILD_MAIN_METHOD(AppEntry)
* macro to define
* the application's entry point in a cross-platform
* standardized way, however, this is not mandatory.
* To manually implement this functionality, all you
* need to do is initialize argon with
*	lib_init ( <array of program arguments> );
* before using any core functionality, and
* deinitialize it when you are done using the
* library with
*	lib_deinit ();
* . Basic classes such as String and Array
* (by necessity) will work without this, but most
* library functionality is undefined otherwise.
*/

namespace Argon
{
	
	// Initialize argon and os-specific things
	void lib_init ( Array<String> && ProgramArgs );
	
	// Get program arguments
	const Array<String> & GetProgramArgs ();
	
	// Deinitilize argon and free os resources
	void lib_deinit ();
	
};

#endif
