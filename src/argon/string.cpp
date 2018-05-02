#include <argon/string.hpp>

Argon::String::String ():
	chars ()
{
};

Argon::String::String ( NO_INIT no_init ):
	chars ( Vector<char32_t>::NoInit )
{
}

Argon::String::String ( const char * c_string ):
	chars ( strlen ( c_string ) )
{
	
	size_t length = chars.get_capacity ();
	size_t index = 0;
	
	while ( index < length )
	{
		
		uint32_t code = static_cast<uint32_t> ( c_string [ index ] ); 
		
		if ( code < 0x80 )
		{
			
			chars.push ( static_cast <char32_t> ( code ) );
			index ++;
			
			continue;
			
		}
		
		if ( code < 0xE0 )
		{
			
			code = ( code & 0x1F ) << 6;
			code |= static_cast <uint32_t> ( c_string [ index + 1 ] ) & 0x3F;
			
			chars.push ( code );
			index += 2;
			
			continue;
			
		}
		
		if ( code < 0xF0 )
		{
			
			code = ( code & 0x0F ) << 12;
			code |= ( static_cast <uint32_t> ( c_string [ index + 1 ] ) & 0x3F ) << 6;
			code |= static_cast <uint32_t> ( c_string [ index + 2 ] ) & 0x3F;
			
			chars.push ( code );
			index += 3;
			
			continue;
			
		}
		
		{
			
			code = ( code & 0x0F ) << 18;
			code |= ( static_cast <uint32_t> ( c_string [ index + 1 ] ) & 0x3F ) << 12;
			code |= ( static_cast <uint32_t> ( c_string [ index + 2 ] ) & 0x3F ) << 6;
			code |= static_cast <uint32_t> ( c_string [ index + 3 ] ) & 0x3F;
			
			chars.push ( code );
			index += 4;
			
			continue;
			
		}
		
	}
	
};

Argon::String::String ( const char16_t * w_string ):
	chars ( std::char_traits<char16_t>::length ( w_string ) )
{
	
	size_t length = chars.get_capacity ();
	size_t index = 0;
	
	while ( index < length )
	{
		
		uint32_t code = static_cast<uint32_t> ( w_string [ index ] ); 
		
		if ( ( code & 0xF800 ) == 0xD800 )
		{
			
			chars.push ( static_cast <char32_t> ( ( ( code & 0x03FF ) << 10 ) | ( w_string [ index + 1 ] & 0x03FF ) ) );
			index += 2;
			
			continue;
			
		}
		
		{
			
			chars.push ( static_cast <char32_t> ( code ) );
			index ++;
			
		}
		
	}
	
};

Argon::String::String ( const char32_t * l_string ):
	chars ( std::char_traits<char32_t>::length ( l_string ) )
{
	
	size_t length = chars.get_capacity ();
	
	for ( size_t i = 0; i < length; i ++ )
		chars.push ( static_cast <char32_t> ( l_string [ i ] ) );
	
};

Argon::String::String ( const char * c_string, size_t length ):
	chars ( length )
{
	
	size_t index = 0;
	
	while ( index < length )
	{
		
		uint32_t code = static_cast<uint32_t> ( c_string [ index ] ); 
		
		if ( code < 0x80 )
		{
			
			chars.push ( static_cast <char32_t> ( code ) );
			index ++;
			
			continue;
			
		}
		
		if ( code < 0xE0 )
		{
			
			code = ( code & 0x1F ) << 6;
			code |= static_cast <uint32_t> ( c_string [ index + 1 ] ) & 0x3F;
			
			chars.push ( code );
			index += 2;
			
			continue;
			
		}
		
		if ( code < 0xF0 )
		{
			
			code = ( code & 0x0F ) << 12;
			code |= ( static_cast <uint32_t> ( c_string [ index + 1 ] ) & 0x3F ) << 6;
			code |= static_cast <uint32_t> ( c_string [ index + 2 ] ) & 0x3F;
			
			chars.push ( code );
			index += 3;
			
			continue;
			
		}
		
		{
			
			code = ( code & 0x0F ) << 18;
			code |= ( static_cast <uint32_t> ( c_string [ index + 1 ] ) & 0x3F ) << 12;
			code |= ( static_cast <uint32_t> ( c_string [ index + 2 ] ) & 0x3F ) << 6;
			code |= static_cast <uint32_t> ( c_string [ index + 3 ] ) & 0x3F;
			
			chars.push ( code );
			index += 4;
			
			continue;
			
		}
		
	}
	
};

