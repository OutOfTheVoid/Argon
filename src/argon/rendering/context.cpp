#include <argon/rendering/context.hpp>
#include <argon/rendering/framebuffer.hpp>
#include <cstring>

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)

thread_local Argon::Rendering::Context * Argon::Rendering::Context::current_context = nullptr;

#if(ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_OPENGL)

void Argon::Rendering::Context::register_external_make_current ()
{
	
	current_context = nullptr;
	
}

void Argon::Rendering::Context::register_external_framebuffer_bind_read ()
{
	
	this -> current_bound_read_framebuffer = nullptr;
	
}

void Argon::Rendering::Context::register_external_framebuffer_bind_write ()
{
	
	this -> current_bound_write_framebuffer = nullptr;
	
}

void Argon::Rendering::Context::register_external_framebuffer_bind_read_write ()
{
	
	this -> current_bound_read_framebuffer = nullptr;
	this -> current_bound_write_framebuffer = nullptr;
	
}
#endif

Argon::Rendering::Context * Argon::Rendering::Context::create_from_gl_context ( OpenGL::IGLContext * gl_context, GLuint default_framebuffer_name )
{
	
	OpenGL::GLFunctionPointers function_ptrs;
	
	function_ptrs.gen_framebuffers = reinterpret_cast<decltype( function_ptrs.gen_framebuffers )> ( gl_context -> void_gl_get_proc_address ( "glGenFramebuffers" ) );
	function_ptrs.delete_framebuffers = reinterpret_cast<decltype( function_ptrs.delete_framebuffers )> ( gl_context -> void_gl_get_proc_address ( "glDeleteFramebuffers" ) );
	function_ptrs.bind_framebuffer = reinterpret_cast<decltype( function_ptrs.bind_framebuffer )> ( gl_context -> void_gl_get_proc_address ( "glBindFramebuffer" ) );
	function_ptrs.clear = reinterpret_cast<decltype( function_ptrs.clear )> ( gl_context -> void_gl_get_proc_address ( "glClear" ) );
	function_ptrs.clear_color = reinterpret_cast<decltype( function_ptrs.clear_color )> ( gl_context -> void_gl_get_proc_address ( "glClearColor" ) );
	function_ptrs.clear_depth = reinterpret_cast<decltype( function_ptrs.clear_depth )> ( gl_context -> void_gl_get_proc_address ( "glClearDepth" ) );
	
	return new Context ( gl_context, & function_ptrs, default_framebuffer_name );
	
}

Argon::Rendering::Context::Context ( OpenGL::IGLContext * gl_context, OpenGL::GLFunctionPointers * function_pointers, GLuint default_framebuffer_name ):
	RefCounted ( 1 ),
	gl_context ( gl_context ),
	function_ptrs (),
	current_bound_read_framebuffer ( nullptr ),
	current_bound_write_framebuffer ( nullptr ),
	default_framebuffer ( nullptr ),
	default_framebuffer_name ( default_framebuffer_name )
{
	
	default_framebuffer = new FrameBuffer ( this );
	
	gl_context -> Ref ();
	memcpy ( & function_ptrs, function_pointers, sizeof ( OpenGL::GLFunctionPointers ) );
	
}

Argon::Rendering::Context::~Context ()
{
	
	default_framebuffer -> Deref ();
	gl_context -> Deref ();
	
}

void Argon::Rendering::Context::make_current () const
{
	
	if ( current_context == this )
		return;
	
	gl_context -> make_current ();
	
	current_context = const_cast <Context *> ( this );
	
}

void Argon::Rendering::Context::flush_back_buffer () const
{
	
	gl_context -> flush_back_buffer ();
	
}

Argon::Rendering::FrameBuffer * Argon::Rendering::Context::get_default_framebuffer ()
{
	
	if ( default_framebuffer == nullptr )
		default_framebuffer = new FrameBuffer ( this );
	
	return default_framebuffer;
	
}

#elif (ARGON_RENDERING_BACKEND == ARGON_RENDERING_BACKEND_DUMMY)

Argon::Rendering::Context::Context ():
	RefCounted ( 1 ),
	default_framebuffer ( nullptr )
{
}

Argon::Rendering::Context::~Context ()
{
}

Argon::Rendering::FrameBuffer * Argon::Rendering::Context::get_default_framebuffer ()
{
	
	if ( default_framebuffer == nullptr )
		default_framebuffer = new FrameBuffer ( this );
	
	return default_framebuffer;
	
}

void Argon::Rendering::Context::make_current () const
{
}

void Argon::Rendering::Context::flush_back_buffer () const
{
}

#endif


