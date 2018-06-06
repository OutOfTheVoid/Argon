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
	protected:
		
		TextureBase ();
		
	protected:
		
		~TextureBase ();
		
	};
	
}

#endif
