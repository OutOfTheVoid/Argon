#ifndef ARGON_OSAL_PLATFORMS_MACOSX_WINDOWSYSTEM_HPP
#define ARGON_OSAL_PLATFORMS_MACOSX_WINDOWSYSTEM_HPP

#include <argon/osal/targets.h>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)


#include <argon/osal/platforms/macosx/objc.h>
#include <argon/osal/platforms/macosx/windowsystem_common.h>

#include <argon/geometry/geometry.hpp>
#include <argon/argon.hpp>

#include <argon/memory/refcounted.hpp>

#include <argon/rendering/backends/opengl/context.hpp>

void PlatformDeInit ();

namespace Argon::OSAL::MacOSX
{
	
	using Argon::Geometry::Rect;
	using Argon::Memory::IRefCounted;
	using Argon::Memory::RefCounted;
	
	class MacApplication
	{
	public:
		
		enum ActivationPolicy
		{
			
			kactivation_policy_regular = MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_REGULAR,
			kactivation_policy_accessory = MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_ACCESSORY,
			kactivation_policy_prohibited = MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_PROHIBITED,
			
		};
		
		static MacApplication * get_shared_instance ();
		
		void set_activation_policy ( ActivationPolicy activation_policy );
		void set_application_did_finish_launching_callback ( void ( * callback ) ( void * ), void * data );
		void run () const;
		
	private:
		
		friend void ::PlatformDeInit ();
		
		MacApplication ( ObjcID ns_application_instance, ObjcID application_delegate_instance );
		~MacApplication ();
		
		ObjcID ns_application_instance;
		ObjcID application_delegate_instance;
		
		static MacApplication * shared_instance;
		
	};
	
	class MacMenu
	{
	public:
		
		MacMenu ();
		MacMenu ( String & title );
		
	private:
		
		~MacMenu ();
		
		ObjcID ns_menu_instance;
		
	};
	
	class IMacWindowView : public virtual IRefCounted
	{
	public:
		
		enum Type
		{
			
			ktype_null,
			ktype_gl
			
		};
		
		virtual Type get_view_type () const = 0;
		
	private:
	};
	
	class MacWindow : public RefCounted
	{
	public:
		
		static const uint32_t kstyle_borderless = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_BORDERLESS;
		static const uint32_t kstyle_titled = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_TITLED;
		static const uint32_t kstyle_closable = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_CLOSABLE;
		static const uint32_t kstyle_miniaturizable = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_MINIATURIZABLE;
		static const uint32_t kstyle_resizable = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_RESIZABLE;
		static const uint32_t kstyle_textured_background = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_TEXTURED_BACKGROUND;
		static const uint32_t kstyle_unified_title_and_toolbar = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_UNIFIED_TITLE_AND_TOOLBAR;
		static const uint32_t kstyle_full_size_content_view = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_FULLSIZE_CONTENT_VIEW;
		static const uint32_t kstyle_utility_window = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_UTILITY_WINDOW;
		static const uint32_t kstyle_doc_modal_window = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_DOC_MODAL_WINDOW;
		static const uint32_t kstyle_nonactivating_panel = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_NONACTIVATING_PANEL;
		static const uint32_t kstyle_hud_window = MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_HUD_WINDOW;
		
		static MacWindow * create ( const Rect & window_rect, uint32_t style_mask );
		
		~MacWindow ();
		
		void set_view ( IMacWindowView * view );
		void make_key_and_order_front ();
		void order_front ( bool regardless_of_application_focus );
		void set_title ( const String & title );
		void set_fullscreen ( bool fullscreen );
		
		void set_should_close_handler ( bool ( * handler ) ( void * data ), void * handler_data );
		
	private:
		
		MacWindow ( ObjcID ns_window_instance, ObjcID window_controller_instance, ObjcID ns_window_delegate_instance );
		
		ObjcID ns_window_instance;
		ObjcID ns_window_controller_instance;
		ObjcID ns_window_delegate_instance;
		
		Argon_OSAL_MacOSX_WindowSystem_Rect non_fullscreen_rect;
		bool fullscreen;
		
		IMacWindowView * view;
		
		static bool should_close_handler ( void * data );
		bool ( * should_close_event_handler ) ( void * );
		void * should_close_event_handler_data;
		
	};
	
	class MacGLContextObj : public RefCounted, public virtual Argon::Rendering::OpenGL::IGLContext
	{
	public:
		
		MacGLContextObj ( ObjcID ns_opengl_context_obj_instance );
		
		void make_current () const;
		void flush_back_buffer () const;
		
		void * void_gl_get_proc_address ( const String & gl_symbol ) const;
		
		template <typename T>
		inline T get_proc_address ( const String & gl_symbol ) const
		{
			
			return reinterpret_cast<T> ( void_gl_get_proc_address ( gl_symbol ) );
			
		};
		
	private:
		
		friend class MacGLView;
		
		virtual ~MacGLContextObj ();
		
		ObjcID ns_opengl_context_obj_instance;
		
	};
	
	class MacGLView : public virtual IMacWindowView, public RefCounted
	{
	public:
		
		enum Version
		{
			
			kversion_legacy = MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_LEGACY,
			kversion_3_2 = MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_3_2,
			kversion_4_1 = MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_4_1
			
		};
			
		static MacGLView * create ( Version version, Rect frame );
		
		Type get_view_type () const;
		
		MacGLContextObj & get_context_obj ();
		const MacGLContextObj & get_context_obj () const;
		
		void set_draw_callback ( void ( * callback )( MacGLView * gl_view, void * data ), void * data );
		
		void update ();
		
		~MacGLView ();
		
	private:
		
		friend class MacWindow;
		
		MacGLView ( ObjcID ns_opengl_view_instance, ObjcID ns_opengl_context_obj_instance );
		
		ObjcID ns_opengl_view_instance;
		MacGLContextObj gl_context_obj;
		
		void * draw_callback_data;
		void ( * draw_callback )( MacGLView * gl_view, void * data );
		
		static void draw_callback_marshaller ( void * data );
		
	};
	
	class MacMetalDevice
	{
		
	private:
		
		ObjcID metal_device_instance;
			
	};
	/*
	class MacMetalView : public IMacWindowView, RefCounted
	{
	public:
		
		static MacMetalView * create (  );
		
	private:
		
		MacMetalDevice * metal_device;
		
	};
	*/
	
};


#endif
#endif
