#include <argon/argon.h>

Argon::Array<Argon::String> ProgramArguments ( Argon::Array<Argon::String>::NoInit );

void Argon::lib_init ( Array<String> && ProgramArgs )
{
	
	ProgramArguments = std::move ( ProgramArgs );
	
};

const Argon::Array<Argon::String> & Argon::GetProgramArgs ()
{
	
	return ProgramArguments;
	
}

void Argon::lib_deinit ()
{	
};