Argon::String::String ( const char16_t * w_string, size_t length ):
	chars ( length )
{
	
	size_t index = 0;
	
	while ( index < length )
	{
		
		uint32_t code = static_cast<uint32_t> ( w_string [ index ] ); 
		
		if ( ( code & 0xF800 ) == 0xD800 )
		{
			
			chars.push ( static_cast <char32_t> ( ( ( code & 0x03FF ) << 10 ) | ( w_string [ index + 1 ] & 0x03FF ) ) );
			index += 2;
			
			continue;
			
		}
		
		{
			
			chars.push ( static_cast <char32_t> ( code ) );
			index ++;
			
		}
		
	}
	
};

Argon::String::String ( const char32_t * l_string, size_t length ):
	chars ( length )
{
	
	for ( size_t i = 0; i < length; i ++ )
		chars.push ( static_cast <char32_t> ( l_string [ i ] ) );
	
};

Argon::String::String ( const std::string & std_string ):
	chars ( std_string.length () )
{
	
	size_t length = std_string.length ();
	size_t index = 0;
	
	while ( index < length )
	{
		
		uint32_t code = static_cast<uint32_t> ( std_string [ index ] ); 
		
		if ( code < 0x80 )
		{
			
			chars.push ( static_cast <char32_t> ( code ) );
			index ++;
			
			continue;
			
		}
		
		if ( code < 0xE0 )
		{
			
			code = ( code & 0x1F ) << 6;
			code |= static_cast <uint32_t> ( std_string [ index + 1 ] ) & 0x3F;
			
			chars.push ( code );
			index += 2;
			
			continue;
			
		}
		
		if ( code < 0xF0 )
		{
			
			code = ( code & 0x0F ) << 12;
			code |= ( static_cast <uint32_t> ( std_string [ index + 1 ] ) & 0x3F ) << 6;
			code |= static_cast <uint32_t> ( std_string [ index + 2 ] ) & 0x3F;
			
			chars.push ( code );
			index += 3;
			
			continue;
			
		}
		
		{
			
			code = ( code & 0x0F ) << 18;
			code |= ( static_cast <uint32_t> ( std_string [ index + 1 ] ) & 0x3F ) << 12;
			code |= ( static_cast <uint32_t> ( std_string [ index + 2 ] ) & 0x3F ) << 6;
			code |= static_cast <uint32_t> ( std_string [ index + 3 ] ) & 0x3F;
			
			chars.push ( code );
			index += 4;
			
			continue;
			
		}
		
	}
	
};

Argon::String::String ( const std::u16string & std_string ):
	chars ( std_string.length () )
{
	
	size_t length = std_string.length ();
	size_t index = 0;
	
	while ( index < length )
	{
		
		uint32_t code = static_cast<uint32_t> ( std_string [ index ] ); 
		
		if ( ( code & 0xF800 ) == 0xD800 )
		{
			
			chars.push ( static_cast <char32_t> ( ( ( code & 0x03FF ) << 10 ) | ( std_string [ index + 1 ] & 0x03FF ) ) );
			index += 2;
			
			continue;
			
		}
		
		{
			
			chars.push ( static_cast <char32_t> ( code ) );
			index ++;
			
		}
		
	}
	
};

bool Argon::String::operator== ( const String & rhs ) const
{
	
	uint32_t count = chars.get_count ();
	
	if ( rhs.get_count () != count )
		return false;
	
	for ( size_t i = 0; i < count; i ++ )
	{
		
		if ( chars [ i ] != rhs.chars [ i ] )
			return false;
		
	}
	
	return true;
	
}

