#include <argon/panic.hpp>
#include <cerrno>
#include <cstdio>
#include <cstdlib>

void Argon::panic ( const char * message )
{
	
	fprintf ( stderr, "Argon::panic ( \"%s\" );\n", message );
	
	if ( errno != 0 )
		perror ( "ERRNO MESSAGE: " );
		
	exit ( 1 );
	
}

