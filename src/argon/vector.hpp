#ifndef ARGON_VECTOR_HPP
#define ARGON_VECTOR_HPP

/*
*==================================================*
* Argon::Vector<T>                                 *
*==================================================*
* Argon::Vector<T> is the basic dynamic array
* type in argon, allowing for easy dynamic array
* behavior.
*
*/

#include <argon/array.hpp>

namespace Argon
{
	
	template <typename T>
	class Vector
	{
	public:
		
		enum NO_INIT
		{
			NoInit
		};
		
		enum MOVE
		{
			Move
		};
		
		// empty/minimal init constructor - mostly useful for swapping.
		Vector ( NO_INIT no_init ):
			capacity ( 0 ),
			count ( 0 ),
			elements ( nullptr )
		{
		};
		
		// default constructor - allocates a store of 100 elements by defailt.
		Vector ():
			capacity ( 100 ),
			count ( 0 ),
			elements ( new T [ capacity ] )
		{
		};
		
		// sized constructor - allocate space for <capacity> elements initially.
		Vector ( size_t capacity ):
			capacity ( capacity ),
			count ( 0 ),
			elements ( new T [ capacity ] )
		{
		};
		
		// c-style array constructor - convert a c style array to an Argon::Vector
		Vector ( T * elements, size_t count ):
			capacity ( count ),
			count ( 0 ),
			elements ( new T [ capacity ] )
		{
			
			if ( elements != nullptr )
			{
				
				for ( size_t i = 0; i < count; i ++ )
					this -> elements [ i ] = elements [ i ];
				
				this -> count = capacity;
				
			}
			
		};
		
		Vector ( MOVE move, T * elements, size_t count ):
			capacity ( count ),
			count ( 0 ),
			elements ( new T [ capacity ] )
		{
			
			if ( elements != nullptr )
			{
				
				for ( size_t i = 0; i < count; i ++ )
					this -> elements [ i ] = std::move ( elements [ i ] );
				
				this -> count = count;
				
			}
			
			
		};
		
		// c-style array constructor - convert a c style array to an Argon::Vector with room for <additional_capacity> extra elements
		Vector ( T * elements, size_t count, size_t additional_capacity ):
			capacity ( count + additional_capacity ),
			count ( count ),
			elements ( new T [ capacity ] )
		{
			
			for ( size_t i = 0; i < count; i ++ )
				this -> elements [ i ] = elements [ i ];
			
		};
		
		// copy constructor
		Vector ( const Vector<T> & elements ):
			capacity ( elements.capacity ),
			count ( elements.count ),
			elements ( new T [ elements.capacity ] )
		{
			
			for ( size_t i = 0; i < elements.count; i ++ )
				this -> elements [ i ] = elements.elements [ i ];
			
		};
		
		// move constructor
		Vector ( Vector<T> && moved ):
			capacity ( moved.capacity ),
			count ( moved.count ),
			elements ( moved.elements )
		{
			
			moved.elements = nullptr;
			moved.count = 0;
			moved.capacity = 0;
			
		};
		
		// move operator
		void operator= ( Vector<T> && moved )
		{
			
			std::swap ( elements, moved.elements );
			std::swap ( count, moved.count );
			std::swap ( capacity, moved.capacity );
			
		};
		
		// copy constructor plus - copy of the vector <elements> with <additional_capacity> extra elements of storage
		Vector ( const Vector<T> & elements, size_t additional_capacity ):
			capacity ( elements.capacity + additional_capacity ),
			count ( elements.count ),
			elements ( new T [ capacity ] )
		{
			
			for ( size_t i = 0; i < elements.count; i ++ )
				this -> elements [ i ] = elements.elements [ i ];
			
		};
		
		// get the count of the vector
		size_t get_count () const
		{
			
			return count;
			
		};
		
		// get the capacity of the vector
		size_t get_capacity () const
		{
			
			return capacity;
			
		};
		
		// raw element accessor
		const T & operator[] ( size_t index ) const
		{
			
			return elements [ index ];
			
		};
		
		T & operator[] ( size_t index )
		{
			
			return elements [ index ];
			
		};
		
		void add_at ( T value, size_t index )
		{
			
			if ( count >= capacity )
				DoubleCapacity ();
			
			if ( index >= count )
				index = count - 1;
			
			for ( size_t i = count; i > index; i -- )
				elements [ i ] = elements [ i - 1 ];
			
			elements [ index ] = value;
			count ++;
			
		}
		
		// push a value onto the vector, allocating more room if necessary
		void push ( T value )
		{
			
			if ( count >= capacity )
				DoubleCapacity ();
			
			elements [ count ] = value;
			count ++;
			
		};
		
		void push ( MOVE move, T && value )
		{
			
			if ( count >= capacity )
				DoubleCapacity ();
			
			elements [ count ] = std::move ( value );
			count ++;
			
		};
		
		// pop an element off the vector
		T pop ()
		{
			
			count --;
			return elements [ count ];
			
		};
		
		// peek at the top element of the vector
		T & peek ()
		{
			
			return elements [ count - 1 ];
			
		};
		
		const T & peek () const
		{
			
			return elements [ count - 1 ];
			
		};
		
		// push an entire vector of values into this vector by copying them.
		void push ( const Vector<T> & values )
		{
			
			ExpandMinimumCapacity ( values.count );
			
			for ( size_t i = 0; i < values.count; i ++ )
				elements [ count + i ] = values.elements [ i ];
			
			count += values.count;
			
		};
		
		// remove an item at an index from this vector
		void remove ( size_t index )
		{
			
			if ( index >= count )
				return;
			
			for ( size_t i = index; i < count - 1; i ++ )
				elements [ i ] = elements [ i + 1 ];
			
			count --;
			
		};
		
		// remove n items at an index from this vector
		void remove ( size_t index, size_t count )
		{
			
			if ( index >= this -> count )
				return;
			
			if ( ( index + count ) > this -> count )
				count = this -> count - index;
			
			for ( size_t i = index; i < this -> count - count; i ++ )
				elements [ i ] = elements [ i + count ];
			
			this -> count -= count;
			
		}
		
		Array<T> && into_array ()
		{
			
			Array<T> out_array = Array<T>::create_from_c_array_owned ( elements, count );
			elements = nullptr;
			count = 0;
			capacity = 0;
			return std::move ( out_array );
			
		}
		
	private:
		
		void DoubleCapacity ()
		{
			
			T * new_elements = new T [ capacity * 2 ];
			
			for ( size_t i = 0; i < capacity; i ++ )
				new_elements [ i ] = std::move ( elements [ i ] );
			
			delete elements;
			
			elements = new_elements;
			capacity *= 2;
			
		}
		
		void ExpandMinimumCapacity ( size_t additional_element_count )
		{
			
			if ( capacity - count < additional_element_count )
			{
				
				T * new_elements = new T [ capacity * 2 + additional_element_count ];
				
				for ( size_t i = 0; i < capacity * 2 + additional_element_count; i ++ )
					new_elements [ i ] = elements [ i ];
				
				delete elements;
				
				capacity = capacity * 2 + additional_element_count;
				this -> elements = new_elements;
				
			}
			
		}
		
		size_t capacity;
		size_t count;
		
		T * elements;
		
	};
	
};

#endif
