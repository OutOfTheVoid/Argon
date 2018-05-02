#ifndef ARGON_RENDERING_CONTEXT_HPP
#define ARGON_RENDERING_CONTEXT_HPP

#include <argon/memory/refcounted.hpp>
#include <argon/rendering/targets.hpp>

namespace Argon::UI
{
	
	class GUIWindow;
	
}

namespace Argon::Rendering
{
	
	class FrameBuffer;
	
	class Context : public Memory::RefCounted
	{
	public:
	
		static void register_external_make_current ();
		
		void make_current () const;
		void flush_back_buffer () const;
		
		FrameBuffer * get_default_framebuffer ();
		
	private:
		
		friend class UI::GUIWindow;
		
		~Context ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		
		static Context * create_from_gl_context ( OpenGL::IGLContext * gl_context );
		
		Context ( OpenGL::IGLContext * gl_context, OpenGL::GLFunctionPointers * function_pointers );
		
		OpenGL::IGLContext * gl_context;
		
		Argon::Rendering::OpenGL::GLFunctionPointers function_ptrs;
		
		friend class FrameBuffer;
		FrameBuffer * current_bound_read_framebuffer;
		FrameBuffer * current_bound_write_framebuffer;
		FrameBuffer * default_framebuffer;
		
		static thread_local Context * current_context;
		
		#elif(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)
		
		Context ();
		void make_current () const;
		void flush_back_buffer () const;
		FrameBuffer * get_default_framebuffer ();
		
		#endif
		
	};
	
}

#endif
