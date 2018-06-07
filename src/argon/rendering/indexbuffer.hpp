#ifndef ARGON_RENDERING_INDEXBUFFER_H
#define ARGON_RENDERING_INDEXBUFFER_H

#include <argon/memory/refcounted.hpp>

#include <argon/rendering/rendering.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/rendering/texturebase.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

namespace Argon::Rendering
{
	
	class Context;
	
	class IndexBuffer : public Memory::RefCounted
	{
	public:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		IndexBuffer ( GLuint name, Context * source_context );
		
		typedef GLsizeiptr buffersize_t;
		typedef GLintptr bufferoffset_t;
		#endif
		
		typedef uint32_t bufferusagehint_t;
		
		static const bufferusagehint_t kusagehint_static = 0;
		static const bufferusagehint_t kusagehint_stream = 1;
		static const bufferusagehint_t kusagehint_dynamic = 2;
		
		static const bufferusagehint_t kusagehint_cpu_to_gpu = 0;
		static const bufferusagehint_t kusagehint_gpu_to_cpu = 4;
		static const bufferusagehint_t kusagehint_gpu_to_gpu = 8;
		
		void alloc_buffer ( buffersize_t size, bufferusagehint_t usage_hint = 0 );
		void write_buffer ( bufferoffset_t offset, buffersize_t size, void * data );
		void alloc_and_write_buffer ( buffersize_t size, void * data, bufferusagehint_t usage_hint = 0 );
		
	protected:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		void bind ();
		#endif
		
		~IndexBuffer ();
		
	private:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		GLuint name;
		Context * source_context;
		#endif
		
	};
	
}

#endif
