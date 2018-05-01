#include <argon/rendering/context.cpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)

Argon::Rendering::Context::Context ( OpenGL::IGLContext * gl_context ):
	gl_context ( gl_context )
{
	
	gl_context -> Ref ();
	
}

Argon::Rendering::Context::~Context ()
{
	
	gl_context -> Deref ();
	
}

void Argon::Rendering::Context::make_current ()
{
	
	gl_context -> make_current ();
	
}

void Argon::Rendering::Context::flush_back_buffer ()
{
	
	gl_context -> flush_back_buffer ();
	
}

#elif (ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)

Argon::Rendering::Context::Context ()
{
}

Argon::Rendering::Context::~Context ()
{
}

void Argon::Rendering::Context::make_current ()
{
}

void Argon::Rendering::Context::flush_back_buffer ()
{
}

#endif


