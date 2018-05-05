#ifndef ARGON_CPP_UTIL_H
#define ARGON_CPP_UTIL_H

/*
*===================================*
* cpp_nocopy - prevents copying     *
*===================================*
* cpp_nocopy is a base class which
* is intended purely to prevent
* default copy implementation in 
* classes where members are not 
* semantically copyable.
*
* simply extend cpp_nocopy to use:
*	class A : public cpp_nocopy
*/

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
