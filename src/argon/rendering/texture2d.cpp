#include <argon/rendering/texture2d.hpp>
#include <argon/rendering/context.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
Argon::Rendering::Texture2D::Texture2D ( GLuint texture_name, Context * source_context ):
	TextureBase (),
	source_context ( source_context ),
	texture_name ( texture_name ),
	width ( 0 ),
	height ( 0 )
{
	
	source_context -> Ref ();
	
}

Argon::Rendering::Texture2D::~Texture2D ()
{
	
	source_context -> function_ptrs.delete_textures ( 1, & texture_name );
	texture_name = 0;
	
	source_context -> Deref ();
	source_context = nullptr;
	
}

void Argon::Rendering::Texture2D::bind ()
{
	
	if ( source_context -> current_bound_texture_2d != this )
	{
		
		source_context -> function_ptrs.bind_texture ( GL_TEXTURE_2D, texture_name );
		source_context -> current_bound_texture_2d = this;
		
	}
	
}

void Argon::Rendering::Texture2D::set_size ( GLsizei width, GLsizei height, GLint mipmap_level, Format format, InternalFormat internalformat )
{
	
	bind ();
	
	source_context -> function_ptrs.tex_image_2d ( GL_TEXTURE_2D, mipmap_level, internalformat, width, height, 0, format, kdatatype_ubyte, 0 );
	
}
#endif
	