Argon::String::String ( const std::u32string & std_string ):
	chars ( std_string.length () )
{
	
	size_t length = std_string.length ();
	
	for ( size_t i = 0; i < length; i ++ )
		chars.push ( static_cast <char32_t> ( std_string [ i ] ) );
	
};

Argon::String::String ( size_t Capacity ):
	chars ( Capacity )
{
};

const Argon::Vector<char32_t> & Argon::String::get_chars () const
{
	
	return chars;
	
};

Argon::Vector<char32_t> & Argon::String::get_chars ()
{
	
	return chars;
	
};

size_t Argon::String::get_count () const
{
	
	return chars.get_count ();
	
};

void Argon::String::append ( const String & value )
{
	
	chars.push ( value.chars );
	
}

Argon::String Argon::String::sub_string ( size_t index, size_t count ) const
{
	
	size_t src_count = chars.get_count ();
	
	if ( index >= src_count )
		return String ();
		
	size_t remaining_length = src_count - index;
	
	if ( remaining_length < count )
		count = remaining_length;
	
	String out ( count );
	
	for ( size_t i = 0; i < count; i ++ )
		out.chars [ i ] = chars [ i + index ];
	
	return out;
	
}

Argon::String:: operator std::string () const
{
	
	std::string out;
	out.reserve ( chars.get_capacity () );
	
	int index = 0;
	int length = chars.get_count ();
	
	while ( index < length )
	{
		
		uint32_t code = static_cast<uint32_t> ( chars [ index ] );
		index ++;
		
		if ( code < 0x80 )
			out.push_back ( static_cast <char> ( code ) );
		else if ( code < 0x800 )
		{
			
			out.push_back ( static_cast <char> ( ( ( code >> 6 ) & 0x1F ) | 0xC0 ) );
			out.push_back ( static_cast <char> ( ( code & 0x3F ) | 0x80 ) );
			
		}
		else if ( code < 0x10000 )
		{
			
			out.push_back ( static_cast <char> ( ( ( code >> 12 ) & 0x0F ) | 0xE0 ) );
			out.push_back ( static_cast <char> ( ( ( code >> 6 ) & 0x3F ) | 0x80 ) );
			out.push_back ( static_cast <char> ( ( code & 0x3F ) | 0x80 ) );
			
		}
		else
		{
			
			out.push_back ( static_cast <char> ( ( ( code >> 18 ) & 0x07 ) | 0xF0 ) );
			out.push_back ( static_cast <char> ( ( ( code >> 12 ) & 0x3F ) | 0x80 ) );
			out.push_back ( static_cast <char> ( ( ( code >> 6 ) & 0x3F ) | 0x80 ) );
			out.push_back ( static_cast <char> ( ( code & 0x3F ) | 0x80 ) );
			
		}
		
	}
	
	return out;
	
};

Argon::String::operator std::basic_string<char16_t> () const
{

	std::basic_string<char16_t> out;
	out.reserve ( chars.get_capacity () );

	int index = 0;
	int length = chars.get_count ();

	while ( index < length )
	{

		uint32_t code = static_cast<uint32_t> ( chars [ index ] );
		index ++;
		
		if ( code < 0x10000 )
			out.push_back ( static_cast<char16_t> ( code ) );
		else
		{
			
			out.push_back ( static_cast<char16_t> ( ( ( code >> 10 ) & 0x3FF ) | 0xD800 ) );
			out.push_back ( static_cast<char16_t> ( ( code & 0x3FF ) | 0xDC00 ) );
			
		}
		
	}
	
	return out;
};

Argon::String && operator ""_as ( const char * c_string, size_t length )
{
	
	return std::move ( Argon::String ( c_string, length ) );
	
}

std::ostream & operator<< ( std::ostream & ostr, const Argon::String & str )
{
	
	std::string value = static_cast<std::string> ( str );
	ostr << value;
	
	return ostr;
	
};
