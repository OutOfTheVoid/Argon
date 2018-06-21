#include <argon/rendering/shaderprogram.hpp>
#include <argon/rendering/context.hpp>
#include <argon/rendering/vertexshader.hpp>
#include <argon/rendering/fragmentshader.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
Argon::Rendering::ShaderProgram::ShaderProgram ( GLuint name, Context * source_context ):
	RefCounted ( 1 ),
	name ( name ),
	source_context ( source_context ),
	linked ( false ),
	vertex_shader ( nullptr ),
	fragment_shader ( nullptr )
{
	
	source_context -> ref ();
	
}
#endif

Argon::Rendering::ShaderProgram::~ShaderProgram ()
{
	
	#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
	if ( this -> vertex_shader != nullptr )
		this -> vertex_shader -> deref ();
	
	if ( this -> fragment_shader != nullptr )
		this -> fragment_shader -> deref ();
	
	source_context -> deref ();
	#endif
	
}

void Argon::Rendering::ShaderProgram::set_vertex_shader ( VertexShader * vertex_shader )
{
	
	if ( this -> vertex_shader == vertex_shader )
		return;
	else
		linked = false;
	
	if ( this -> vertex_shader != nullptr )
	{
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		this -> source_context -> function_ptrs.detach_shader ( name, this -> vertex_shader -> name );
		#endif
		
		this -> vertex_shader -> deref ();
		
	}
	
	this -> vertex_shader = vertex_shader;
	
	if ( this -> vertex_shader != nullptr )
	{
		
		this -> vertex_shader -> ref ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		this -> source_context -> function_ptrs.attach_shader ( name, this -> vertex_shader -> name );
		#endif
		
	}
	
}

void Argon::Rendering::ShaderProgram::set_fragment_shader ( FragmentShader * fragment_shader )
{
	
	if ( this -> fragment_shader == fragment_shader )
		return;
	else
		linked = false;
	
	if ( this -> fragment_shader != nullptr )
	{
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		this -> source_context -> function_ptrs.detach_shader ( name, this -> fragment_shader -> name );
		#endif
		
		this -> fragment_shader -> deref ();
		
	}
	
	this -> fragment_shader = fragment_shader;
	
	if ( this -> fragment_shader != nullptr )
	{
		
		this -> fragment_shader -> ref ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		this -> source_context -> function_ptrs.attach_shader ( name, this -> fragment_shader -> name );
		#endif
		
	}
	
}

bool Argon::Rendering::ShaderProgram::link ()
{
	
	#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
	source_context -> make_current ();
	
	GLint link_status = GL_TRUE;
	
	source_context -> function_ptrs.link_program ( name );
	source_context -> function_ptrs.get_program_iv ( name, GL_LINK_STATUS, & link_status );
	
	source_context -> current_bound_shader_program = this;
	
	if ( link_status ==  GL_TRUE )
		linked = true;
	else
		linked = false;
	#endif
	
	return linked;
	
}

bool Argon::Rendering::ShaderProgram::is_linked ()
{
	
	return linked;
	
}
