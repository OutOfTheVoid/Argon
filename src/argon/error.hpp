#ifndef ARGON_ERROR_HPP
#define ARGON_ERROR_HPP

#include <argon/string.hpp>

/*
*=======================================*
* Argon::Error: a basic error class     *
*=======================================*
* Argon::Error is the base class for all
* high-level error reporting in Argon.
* 
* It simply contains an error message,
* and serves as a base class for more
* complex error values.
*/

namespace Argon
{
	
	class Error
	{
	public:
		
		// constructor
		Error ();
		
		// message constructor
		Error ( const String & Message );
		
		// copy constructor
		Error ( const Error & Copy );
		
		// move constructor
		Error ( Error && Moved );
		
		// destructor
		~Error ();
		
		// get the error message
		const String & get_message () const;
		
	private:
		
		String Message;
		
	};
	
};

#endif
