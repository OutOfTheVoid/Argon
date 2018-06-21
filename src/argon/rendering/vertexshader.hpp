#ifndef ARGON_RENDERING_VERTEXSHADER_H
#define ARGON_RENDERING_VERTEXSHADER_H

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
	class ShaderProgram;
	
	class VertexShader : public Memory::RefCounted
	{
	public:
		
		enum ShaderLanguage
		{
			
			kshaderlanguage_glsl,
			kshaderlanguage_hlsl,
			kshaderlanguage_spirv,
			
		};
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		VertexShader ( GLuint name, Context * source_context );
		
		static const ShaderLanguage kshader_language = kshaderlanguage_glsl;
		#endif
		
		void set_source ( const char * source );
		void set_source ( const String & source );
		bool compile ();
		String && get_compile_info ();
		
	private:
		
		friend class ShaderProgram;
		
		~VertexShader ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		GLuint name;
		Context * source_context;
		
		bool compiled;
		#endif
		
	};
	
}

#endif
