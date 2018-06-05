#ifndef ARGON_RENDERING_CONTEXT_HPP
#define ARGON_RENDERING_CONTEXT_HPP

#include <argon/memory/refcounted.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/events/eventdispatcher.hpp>

namespace Argon::UI
{
	
	class GUIWindow;
	
}

namespace Argon::Rendering
{
	
	class FrameBuffer;
	
	class Context : public Memory::RefCounted, public Argon::Events::EventDispatcher
	{
	public:
	
		static void register_external_make_current ();
		
		void make_current () const;
		void flush_back_buffer () const;
		
		FrameBuffer * get_default_framebuffer ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		void register_external_framebuffer_bind_read ();
		void register_external_framebuffer_bind_write ();
		void register_external_framebuffer_bind_read_write ();
		#endif
		
	private:
		
		friend class UI::GUIWindow;
		
		~Context ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		
		static Context * create_from_gl_context ( OpenGL::IGLContext * gl_context, GLuint default_framebuffer_name );
		
		Context ( OpenGL::IGLContext * gl_context, OpenGL::GLFunctionPointers * function_pointers, GLuint default_framebuffer_name );
		
		OpenGL::IGLContext * gl_context;
		GLuint default_framebuffer_name;
		
		Argon::Rendering::OpenGL::GLFunctionPointers function_ptrs;
		
		friend class FrameBuffer;
		FrameBuffer * current_bound_read_framebuffer;
		FrameBuffer * current_bound_write_framebuffer;
		FrameBuffer * default_framebuffer;
		
		static thread_local Context * current_context;
		
		#elif(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)
		
		Context ();
		
		friend class FrameBuffer;
		FrameBuffer * default_framebuffer;
		
		#endif
		
	};
	
}

#endif
