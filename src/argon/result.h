#ifndef ARGON_RESULT_H
#define ARGON_RESULT_H

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
		
		T & get_value ()
		{
			
			return data.value;
			
		};
		
		const T & get_value () const
		{
			
			return data.value;
			
		};
		
		ERROR & get_error ()
		{
			
			return data.error;
			
		};
		
		const ERROR & get_error () const
		{
			
			return data.error;
			
		};
		
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
