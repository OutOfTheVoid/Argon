#ifndef ARGON_MEMORY_REFCOUNTED_HPP
#define ARGON_MEMORY_REFCOUNTED_HPP

#include <atomic>

namespace Argon::Memory
{
	
	class IRefCounted
	{
	public:
		virtual void Ref () const = 0;
		virtual void Deref () const = 0;
		
	};
	
	class RefCounted : public virtual IRefCounted
	{
	private:
		
		std::atomic_int ref_count;
		
		void ( * finalizer ) ( void * );
		void * finalizer_data;
		
	protected:
		
		inline RefCounted ( int initial_ref_count ):
			ref_count ( initial_ref_count ),
			finalizer ( nullptr ),
			finalizer_data ( nullptr )
		{
		};
		
		RefCounted ( int initial_ref_count, void ( * finalizer ) ( void * ), void * finalizer_data ):
			ref_count ( initial_ref_count ),
			finalizer ( finalizer ),
			finalizer_data ( finalizer_data )
		{
		};
		
	public:
		
		inline virtual ~RefCounted ()
		{
			
			if ( finalizer != nullptr )
				finalizer ( finalizer_data );
			
		};
		
		inline void Ref () const
		{
			
			const_cast<std::atomic_int &>( ref_count ) ++;
			
		};
		
		inline void Deref () const
		{
			
			int previous = const_cast<std::atomic_int &>( ref_count ).fetch_sub ( 1 );
			
			if ( previous == 1 )
			{
				
				if ( finalizer != nullptr )
					( * finalizer ) ( finalizer_data );
				else
					delete this;
				
			}
			
		};
		
	};
	
}

#endif
