#ifndef ARGON_STRING_HPP
#define ARGON_STRING_HPP

#include <string>
#include <cstring>
#include <argon/vector.hpp>
#include <argon/array.hpp>
#include <stdint.h>

/*
*==================================================*
* Argon::String                                    *
*==================================================*
* Argon::String is argon's basic string type.
* It is a container for a UTF32 valid char32_t
* vector (invalid char sequences are undefined
* behavior) with extra functionality related to
* string processing.
*
* Argon works with utf-32 strings in order to
* preserve a 1-1 mapping between string length and
* data size - one codepoint always has length 1.
*
* Of course there is always the tradeoff of
* interacting with ASCII or utf-8 interfaces, but
* ideally an application would not be doing heavy
* lifting with string processing, and if so, would
* use a specialized container for such a task.
*
* That being said, in the case where there must be
* a utf-8 interface (or possibly ASCII) interacting
* with Argon::String, there are cast-operators
* defined for the c++ standard librarie's
* std::string in utf-8, as well as
* std::basic_string<char16_t> in utf-16,
* (which was initially done for windows wide-string
* interop).
*
* In short:
* UTF32 gaurentees language compatibility and 
* codepoint-per length unit coherence, so it was
* chosen as the natural argon string representation
* valuing those properties over speed or memory
* conservation. In the rare case that narrower
* representations are needed, casting is easy.
*/

namespace Argon
{

	class String
	{
	public:
		
		enum NO_INIT
		{
			NoInit
		};
		
		// Default constructor - empty string
		String ();
		
		// initialize an empty string with minimal work - used mostly for move-semantics
		String ( NO_INIT no_init );
		
		// initialize a string with <capacity> capacity for chars.
		String ( size_t capacity );
		
		// convert from a utf-8/ascii c style string
		String ( const char * c_string );
		
		// convert from a utf-16/USC2 c style string
		String ( const char16_t * w_string );
		
		// convert from a utf-32 c style string
		String ( const char32_t * l_string );
		
		// convert from a utf-8/ascii char array and length
		String ( const char * c_string, size_t length );
		
		// convert from a utf-16/USC2 char array and length
		String ( const char16_t * w_string, size_t length );
		
		// convert from a utf-32 char array and length
		String ( const char32_t * l_string, size_t length );
		
		// convert from a std::string
		String ( const std::string & std_string );
		
		// convert from a std::u16string
		String ( const std::u16string & std_string );
		
		// convert from a std::u32string
		String ( const std::u32string & std_string );
		
		// convert to a utf-8 std::string
		operator std::basic_string<char> () const;
		
		// convert to a utf-16 std::u16string
		operator std::basic_string<char16_t> () const;
		
		// get the charachter vector of the string
		// note that modifying chars of the vector in a non-utf32 compatible way is undefined behavior
		const Vector<char32_t> & get_chars () const;
		Vector<char32_t> & get_chars ();
		
		bool operator== ( const String & rhs ) const;
		
		// get the number of charachters
		size_t get_count () const;
		
		// append to the string
		void append ( const String & value );
		
		// get a sub-string of the string
		String && sub_string ( size_t index, size_t count ) const;
		
		// split the string by a seperator
		Array<String> && split ( const String & delimiter, size_t start = 0, size_t length = 0, size_t max_count = 0 );
		
	private:
		
		Vector<char32_t> chars;
		
	};
	
};

// literal operator for argon strings from c-strings
// use as so:
//	Argon::String my_string = "hello world"_as;
Argon::String && operator ""_as ( const char * c_string, size_t length );

#include <ostream>

// definition for operator<< on std::ostream (Allows std::cout <Some Argon::String>).
std::ostream & operator<< ( std::ostream & ostr, const Argon::String & str );

#endif
