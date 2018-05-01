#ifndef ARGON_RENDERING_CONTEXT_HPP
#define ARGON_RENDERING_CONTEXT_HPP

#include <argon/memory/ref_counted.h>

#include <argon/global_config.h>
#include <argon/osal/targets.h>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
	#define ARGON_RENDERING_BACKEND ARGON_PLATFORM_RENDERING_BACKEND_WINDOWS
#elif(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
	#define ARGON_RENDERING_BACKEND ARGON_PLATFORM_RENDERING_BACKEND_MACOSX
#elif(ARGON_PLARFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
	#define ARGON_RENDERING_BACKEND ARGON_PLATFORM_RENDERING_BACKEND_LINUX
#else
	#define ARGON_RENDERING_BACKEND ARGON_RENDERING_BACKEND_DUMMY
#endif

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

namespace Argon::Rendering
{
	
	class Context : public RefCounted
	{
	public:
		
		void make_current ();
		void flush_back_buffer ();
		
	private:
		
		~Context ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		
		Context ( OpenGL::IGLContext * gl_context );
		
		OpenGL::IGLContext * gl_context;
		
		#elif(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)
		
		Context ();
		
		#endif
		
	};
	
}

#endif
