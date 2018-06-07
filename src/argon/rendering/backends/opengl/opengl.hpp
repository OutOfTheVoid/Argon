#ifndef ARGON_RENDERING_BACKENDS_OPENGL_OPENGL_HPP
#define ARGON_RENDERING_BACKENDS_OPENGL_OPENGL_HPP

#include <argon/osal/targets.h>
#include <argon/rendering/rendering.hpp>
#include <argon/rendering/backends/opengl/context.hpp>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#elif(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
#elif(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
#include <GL/gl.h>
#endif

namespace Argon::Rendering::OpenGL
{
	
	typedef struct
	{
		
		void ( * gen_framebuffers ) ( GLsizei n, GLuint * frame_buffers );
		void ( * bind_framebuffer ) ( GLenum target, GLuint frame_buffer );
		void ( * delete_framebuffers ) ( GLsizei count, const GLuint * framebuffers );
		void ( * clear ) ( GLbitfield mask );
		void ( * framebuffer_renderbuffer ) ( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
		void ( * framebuffer_texture ) ( GLenum target, GLenum attachment, GLuint texture, GLint level );
		void ( * blit_framebuffers ) ( GLint srcX0, GLint srcY0,GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter );
		GLenum ( * check_framebuffer_status ) ( GLenum target );
		
		void ( * clear_color ) ( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
		void ( * clear_depth ) ( GLdouble depth );
		
		void ( * gen_textures ) ( GLsizei n, GLuint * textures );
		void ( * delete_textures ) ( GLsizei count, const GLuint * textures );
		void ( * bind_texture ) ( GLenum target, GLuint texture );
		void ( * tex_image_2d ) ( GLenum target, GLint level, GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data );
		void ( * tex_parameter_i ) ( GLenum target, GLenum param_name, GLint param );
		void ( * tex_sub_image_2d ) ( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels );
		
		void ( * gen_renderbuffers ) ( GLsizei n, GLuint * render_buffers );
		void ( * bind_renderbuffer ) ( GLenum target, GLuint render_buffer );
		void ( * renderbuffer_storage ) ( GLenum target, GLenum internalformat, GLsizei width, GLsizei height );
		void ( * delete_renderbuffers ) ( GLsizei n, GLuint * render_buffers );
		
		void ( * gen_buffers ) ( GLsizei n, GLuint * buffers );
		void ( * delete_buffers ) ( GLsizei n, GLuint * buffers );
		void ( * bind_buffer ) ( GLenum target, GLuint buffer );
		void ( * buffer_data ) ( GLenum target​, GLsizeiptr size​, const GLvoid * data​, GLenum usage );
		void ( * sub_buffer_data ) ( GLenum target​, GLintptr offset​, GLsizeiptr size​, const GLvoid * data​ );
		
		void ( * draw_buffers ) ( GLsizei n, const GLenum * bufs );
		
		void ( * viewport ) ( GLint x, GLint y, GLsizei width, GLsizei height );
		
		GLenum ( * get_error ) ();
		
	} GLFunctionPointers;
	
}

#endif
