#ifndef ARGON_STRING_H
#define ARGON_STRING_H

#include <string>
#include <argon/vector.h>
#include <stdint.h>

namespace Argon
{

	class String
	{
	public:
		
		enum NO_INIT
		{
			NoInit
		};
		
		String ();
		String ( NO_INIT no_init );
		String ( size_t capacity );
		
		String ( const char * c_string );
		String ( const char16_t * w_string );
		String ( const char32_t * l_string );
		
		String ( const char * c_string, size_t length );
		String ( const char16_t * w_string, size_t length );
		String ( const char32_t * l_string, size_t length );
		
		String ( const std::string & std_string );
		String ( const std::u16string & std_string );
		String ( const std::u32string & std_string );
		
		operator std::basic_string<char> () const;
		
		const Vector<char32_t> & get_chars () const;
		
		size_t get_count () const;
		
		void append ( const String & value );
		
		String sub_string ( size_t index, size_t count );
		
	private:
		
		Vector<char32_t> chars;
		
	};
	
};

Argon::String && operator ""_as ( const char * c_string, size_t length );

#include <ostream>

std::ostream & operator<< ( std::ostream & ostr, const Argon::String & str );

#endif
