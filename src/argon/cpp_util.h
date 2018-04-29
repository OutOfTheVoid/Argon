#ifndef ARGON_CPP_UTIL_H
#define ARGON_CPP_UTIL_H

class cpp_nocopy
{
protected:	
	
	inline cpp_nocopy () {};
	inline ~cpp_nocopy () {};
	
protected:
	
	inline cpp_nocopy ( const cpp_nocopy & _ ) = delete;
	inline const cpp_nocopy & operator= ( const cpp_nocopy & _ ) = delete;
	
};

#endif
