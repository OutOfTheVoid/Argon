#ifndef ARGON_RESULT_HPP
#define ARGON_RESULT_HPP

#include <argon/panic.hpp>
#include <argon/string.hpp>
#include <string>

/*
*=================================================*
* Argon::Result<T, E>: Result container           *
*=================================================*
* Argon::Result is a basic container for the
* return value of a function which might have
* failed - it contains either a value (of type T),
* or an error (of type ERROR).
*
* The value/error can be retrieved using the
* associated getters, but be warned - accessing
* a value when it's actually an error is undefined.
* If you're 100% sure that you won't get an error,
* (such as after checking is_error ()),
* then use the get_value_unchecked () getter,
* otherwise, you can use expect_value (), which
* will panic if the value you were expecting was
* actually an error. Alternatively, you can use
* get_value_or, which will return an alternative
* value if the result was an error.
*/

namespace Argon
{
	
	template <typename T, typename ERROR>
	class Result
	{
	public:
		
		Result ( T value ):
			is_err ( false ),
			data ( value )
		{
		};
		
		Result ( ERROR error ):
			is_err ( true ),
			data ( error )
		{
		}
		
		Result ( const Result<T, ERROR> & copy ):
			is_err ( copy.is_err )
		{
			
			if ( is_err )
				this -> data.error = copy.error;
			else
				this -> data.value = copy.value;
			
		};
		
		~Result ()
		{
			
			if ( is_err )
				( & this -> data.error ) -> ~ERROR ();
			else
				( & this -> data.value ) -> ~T ();
			
		};
		
		bool is_error () const
		{
			
			return is_err;
			
		};
		
		T & get_value_unchecked ()
		{
			
			return data.value;
			
		};
		
		const T & get_value_unchecked () const
		{
			
			return data.value;
			
		};
		
		ERROR & get_error_unchecked ()
		{
			
			return data.error;
			
		};
		
		const ERROR & get_error_unchecked () const
		{
			
			return data.error;
			
		};
		
		T & expect_value ()
		{
			
			if ( is_err )
			{
				
				String error_string ( "Argon::Result::expect_value (): expected value on error: " );
				error_string.append ( data.error.get_message () );
				
				std::string std_str_error_message = error_string;
				
				panic ( std_str_error_message.c_str () );
				
			}
			
		}
		
		ERROR & expect_error ()
		{
			
			if ( ! is_err )
			{
				
				String error_string ( "Argon::Result::expect_error (): expected error on value!" );
				std::string std_str_error_message = error_string;
				
				panic ( std_str_error_message.c_str () );
				
			}
			
			return data.error;
			
		}
		
		const T & expect_value () const
		{
			
			if ( is_err )
			{
				
				String error_string ( "Argon::Result::expect_value (): expected value on error: " );
				error_string.append ( data.error.get_message () );
				
				std::string std_str_error_message = error_string;
				
				panic ( std_str_error_message.c_str () );
				
			}
			
		}
		
		const ERROR & expect_error () const
		{
			
			if ( ! is_err )
			{
				
				String error_string ( "Argon::Result::expect_error (): expected error on value!" );
				std::string std_str_error_message = error_string;
				
				panic ( std_str_error_message.c_str () );
				
			}
			
			return data.error;
			
		}
		
		T & get_value_or ( T & alternative )
		{
			
			if ( is_err )
				return alternative;
			
			return data.value;
			
		}
		
		const T & get_value_or ( const T & alternative ) const
		{
			
			if ( is_err )
				return alternative;
			
			return data.value;
			
		}
		
	private:
		
		union DataUnion
		{
			
			DataUnion ( T value ): value ( value ) {};
			DataUnion ( ERROR error ): error ( error ) {};
			~DataUnion () {};
			
			T value;
			ERROR error;
			
		} data;
		
		bool is_err;
		
	};
	
};

#endif
