#ifndef ARGON_RENDERING_BACKENDS_OPENGL_OPENGL_HPP
#define ARGON_RENDERING_BACKENDS_OPENGL_OPENGL_HPP

#include <argon/osal/targets.h>
#include <argon/rendering/rendering.hpp>
#include <argon/rendering/backends/opengl/context.hpp>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#elif(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
#elif(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
#include <GL/gl.h>
#endif

namespace Argon::Rendering::OpenGL
{
	
	typedef struct
	{
		
		void ( * bind_framebuffer ) ( GLenum target,  GLuint framebuffer );
		void ( * gen_framebuffers ) ( GLsizei count,  GLuint * framebuffers );
		void ( * delete_framebuffers ) ( GLsizei count, const GLuint * framebuffers );
		void ( * clear ) ( GLbitfield mask );
		void ( * clear_color ) ( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
		void ( * clear_depth ) ( GLdouble depth );
		
	} GLFunctionPointers;
	
}

#endif
