#ifndef ARGON_ARRAY_HPP
#define ARGON_ARRAY_HPP

#include <stddef.h>
#include <algorithm>

/*
*===============================*
* Argon::Array<T> - basic array *
*===============================*
* Argon fixed-size array wrapper
* which simply keeps track of
* the array's length for
* (slightly) more safe array
* usage and auxiliary
* functionality.
*/

namespace Argon
{
	
	template <typename T>
	class Array
	{
	public:
		
		enum NO_INIT
		{
			NoInit
		};
		
		// construct an empty/null array. (no-op)
		inline Array ( NO_INIT no_init ):
			length ( 0 ),
			elements ( nullptr )
		{
		}
		
		// construct an array with <length> elements
		inline Array ( size_t length ):
			length ( length ),
			elements ( new T [ length ] )
		{
		};
		
		// move constructor
		inline Array ( Array<T> && moved ):
			length ( moved.length ),
			elements ( moved.elements )
		{
			
			moved.length = 0;
			moved.elements = nullptr;
			
		};
		
		// move operator
		inline void operator= ( Array<T> && moved )
		{
			
			elements = nullptr;
			length = 0;
			
			std::swap ( elements, moved.elements );
			std::swap ( length, moved.length );
			
		}
		
		// convert raw-c-style array to wrapped array - allocating
		Array ( const T * values, size_t length ):
			length ( length ),
			elements ( new T [ length ] )
		{
			
			for ( size_t i = 0; i < length; i ++ )
				elements [ i ] = values [ i ];
			
		};
		
		// copy constructor
		Array ( const Array<T> & copy ):
			length ( copy.length ),
			elements ( new T [ length ] )
		{
			
			for ( size_t i = 0; i < length; i ++ )
				elements [ i ] = copy.elements [ i ];
			
		};
		
		static inline Array<T> && create_from_c_array_owned ( T * array, size_t length )
		{
			
			Array out_array ( NoInit );
			out_array.elements = array;
			out_array.length = length;
			
			return std::move ( out_array );
			
		}
		
		// destructor
		~Array ()
		{
			
			delete[] elements;
			
		}
		
		// get array length
		inline size_t get_length () const
		{
			
			return length;
			
		}
		
		// array accessor - const
		inline const T & operator[] ( size_t index ) const
		{
			
			return elements [ index ];
			
		};
		
		// array accessor
		inline T & operator[] ( size_t index )
		{
			
			return elements [ index ];
			
		};
		
	private:
		
		T * elements;
		size_t length;
		
	};
	
};

#endif
