#include <argon/error.h>

Argon::Error::Error ( const String & Message ):
	Message ( Message )
{
};

Argon::Error::Error ( const Error & Copy ):
	Message ( Copy.Message )
{
}


Argon::Error::Error ( Error && Moved ):
	Message ( std::move ( Moved.Message ) )
{
}

Argon::Error::~Error ()
{
}

const Argon::String & Argon::Error::GetMessage ()
{
	
	return Message;
	
}
