#ifndef ARGON_RENDERING_BACKENDS_OPENGL_CONTEXT_HPP
#define ARGON_RENDERING_BACKENDS_OPENGL_CONTEXT_HPP

#include <argon/memory/refcounted.hpp>
#include <argon/string.hpp>

namespace Argon::Rendering::OpenGL
{
	
	class IGLContext : public virtual Memory::IRefCounted
	{
	public:
		
		virtual void make_current () const = 0;
		virtual void flush_back_buffer () const = 0;
		
		virtual void * void_gl_get_proc_address ( const String & gl_symbol ) const = 0;
		
	};
	
}

#endif
