#ifndef ARGON_RENDERING_TEXTURE2D_HPP
#define ARGON_RENDERING_TEXTURE2D_HPP

#include <argon/rendering/rendering.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/rendering/texturebase.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

namespace Argon::Rendering
{
	
	class Context;
	
	class Texture2D : public TextureBase
	{
	public:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		Texture2D ( GLuint name, Context * source_context );
		
		typedef GLsizei texsize_t;
		typedef GLint mipmaplevel_t;
		typedef GLint texoffset_t;
		#endif
		
		void alloc_buffer ( texsize_t width, texsize_t height, mipmaplevel_t mipmap_level, Format format, InternalFormat internalformat );
		void write_buffer ( texoffset_t x_offset, texoffset_t y_offset, texsize_t width, texsize_t height, mipmaplevel_t mipmap_level, Format format, DataType data_type, void * data );
		void alloc_and_write_buffer ( texsize_t width, texsize_t height, mipmaplevel_t mipmap_level, InternalFormat internalformat, Format format, DataType data_type, void * data );
		
		texsize_t get_width ();
		texsize_t get_height ();
		
	protected:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		void bind ();
		#endif
		
	private:
		
		~Texture2D ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		Context * source_context;
		GLuint texture_name;
		#endif
		
		texsize_t width;
		texsize_t height;
		
	};
	
}

#endif
