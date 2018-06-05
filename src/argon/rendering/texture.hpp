#ifndef ARGON_RENDERING_TEXTURE_HPP
#define ARGON_RENDERING_TEXTURE_HPP

#include <argon/rendering/rendering.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/memory/refcounted.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

namespace Argon::Rendering
{
	
	class Context;
	
	class Texture : public Memory::RefCounted
	{
	public:
		
		
		
	}
	
}
