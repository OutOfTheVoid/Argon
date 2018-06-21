#ifndef ARGON_RENDERING_VERTEXSPECIFICATION_H
#define ARGON_RENDERING_VERTEXSPECIFICATION_H

#include <argon/rendering/rendering.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/memory/refcounted.hpp>
#include <argon/string.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

namespace Argon::Rendering
{
	
	class Context;
	
	class VertexSpecification : public Memory::RefCounted
	{
	public:	
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		VertexSpecification ( GLuint name, Context * source_context );
		#endif
		
	private:
		
		~VertexSpecification ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		GLuint name;
		Context * source_context;
		#endif
		
	};
	
}

#endif
