#ifndef ARGON_RENDERING_TEXTUREBASE_H
#define ARGON_RENDERING_TEXTUREBASE_H

#include <argon/rendering/rendering.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/memory/refcounted.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

namespace Argon::Rendering
{
	
	class TextureBase : public Memory::RefCounted
	{
	public:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		typedef GLenum Format;
		typedef GLenum InternalFormat;
		typedef GLenum DataType;
		
		static const Format kformat_alpha = GL_ALPHA;
		static const Format kformat_r = GL_RED;
		static const Format kformat_rg = GL_RG;
		static const Format kformat_rgb = GL_RGB;
		static const Format kformat_bgr =  GL_BGR;
		static const Format kformat_rgba = GL_RGBA;
		static const Format kformat_bgra =  GL_BGRA;
		static const Format kformat_depth = GL_DEPTH_COMPONENT;
		static const Format kformat_depth_stencil = GL_DEPTH_STENCIL;
		
		static const InternalFormat kinternalformat_alpha = GL_ALPHA;
		static const InternalFormat kinternalformat_r = GL_RED;
		static const InternalFormat kinternalformat_rg = GL_RG;
		static const InternalFormat kinternalformat_rgb = GL_RGB;
		static const InternalFormat kinternalformat_bgr =  GL_BGR;
		static const InternalFormat kinternalformat_rgba = GL_RGBA;
		static const InternalFormat kinternalformat_bgra =  GL_BGRA;
		static const InternalFormat kinternalformat_depth = GL_DEPTH_COMPONENT;
		static const InternalFormat kinternalformat_depth_stencil = GL_DEPTH_STENCIL;
		
		static const InternalFormat kinternalformat_r_8u = GL_R8UI;
		static const InternalFormat kinternalformat_r_8i = GL_R8I;
		static const InternalFormat kinternalformat_r_8i_norm = GL_R8_SNORM;
		
		static const InternalFormat kinternalformat_r_16i = GL_R16I;
		static const InternalFormat kinternalformat_r_16i_norm = GL_R16_SNORM;
		static const InternalFormat kinternalformat_r_16u = GL_R16UI;
		static const InternalFormat kinternalformat_r_16f = GL_R16F;
		
		static const InternalFormat kinternalformat_r_32i = GL_R32I;
		static const InternalFormat kinternalformat_r_32u = GL_R32UI;
		static const InternalFormat kinternalformat_r_32f = GL_R32F;
		
		static const InternalFormat kinternalformat_rg_8u = GL_RG8UI;
		static const InternalFormat kinternalformat_rg_8i = GL_RG8I;
		static const InternalFormat kinternalformat_rg_8i_norm = GL_RG8_SNORM;
		
		static const InternalFormat kinternalformat_rg_16i = GL_RG16I;
		static const InternalFormat kinternalformat_rg_16u = GL_RG16UI;
		static const InternalFormat kinternalformat_rg_16f = GL_RG16F;
		static const InternalFormat kinternalformat_rg_18i_norm = GL_RG8_SNORM;
		
		static const InternalFormat kinternalformat_rg_32i = GL_RG32I;
		static const InternalFormat kinternalformat_rg_32u = GL_RG32UI;
		static const InternalFormat kinternalformat_rg_32f = GL_RG32F;
		
		static const InternalFormat kinternalformat_rgb_8u = GL_RGB8UI;
		static const InternalFormat kinternalformat_rgb_8i = GL_RGB8I;
		static const InternalFormat kinternalformat_rgb_8i_norm = GL_RGB8_SNORM;
		
		static const InternalFormat kinternalformat_rgb_16i = GL_RGB16I;
		static const InternalFormat kinternalformat_rgb_16u = GL_RGB16UI;
		static const InternalFormat kinternalformat_rgb_16f = GL_RGB16F;
		static const InternalFormat kinternalformat_rgb_16i_norm = GL_RGB16_SNORM;
		
		static const InternalFormat kinternalformat_rgb_32i = GL_RGB32I;
		static const InternalFormat kinternalformat_rgb_32u = GL_RGB32UI;
		static const InternalFormat kinternalformat_rgb_32f = GL_RGB32F;
		
		static const InternalFormat kinternalformat_rgba_8i = GL_RGBA8I;
		static const InternalFormat kinternalformat_rgba_8u = GL_RGBA8UI;
		static const InternalFormat kinternalformat_rgba_8i_norm = GL_RGBA8_SNORM;
		
		static const InternalFormat kinternalformat_rgba_16i = GL_RGBA16I;
		static const InternalFormat kinternalformat_rgba_16u = GL_RGBA16UI;
		static const InternalFormat kinternalformat_rgba_16i_norm = GL_RGBA16_SNORM;
		static const InternalFormat kinternalformat_rgba_16f = GL_RGBA16F;
		
		static const InternalFormat kinternalformat_rgba_32i = GL_RGBA32I;
		static const InternalFormat kinternalformat_rgba_32u = GL_RGBA32UI;
		static const InternalFormat kinternalformat_rgba_32f = GL_RGBA32F;
		
		static const DataType kdatatype_ubyte = GL_UNSIGNED_BYTE;
		static const DataType kdatatype_byte = GL_BYTE;
		static const DataType kdatatype_ushort = GL_UNSIGNED_SHORT;
		static const DataType kdatatype_short = GL_SHORT;
		static const DataType kdatatype_uint = GL_UNSIGNED_INT;
		static const DataType kdatatype_int = GL_INT;
		static const DataType kdatatype_float = GL_FLOAT;
		static const DataType kdatatype_ubyte_3_3_2 = GL_UNSIGNED_BYTE_3_3_2;
		static const DataType kdatatype_ubyte_2_3_3_Rev = GL_UNSIGNED_BYTE_2_3_3_REV;
		static const DataType kdatatype_ubyte_5_6_5 = GL_UNSIGNED_SHORT_5_6_5;
		static const DataType kdatatype_ubyte_5_6_5_Rev = GL_UNSIGNED_SHORT_5_6_5_REV;
		static const DataType kdatatype_ushort_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4;
		static const DataType kdatatype_ushort_4_4_4_4_Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV;
		static const DataType kdatatype_ushort_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1;
		static const DataType kdatatype_ushort_1_5_5_5_Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV;
		static const DataType kdatatype_uint_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8;
		static const DataType kdatatype_uint_8_8_8_8_Rev = GL_UNSIGNED_INT_8_8_8_8_REV;
		static const DataType kdatatype_uint_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2;
		static const DataType kdatatype_uint_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV;
		
		#endif
		
	protected:
		
		TextureBase ();
		~TextureBase ();
		
	};
	
}

#endif
