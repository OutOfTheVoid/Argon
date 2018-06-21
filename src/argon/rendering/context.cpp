#include <argon/rendering/context.hpp>
#include <argon/rendering/framebuffer.hpp>
#include <argon/rendering/texture2d.hpp>
#include <argon/rendering/vertexbuffer.hpp>
#include <argon/rendering/indexbuffer.hpp>
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
	
	current_context -> current_bound_read_framebuffer = nullptr;
	
}

void Argon::Rendering::Context::register_external_framebuffer_bind_write ()
{
	
	current_context -> current_bound_write_framebuffer = nullptr;
	
}

void Argon::Rendering::Context::register_external_framebuffer_bind_read_write ()
{
	
	current_context -> current_bound_read_framebuffer = nullptr;
	current_context -> current_bound_write_framebuffer = nullptr;
	
}

void Argon::Rendering::Context::register_external_texture2d_bind ()
{
	
	current_context -> current_bound_texture_2d = nullptr;
	
}


void Argon::Rendering::Context::register_external_vertex_buffer_bind ()
{
	
	current_context -> current_bound_vertex_buffer = nullptr;
	
}

void Argon::Rendering::Context::register_external_index_buffer_bind ()
{
	
	current_context -> current_bound_index_buffer = nullptr;
	
}

void Argon::Rendering::Context::register_external_shader_program ()
{
	
	current_context -> current_bound_shader_program = nullptr;
	
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
	function_ptrs.blit_framebuffers = reinterpret_cast<decltype( function_ptrs.blit_framebuffers )> ( gl_context -> void_gl_get_proc_address ( "glBlitFramebuffer" ) );
	function_ptrs.check_framebuffer_status = reinterpret_cast<decltype( function_ptrs.check_framebuffer_status )> ( gl_context -> void_gl_get_proc_address ( "glCheckFramebufferStatus" ) );
	function_ptrs.framebuffer_renderbuffer = reinterpret_cast<decltype( function_ptrs.framebuffer_renderbuffer )> ( gl_context -> void_gl_get_proc_address ( "glFramebufferRenderbuffer" ) );
	function_ptrs.framebuffer_texture = reinterpret_cast<decltype( function_ptrs.framebuffer_texture )> ( gl_context -> void_gl_get_proc_address ( "glFramebufferTexture" ) );
	
	function_ptrs.gen_textures = reinterpret_cast<decltype( function_ptrs.gen_textures )> ( gl_context -> void_gl_get_proc_address ( "glGenTextures" ) );
	function_ptrs.delete_textures = reinterpret_cast<decltype( function_ptrs.delete_textures )> ( gl_context -> void_gl_get_proc_address ( "glDeleteTextures" ) );
	function_ptrs.bind_texture = reinterpret_cast<decltype( function_ptrs.bind_texture )> ( gl_context -> void_gl_get_proc_address ( "glBindTexture" ) );
	function_ptrs.tex_image_2d = reinterpret_cast<decltype( function_ptrs.tex_image_2d )> ( gl_context -> void_gl_get_proc_address ( "glTexImage2D" ) );
	function_ptrs.tex_parameter_i = reinterpret_cast<decltype( function_ptrs.tex_parameter_i )> ( gl_context -> void_gl_get_proc_address ( "glTexParameteri" ) );
	
	function_ptrs.gen_renderbuffers = reinterpret_cast<decltype( function_ptrs.gen_renderbuffers )> ( gl_context -> void_gl_get_proc_address ( "glGenRenderbuffers" ) );
	function_ptrs.bind_renderbuffer = reinterpret_cast<decltype( function_ptrs.bind_renderbuffer )> ( gl_context -> void_gl_get_proc_address ( "glBindRenderbuffer" ) );
	function_ptrs.renderbuffer_storage = reinterpret_cast<decltype( function_ptrs.renderbuffer_storage )> ( gl_context -> void_gl_get_proc_address ( "glRenderbufferStorage" ) );
	function_ptrs.delete_renderbuffers = reinterpret_cast<decltype( function_ptrs.delete_renderbuffers )> ( gl_context -> void_gl_get_proc_address ( "glDeleteRenderbuffers" ) );
	
	function_ptrs.gen_buffers = reinterpret_cast<decltype( function_ptrs.gen_buffers )> ( gl_context -> void_gl_get_proc_address ( "glGenBuffers" ) );
	function_ptrs.delete_buffers = reinterpret_cast<decltype( function_ptrs.delete_buffers )> ( gl_context -> void_gl_get_proc_address ( "glDeleteBuffers" ) );
	function_ptrs.bind_buffer = reinterpret_cast<decltype( function_ptrs.bind_buffer )> ( gl_context -> void_gl_get_proc_address ( "glBindBuffer" ) );
	function_ptrs.buffer_data = reinterpret_cast<decltype( function_ptrs.buffer_data )> ( gl_context -> void_gl_get_proc_address ( "glBufferData" ) );
	function_ptrs.sub_buffer_data = reinterpret_cast<decltype( function_ptrs.sub_buffer_data )> ( gl_context -> void_gl_get_proc_address ( "glBufferSubData" ) );
	
	function_ptrs.create_shader = reinterpret_cast<decltype( function_ptrs.create_shader )> ( gl_context -> void_gl_get_proc_address ( "glCreateShader" ) );
	function_ptrs.delete_shader = reinterpret_cast<decltype( function_ptrs.delete_shader )> ( gl_context -> void_gl_get_proc_address ( "glDeleteShader" ) );
	function_ptrs.shader_source = reinterpret_cast<decltype( function_ptrs.shader_source )> ( gl_context -> void_gl_get_proc_address ( "glShaderSource" ) );
	function_ptrs.compile_shader = reinterpret_cast<decltype( function_ptrs.compile_shader )> ( gl_context -> void_gl_get_proc_address ( "glCompileShader" ) );
	function_ptrs.get_shader_iv = reinterpret_cast<decltype( function_ptrs.get_shader_iv )> ( gl_context -> void_gl_get_proc_address ( "glGetShaderiv" ) );
	function_ptrs.get_shader_info_log = reinterpret_cast<decltype( function_ptrs.get_shader_info_log )> ( gl_context -> void_gl_get_proc_address ( "glGetShaderInfoLog" ) );
	
	function_ptrs.create_shader_program = reinterpret_cast<decltype( function_ptrs.create_shader_program )> ( gl_context -> void_gl_get_proc_address ( "glCreateProgram" ) );
	function_ptrs.delete_shader_program = reinterpret_cast<decltype( function_ptrs.delete_shader_program )> ( gl_context -> void_gl_get_proc_address ( "glDeleteProgram" ) );
	function_ptrs.attach_shader = reinterpret_cast<decltype( function_ptrs.attach_shader )> ( gl_context -> void_gl_get_proc_address ( "glAttachShader" ) );
	function_ptrs.detach_shader = reinterpret_cast<decltype( function_ptrs.detach_shader )> ( gl_context -> void_gl_get_proc_address ( "glDetachShader" ) );
	function_ptrs.link_program = reinterpret_cast<decltype( function_ptrs.link_program )> ( gl_context -> void_gl_get_proc_address ( "glLinkProgram" ) );
	function_ptrs.get_program_iv = reinterpret_cast<decltype( function_ptrs.get_program_iv )> ( gl_context -> void_gl_get_proc_address ( "glGetProgramiv" ) );
	function_ptrs.bind_program = reinterpret_cast<decltype( function_ptrs.bind_program )> ( gl_context -> void_gl_get_proc_address ( "glBindProgram" ) );
	
	function_ptrs.draw_buffers = reinterpret_cast<decltype( function_ptrs.draw_buffers )> ( gl_context -> void_gl_get_proc_address ( "glDrawBuffers" ) );
	function_ptrs.viewport = reinterpret_cast<decltype( function_ptrs.viewport )> ( gl_context -> void_gl_get_proc_address ( "glViewport" ) );
	
	function_ptrs.get_error = reinterpret_cast<decltype( function_ptrs.get_error )> ( gl_context -> void_gl_get_proc_address ( "glGetError" ) );
	
	return new Context ( gl_context, & function_ptrs, default_framebuffer_name );
	
}

