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
	
	if ( source_context -> current_bound_texture_2d == this )
	{
		
		source_context -> current_bound_texture_2d = nullptr;
		source_context -> function_ptrs.bind_texture ( GL_TEXTURE_2D, 0 );
		
	}
	
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

void Argon::Rendering::Texture2D::alloc_buffer ( texsize_t width, texsize_t height, mipmaplevel_t mipmap_level, Format format, InternalFormat internalformat )
{
	
	bind ();
	
	source_context -> function_ptrs.tex_image_2d ( GL_TEXTURE_2D, mipmap_level, internalformat, width, height, 0, format, kdatatype_ubyte, 0 );
	
	this -> width = width;
	this -> height = height;
	
}

void Argon::Rendering::Texture2D::write_buffer ( texoffset_t x_offset, texoffset_t y_offset, texsize_t width, texsize_t height, mipmaplevel_t mipmap_level, Format format, DataType data_type, void * data )
{
	
	bind ();
	
	source_context -> function_ptrs.tex_sub_image_2d ( GL_TEXTURE_2D, mipmap_level, x_offset, y_offset, width, height, format, data_type, data );
	
}

void Argon::Rendering::Texture2D::alloc_and_write_buffer ( texsize_t width, texsize_t height, mipmaplevel_t mipmap_level, InternalFormat internalformat, Format format, DataType data_type, void * data )
{
	
	bind ();
	
	source_context -> function_ptrs.tex_image_2d ( GL_TEXTURE_2D, mipmap_level, internalformat, width, height, 0, format, data_type, data );
	
}

#endif

Argon::Rendering::Texture2D::texsize_t Argon::Rendering::Texture2D::get_width ()
{
	
	return width;
	
}

Argon::Rendering::Texture2D::texsize_t Argon::Rendering::Texture2D::get_height ()
{
	
	return height;
	
}
	
