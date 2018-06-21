#ifndef ARGON_RENDERING_SHADERPROGRAM_H
#define ARGON_RENDERING_SHADERPROGRAM_H

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
	class VertexShader;
	class FragmentShader;
	
	class ShaderProgram : public Memory::RefCounted
	{
	public:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		ShaderProgram ( GLuint name, Context * source_context ); 
		#endif
		
		void set_vertex_shader ( VertexShader * vertex_shader );
		void set_fragment_shader ( FragmentShader * fragment_shader );
		
		bool link ();
		bool is_linked ();
		
	private:
		
		void bind ();
		
		~ShaderProgram ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		GLuint name;
		Context * source_context;
		
		bool linked;
		#endif
		
		VertexShader * vertex_shader;
		FragmentShader * fragment_shader;
		
	};
	
}

#endif
