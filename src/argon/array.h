#ifndef ARGON_ARRAY_H
#define ARGON_ARRAY_H

#include <cstddef>
#include <utility>

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
		
		Array ( NO_INIT no_init ):
			length ( 0 ),
			elements ( nullptr )
		{
		}
		
		Array ( size_t length ):
			length ( length ),
			elements ( new T [ length ] )
		{
		};
		
		Array ( Array<T> && moved ):
			length ( moved.length ),
			elements ( moved.elements )
		{
			
			moved.length = 0;
			moved.elements = nullptr;
			
		};
		
		void operator= ( Array<T> && moved )
		{
			
			std::swap ( elements, moved.elements );
			std::swap ( length, moved.length );
			
		}
		
		Array ( const T * values, size_t length ):
			length ( length ),
			elements ( new T [ length ] )
		{
			
			for ( size_t i = 0; i < length; i ++ )
				elements [ i ] = values [ i ];
			
		};
		
		Array ( const Array<T> & copy ):
			length ( copy.length ),
			elements ( new T [ length ] )
		{
			
			for ( size_t i = 0; i < length; i ++ )
				elements [ i ] = copy.elements [ i ];
			
		};
		
		~Array ()
		{
			
			delete elements;
			
		}
		
		size_t GetLength () const
		{
			
			return length;
			
		}
		
		const T & operator[] ( size_t index ) const
		{
			
			return elements [ index ];
			
		};
		
		T & operator[] ( size_t index )
		{
			
			return elements [ index ];
			
		};
		
	private:
		
		T * elements;
		size_t length;
		
	};
	
};

#endif
