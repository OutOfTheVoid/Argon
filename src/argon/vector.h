#ifndef ARGON_VECTOR_H
#define ARGON_VECTOR_H

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
		
		Vector ( NO_INIT no_init ):
			capacity ( 0 ),
			count ( 0 ),
			elements ( nullptr )
		{
		};
		
		Vector ():
			capacity ( 100 ),
			count ( 0 ),
			elements ( new T [ capacity ] )
		{
		};
		
		Vector ( size_t capacity ):
			capacity ( capacity ),
			count ( 0 ),
			elements ( new T [ capacity ] )
		{
		};
		
		Vector ( T * elements, size_t count ):
			capacity ( count ),
			count ( 0 ),
			elements ( new T [ capacity ] )
		{
			
			if ( elements != nullptr )
			{
				
				for ( size_t i = 0; i < count; i ++ )
					this -> elements [ i ] = elements [ i ];
				
			}
			
		};
		
		Vector ( T * elements, size_t count, size_t additional_capacity ):
			capacity ( count + additional_capacity ),
			count ( count ),
			elements ( new T [ capacity ] )
		{
			
			for ( size_t i = 0; i < count; i ++ )
				this -> elements [ i ] = elements [ i ];
			
		};
		
		Vector ( const Vector<T> & elements ):
			capacity ( elements.capacity ),
			count ( elements.count ),
			elements ( new T [ elements.capacity ] )
		{
			
			for ( size_t i = 0; i < elements.count; i ++ )
				this -> elements [ i ] = elements.elements [ i ];
			
		};
		
		Vector ( Vector<T> && moved ):
			capacity ( moved.capacity ),
			count ( moved.count ),
			elements ( moved.elements )
		{
			
			moved.elements = nullptr;
			moved.count = 0;
			moved.capacity = 0;
			
		};
		
		void operator= ( Vector<T> && moved )
		{
			
			std::swap ( elements, moved.elements );
			std::swap ( count, moved.count );
			std::swap ( capacity, moved.capacity );
			
		};
		
		Vector ( const Vector<T> & elements, size_t additional_capacity ):
			capacity ( elements.capacity + additional_capacity ),
			count ( elements.count ),
			elements ( new T [ capacity ] )
		{
			
			for ( size_t i = 0; i < elements.count; i ++ )
				this -> elements [ i ] = elements.elements [ i ];
			
		};
		
		size_t get_count () const
		{
			
			return count;
			
		};
		
		size_t get_capacity () const
		{
			
			return capacity;
			
		};
		
		const T & operator[] ( int32_t index ) const
		{
			
			return elements [ index ];
			
		};
		
		T & operator[] ( int32_t index )
		{
			
			return elements [ index ];
			
		};
		
		void push ( T value )
		{
			
			if ( count >= capacity )
				DoubleCapacity ();
			
			elements [ count ] = value;
			count ++;
			
		};
		
		T pop ()
		{
			
			count --;
			return elements [ count ];
			
		};
		
		T & peek ()
		{
			
			return elements [ count - 1 ];
			
		};
		
		const T & peek () const
		{
			
			return elements [ count - 1 ];
			
		};
		
		void push ( const Vector<T> & values )
		{
			
			ExpandMinimumCapacity ( values.count );
			
			for ( size_t i = 0; i < values.count; i ++ )
				elements [ count + i ] = values.elements [ i ];
			
			count += values.count;
			
		};
		
		void remove ( size_t index )
		{
			
			if ( index >= count )
				return;
			
			for ( size_t i = index; i < count - 1; i ++ )
				elements [ i ] = elements [ i + 1 ];
			
			count --;
			
		};
		
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
		
	private:
		
		void DoubleCapacity ()
		{
			
			T * new_elements = new T [ capacity * 2 ];
			
			for ( size_t i = 0; i < capacity; i ++ )
				new_elements [ i ] = elements [ i ];
			
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
