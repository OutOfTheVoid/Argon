#ifndef ARGON_ARGON_H
#define ARGON_ARGON_H

#include <argon/array.h>
#include <argon/error.h>
#include <argon/result.h>
#include <argon/string.h>
#include <argon/vector.h>
#include <argon/osal/osal.h>
#include <argon/memory/memory.h>

namespace Argon
{
	
	void lib_init ( Array<String> && ProgramArgs );
	
	const Array<String> & GetProgramArgs ();
	
	void lib_deinit ();
	
};

#endif
