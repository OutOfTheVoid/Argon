#ifndef ARGON_RENDERING_FRAMEBUFFER_HPP
#define ARGON_RENDERING_FRAMEBUFFER_HPP

#include <argon/rendering/rendering.hpp>
#include <argon/rendering/targets.hpp>
#include <argon/memory/refcounted.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>
#endif

namespace Argon::Rendering
{
	
	class Context;
	
	class FrameBuffer : public Memory::RefCounted
	{
	public:
		
		typedef struct
		{
			
			bool clear_color_buffer;
			float red, green, blue, alpha;
			
			bool clear_depth_buffer;
			float depth;
			
		} ClearOptions;
		
		void clear ( const ClearOptions & clear_options );
	
	protected:
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		enum BindTarget
		{
			
			kbind_target_read = 1,
			kbind_target_write = 2,
			kbind_target_read_write = 3
			
		};
		
		void bind ( BindTarget target );
		#endif
	
	private:
		
		friend class Context;
		
		~FrameBuffer ();
		
		#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
		
		FrameBuffer ( GLuint gl_framebuffer_name, Context * source_context );
		FrameBuffer ( Context * owner_of_default_framebuffer );
		
		static void default_framebuffer_delete ( void * context_instance );
		
		GLuint gl_framebuffer_name;
		Context * source_context;
		
		#elif (ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)
		
		FrameBuffer ( Context * owner_of_default_framebuffer );
		
		static void default_framebuffer_delete ( void * context_instance );
		
		Context * source_context;
		
		#endif
		
	};
	
}

#endif
