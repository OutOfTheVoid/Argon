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
	class Texture2D;
	class VertexBuffer;
	class IndexBuffer;
	class VertexShader;
	class FragmentShader;
	class ShaderProgram;
	class VertexSpecification;
	
	class Context : public Memory::RefCounted, public Argon::Events::EventDispatcher
	{
	public:
	
		static void register_external_make_current ();
		
		void make_current () const;
		void flush_back_buffer () const;
		
		FrameBuffer * get_default_framebuffer ();
		
		FrameBuffer * create_framebuffer ();
		Texture2D * create_texture ();
		VertexBuffer * create_vertex_buffer ();
		IndexBuffer * create_index_buffer ();
		
		VertexShader * creat_vertex_shader ();
		FragmentShader * create_fragment_shader ();
		ShaderProgram * create_shader_program ();
		
		VertexSpecification * create_vertex_specification ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		static void register_external_framebuffer_bind_read ();
		static void register_external_framebuffer_bind_write ();
		static void register_external_framebuffer_bind_read_write ();
		static void register_external_vertex_buffer_bind ();
		static void register_external_index_buffer_bind ();
		
		static void register_external_texture2d_bind ();
		static void register_external_shader_program ();
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
		
		friend class Texture2D;
		Texture2D * current_bound_texture_2d;
		
		friend class VertexBuffer;
		VertexBuffer * current_bound_vertex_buffer;
		
		friend class IndexBuffer;
		IndexBuffer * current_bound_index_buffer;
		
		friend class VertexShader;
		friend class FragmentShader;
		friend class ShaderProgram;
		ShaderProgram * current_bound_shader_program;
		
		static thread_local Context * current_context;
		
		#elif(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)
		
		Context ();
		
		friend class FrameBuffer;
		FrameBuffer * default_framebuffer;
		
		#endif
		
	};
	
}

#endif
