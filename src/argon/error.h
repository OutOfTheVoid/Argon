#ifndef ARGON_ERROR_H
#define ARGON_ERROR_H

#include <argon/string.h>

namespace Argon
{
	
	class Error
	{
	public:
		
		Error ();
		Error ( const String & Message );
		Error ( const Error & Copy );
		Error ( Error && Moved );
		~Error ();
		
		const String & GetMessage ();
		
	private:
		
		String Message;
		
	};
	
};

#endif
