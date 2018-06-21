#include <argon/rendering/fragmentshader.hpp>
#include <argon/rendering/context.hpp>
#include <cstring>

Argon::Rendering::FragmentShader::FragmentShader ( GLuint name, Context * source_context ):
	RefCounted ( 1 ),
	name ( name ),
	source_context ( source_context ),
	compiled ( false )
{
	
	source_context -> ref ();
	
}

Argon::Rendering::FragmentShader::~FragmentShader ()
{
	
	source_context -> deref ();
	
}

void Argon::Rendering::FragmentShader::set_source ( const char * source )
{
	
	GLint length = strlen ( source );
	source_context -> function_ptrs.shader_source ( name, 1, & source, & length );
	
	compiled = false;
	
}

void Argon::Rendering::FragmentShader::set_source ( const String & source )
{
	
	std::string std_string_source = source;
	GLint length = std_string_source.size ();
	const GLchar * c_string_source = std_string_source.c_str ();
	
	source_context -> function_ptrs.shader_source ( name, 1, & c_string_source, & length );
	
	compiled = false;
	
}

bool Argon::Rendering::FragmentShader::compile ()
{
	
	if ( ! compiled )
	{
		
		GLint success = 0;
		
		source_context -> function_ptrs.compile_shader ( name );
		source_context -> function_ptrs.get_shader_iv ( name, GL_COMPILE_STATUS, & success );
		
		compiled = !! success;
		
	}
	
	return compiled;
	
}

Argon::String && Argon::Rendering::FragmentShader::get_compile_info ()
{
	
	GLint log_length;
	
	source_context -> function_ptrs.get_shader_iv ( name, GL_INFO_LOG_LENGTH, & log_length );
	
	if ( log_length == 0 )
		return std::move ( String () );
	
	char * shader_log_buff = new char [ log_length ];
	source_context -> function_ptrs.get_shader_info_log ( name, log_length, & log_length, shader_log_buff );
	
	return std::move ( String ( shader_log_buff, log_length ) );
	
}

