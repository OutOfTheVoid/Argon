#include <argon/rendering/framebuffer.hpp>
#include <argon/rendering/context.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)
#include <argon/rendering/backends/opengl/opengl.hpp>

Argon::Rendering::FrameBuffer::FrameBuffer ( GLuint gl_framebuffer_name, Context * source_context ):
	RefCounted ( 1 ),
	gl_framebuffer_name ( gl_framebuffer_name ),
	source_context ( source_context )
{
	
	source_context -> Ref ();
	
};

Argon::Rendering::FrameBuffer::FrameBuffer ( Context * owner_of_default_framebuffer ):
	RefCounted ( 1, & default_framebuffer_delete, reinterpret_cast<void *> ( this ) ),
	gl_framebuffer_name ( 0 ),
	source_context ( owner_of_default_framebuffer )
{
}

void Argon::Rendering::FrameBuffer::default_framebuffer_delete ( void * context_instance )
{
	
	Rendering::Context * context = reinterpret_cast <Context *> ( context_instance );
	
	context -> default_framebuffer = nullptr;
	
}

Argon::Rendering::FrameBuffer::~FrameBuffer ()
{
	
	source_context -> make_current ();
	source_context -> function_ptrs.delete_framebuffers ( 1, & gl_framebuffer_name );
	
	source_context -> Deref ();
	
};

void Argon::Rendering::FrameBuffer::bind ( BindTarget target )
{
	
	source_context -> make_current ();
	
	switch ( target )
	{
		
		case kbind_target_read:
		{
			
			if ( source_context -> current_bound_read_framebuffer != this )
			{
				
				source_context -> function_ptrs.bind_framebuffer ( GL_READ_FRAMEBUFFER, gl_framebuffer_name );
				source_context -> current_bound_read_framebuffer = this;
				
			}
			
		}
		break;
		
		case kbind_target_write:
		{
			
			if ( source_context -> current_bound_write_framebuffer != this )
			{
				
				source_context -> function_ptrs.bind_framebuffer ( GL_DRAW_FRAMEBUFFER, gl_framebuffer_name );
				source_context -> current_bound_write_framebuffer = this;
				
			}
			
		}
		break;
		
		case kbind_target_read_write:
		{
			
			if ( ( source_context -> current_bound_write_framebuffer != this ) || ( source_context -> current_bound_read_framebuffer != this ) )
			{
				
				source_context -> function_ptrs.bind_framebuffer ( GL_FRAMEBUFFER, gl_framebuffer_name );
				source_context -> current_bound_write_framebuffer = this;
				source_context -> current_bound_read_framebuffer = this;
				
			}
			
		}
		break;
		
	}
	
};

void Argon::Rendering::FrameBuffer::clear ( const ClearOptions & clear_options )
{
	
	bind ( kbind_target_write );
	
	GLbitfield clear_flags = 0;
	
	if ( clear_options.clear_color_buffer )
	{
		
		source_context -> function_ptrs.clear_color ( clear_options.red, clear_options.green, clear_options.blue, clear_options.alpha );
		clear_flags |= GL_COLOR_BUFFER_BIT;
		
	}
	
	if ( clear_options.clear_depth_buffer )
	{
		
		source_context -> function_ptrs.clear_depth ( clear_options.depth );
		clear_flags |= GL_DEPTH_BUFFER_BIT;
		
	}
	
	if ( clear_flags != 0 )
		source_context -> function_ptrs.clear ( clear_flags );
	
}

#elif(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)

Argon::Rendering::FrameBuffer::FrameBuffer ()
{
};

Argon::Rendering::FrameBuffer::~FrameBuffer ()
{
};

void Argon::Rendering::FrameBuffer::bind ()
{
};

#endif