Argon::Rendering::Context::Context ( OpenGL::IGLContext * gl_context, OpenGL::GLFunctionPointers * function_pointers, GLuint default_framebuffer_name ):
	RefCounted ( 1 ),
	gl_context ( gl_context ),
	function_ptrs (),
	current_bound_read_framebuffer ( nullptr ),
	current_bound_write_framebuffer ( nullptr ),
	default_framebuffer ( nullptr ),
	default_framebuffer_name ( default_framebuffer_name ),
	current_bound_index_buffer ( nullptr ),
	current_bound_vertex_buffer ( nullptr ),
	current_bound_shader_program ( nullptr )
{
	
	default_framebuffer = new FrameBuffer ( this );
	
	gl_context -> ref ();
	memcpy ( & function_ptrs, function_pointers, sizeof ( OpenGL::GLFunctionPointers ) );
	
}

Argon::Rendering::Context::~Context ()
{
	
	default_framebuffer -> deref ();
	gl_context -> deref ();
	
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

Argon::Rendering::FrameBuffer * Argon::Rendering::Context::create_framebuffer ()
{
	
	make_current ();
	
	GLuint framebuffer_name = 0;
	function_ptrs.gen_framebuffers ( 1, & framebuffer_name );
	
	if ( framebuffer_name == 0 )
		return nullptr;
	
	return new FrameBuffer ( framebuffer_name, this );
	
}

Argon::Rendering::Texture2D * Argon::Rendering::Context::create_texture ()
{
	
	make_current ();
	
	GLuint texture_name = 0;
	function_ptrs.gen_textures ( 1, & texture_name );
	
	if ( texture_name == 0 )
		return nullptr;
	
	Texture2D * new_tex = new Texture2D ( texture_name, this );
	//new_tex -> set_size ( width, height, level );
	return new_tex;
	
}

Argon::Rendering::VertexBuffer * Argon::Rendering::Context::create_vertex_buffer ()
{
	
	make_current ();
	
	GLuint buffer_name = 0;
	function_ptrs.gen_buffers ( 1, & buffer_name );
	
	if ( buffer_name == 0 )
		return nullptr;
		
	return new VertexBuffer ( buffer_name, this );
	
}

Argon::Rendering::IndexBuffer * Argon::Rendering::Context::create_index_buffer ()
{
	
	make_current ();
	
	GLuint buffer_name = 0;
	function_ptrs.gen_buffers ( 1, & buffer_name );
	
	if ( buffer_name == 0 )
		return nullptr;
		
	return new IndexBuffer ( buffer_name, this );
	
}

Argon::Rendering::VertexSpecification * Argon::Rendering::Context::create_vertex_specification ()
{
	
	make_current ();
	
	GLuint buffer_name = 0;
	function_ptrs.gen_vertex_arrays ( 1, & buffer_name );
	
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


