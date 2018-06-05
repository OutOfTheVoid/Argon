#ifndef ARGON_UI_GUIWINDOW_HPP
#define ARGON_UI_GUIWINDOW_HPP

#include <stdint.h>

#include <argon/osal/targets.h>
#include <argon/osal/windowsystem.hpp>

#include <argon/rendering/context.hpp>

#include <argon/memory/refcounted.hpp>
#include <argon/geometry/geometry.hpp>

#include <argon/events/eventdispatcher.hpp>

namespace Argon::UI
{
	
	using Geometry::Rect;
	
	class GUIWindow : public Memory::RefCounted, public Argon::Events::EventDispatcher
	{
	public:
		
		typedef uint32_t GUIWindowStyle;
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
		static const GUIWindowStyle kstyle_minimizable = Argon::OSAL::MacOSX::MacWindow::kstyle_miniaturizable;
		static const GUIWindowStyle kstyle_resizable = Argon::OSAL::MacOSX::MacWindow::kstyle_resizable;
		static const GUIWindowStyle kstyle_titled = Argon::OSAL::MacOSX::MacWindow::kstyle_titled;
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
		static const GUIWindowStyle kstyle_minimizable = 0;
		static const GUIWindowStyle kstyle_resizable = 0;
		static const GUIWindowStyle kstyle_titled = 0;
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)
		static const GUIWindowStyle kstyle_minimizable = OSAL::Windows::WinWindow::kstyle_minimizable;
		static const GUIWindowStyle kstyle_maximizable = OSAL::Windows::WinWindow::kstyle_maximizable;
		static const GUIWindowStyle kstyle_titled = OSAL::Windows::WinWindow::kstyle_titled;
		#else
		#endif
		
		static GUIWindow * create ( const Rect & content_frame, GUIWindowStyle style );
		
		void show ();
		void set_title ( const String & title );
		void set_fullscreen ( bool fullscreen );
		
		Rendering::Context * get_render_context ( bool temporary );
		
	private:
		
		static bool should_close_event_dispatcher ( void * data );
		static void will_close_event_dispatcher ( void * data );
		
		~GUIWindow ();
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)
		
		GUIWindow ( OSAL::MacOSX::MacWindow * os_window );
		
		OSAL::MacOSX::MacWindow * os_window;
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		OSAL::MacOSX::MacGLView * gl_view;
		OSAL::MacOSX::MacGLContextObj * drawing_gl_context;
		
		GLuint transfer_framebuffer;
		GLuint transfer_framebuffer_texture;
		GLuint transfer_framebuffer_depth_renderbuffer;
		
		GLint transfer_framebuffer_width;
		GLint transfer_framebuffer_height;
		
		void ( * gl_gen_framebuffers ) ( GLsizei n, GLuint * frame_buffers );
		void ( * gl_bind_framebuffer ) ( GLenum target, GLuint frame_buffer );
		void ( * gl_gen_textures ) ( GLsizei n, GLuint * textures );
		void ( * gl_bind_texture ) ( GLenum target, GLuint texture );
		void ( * gl_tex_image_2d ) ( GLenum target, GLint level, GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data );
		void ( * gl_tex_parameter_i ) ( GLenum target, GLenum param_name, GLint param );
		void ( * gl_gen_renderbuffers ) ( GLsizei n, GLuint * render_buffers );
		void ( * gl_bind_renderbuffer ) ( GLenum target, GLuint render_buffer );
		void ( * gl_renderbuffer_storage ) ( GLenum target, GLenum internalformat, GLsizei width, GLsizei height );
		void ( * gl_framebuffer_renderbuffer ) ( GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );
		void ( * gl_framebuffer_texture ) ( GLenum target, GLenum attachment, GLuint texture, GLint level );
		void ( * gl_draw_buffers ) ( GLsizei n, const GLenum * bufs );
		void ( * gl_blit_framebuffers ) ( GLint srcX0, GLint srcY0,GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter );
		GLenum ( * gl_check_framebuffer_status ) ( GLenum target );
		GLenum ( * gl_get_error ) ();
		void ( * gl_viewport ) ( GLint x, GLint y, GLsizei width, GLsizei height );
		
		static void backing_gl_view_render ( OSAL::MacOSX::MacGLView * gl_view, void * data );
		static void backing_gl_view_resize ( OSAL::MacOSX::MacGLView * gl_view, GLint x, GLint y, GLsizei width, GLsizei height, void * data );
		#endif
		
		Rendering::Context * rendering_context;
		
		#endif
		
		#if (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_LINUX)
		
		GUIWindow ( OSAL::Linux::LinuxWindow * os_window );
		
		OSAL::Linux::LinuxWindow * os_window;
		
		Rendering::Context * rendering_context;
		
		#elif (ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

		GUIWindow ( OSAL::Windows::WinWindow * os_window );

		OSAL::Windows::WinWindow * os_window;

		#else
		#endif
		
	};
	
};

#endif
