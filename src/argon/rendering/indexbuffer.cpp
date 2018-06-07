#include <argon/rendering/indexbuffer.hpp>
#include <argon/rendering/context.hpp>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)

Argon::Rendering::IndexBuffer::IndexBuffer ( GLuint name, Context * source_context ):
	RefCounted ( 1 ),
	name ( name )
{
	
	source_context -> Ref ();
	
}

Argon::Rendering::IndexBuffer::~IndexBuffer ()
{
	
	source_context -> function_ptrs.delete_buffers ( 1, & name );
	name = 0;
	
	source_context -> Deref ();
	
}

void Argon::Rendering::IndexBuffer::bind ()
{
	
	if ( source_context -> current_bound_index_buffer != this )
	{
		
		source_context -> function_ptrs.bind_buffer ( GL_ELEMENT_ARRAY_BUFFER, name );
		source_context -> current_bound_index_buffer = this;
			
	}
	
}

void Argon::Rendering::IndexBuffer::alloc_buffer ( buffersize_t size, bufferusagehint_t usage_hint )
{
	
	GLenum buffer_usage = GL_STATIC_DRAW;
	
	switch ( usage_hint & 0x3 )
	{
		
		case kusagehint_static:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_STATIC_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_STATIC_COPY;
					break;
					
				default:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
			}
			
		}
		break;
		
		case kusagehint_stream:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_STREAM_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_STREAM_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_STREAM_COPY;
					break;
					
				default:
					buffer_usage = GL_STREAM_DRAW;
					break;
				
			}
			
		}
		break;
		
		case kusagehint_dynamic:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_DYNAMIC_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_DYNAMIC_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_DYNAMIC_COPY;
					break;
					
				default:
					buffer_usage = GL_DYNAMIC_DRAW;
					break;
				
			}
			
		}
		break;
		
		default:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_STATIC_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_STATIC_COPY;
					break;
					
				default:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
			}
			
		}
		
	}
	
	bind ();
	
	source_context -> function_ptrs.buffer_data ( GL_ELEMENT_ARRAY_BUFFER, size, nullptr, buffer_usage );
	
}


void Argon::Rendering::IndexBuffer::write_buffer ( bufferoffset_t offset, buffersize_t size, void * data )
{
	
	bind ();
	
	source_context -> function_ptrs.sub_buffer_data ( GL_ELEMENT_ARRAY_BUFFER, offset, size, nullptr );
	
}

void Argon::Rendering::IndexBuffer::alloc_and_write_buffer ( buffersize_t size, void * data, bufferusagehint_t usage_hint )
{
	
	GLenum buffer_usage = GL_STATIC_DRAW;
	
	switch ( usage_hint & 0x3 )
	{
		
		case kusagehint_static:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_STATIC_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_STATIC_COPY;
					break;
					
				default:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
			}
			
		}
		break;
		
		case kusagehint_stream:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_STREAM_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_STREAM_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_STREAM_COPY;
					break;
					
				default:
					buffer_usage = GL_STREAM_DRAW;
					break;
				
			}
			
		}
		break;
		
		case kusagehint_dynamic:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_DYNAMIC_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_DYNAMIC_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_DYNAMIC_COPY;
					break;
					
				default:
					buffer_usage = GL_DYNAMIC_DRAW;
					break;
				
			}
			
		}
		break;
		
		default:
		{
			
			switch ( usage_hint & 0xC )
			{
				
				case kusagehint_cpu_to_gpu:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
				case kusagehint_gpu_to_cpu:
					buffer_usage = GL_STATIC_READ;
					break;
					
				case kusagehint_gpu_to_gpu:
					buffer_usage = GL_STATIC_COPY;
					break;
					
				default:
					buffer_usage = GL_STATIC_DRAW;
					break;
				
			}
			
		}
		
	}
	
	bind ();
	
	source_context -> function_ptrs.buffer_data ( GL_ELEMENT_ARRAY_BUFFER, size, data, buffer_usage );
	
}

#endif
