#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>
#include <argon/osal/platforms/macosx/windowsystem_common.h>
#import <mach-o/dyld.h>
#import <stdlib.h>

@interface Argon_OSAL_MacOSX_ExtNSOpenGLView : NSOpenGLView
{
	
	@public void * draw_callback_data;
	@public void ( * draw_callback )( void * );
	@public void * resize_callback_data;
	@public void ( * resize_callback )( void *, GLint, GLint, GLsizei, GLsizei );
	
}
@end

@implementation Argon_OSAL_MacOSX_ExtNSOpenGLView

-(void) drawRect:(NSRect)dirtyRect
{
	
	if ( self -> draw_callback )
		draw_callback ( self -> draw_callback_data );
	
}

#include <stdio.h>

-(void) reshape
{
	
	printf ( "reshape\n" );
	
	NSRect bounds = [self bounds];
	
	if ( self -> resize_callback )
		resize_callback ( self -> resize_callback_data, NSMinX ( bounds ), NSMinY ( bounds ), NSWidth ( bounds ), NSHeight ( bounds ) );
	
}

@end

@interface Argon_OSAL_MacOSX_NSApplicationDelegateExt : NSObject <NSApplicationDelegate>
{
	
	@public void * app_did_finish_launching_callback_data;
	@public void ( * app_did_finish_launching_callback )( void * );
	
}
@end

@implementation Argon_OSAL_MacOSX_NSApplicationDelegateExt

-(instancetype) init
{
	
	[super init];
	
	self -> app_did_finish_launching_callback = nil;
	self -> app_did_finish_launching_callback_data = nil;
	
	return self;
	
}

-(void) applicationDidFinishLaunching:(NSNotification *)notification
{
	
	if ( self -> app_did_finish_launching_callback )
		self -> app_did_finish_launching_callback ( self -> app_did_finish_launching_callback_data );
	
}

@end

@interface Argon_OSAL_MacOSX_NSWindowDelegateExt : NSObject <NSWindowDelegate>
{

	@public Argon_OSAL_MacOSX_WindowSystem_WindowDelegate_Event_Callbacks callbacks;
	
}
@end

@implementation Argon_OSAL_MacOSX_NSWindowDelegateExt

-(instancetype) init
{
	
	[super init];
	
	memset ( (void *) & ( self -> callbacks ), 0, sizeof ( Argon_OSAL_MacOSX_WindowSystem_WindowDelegate_Event_Callbacks ) );
	
	return self;
	
}

-(BOOL) windowShouldClose:(NSWindow *)sender
{
	
	if ( self -> callbacks.window_should_close_handler != nil )
		return self -> callbacks.window_should_close_handler ( self -> callbacks.window_should_close_handler_data ) ? YES : NO;
	
	return YES;
	
}

-(void) windowWillClose:(NSWindow *)sender
{
	
	if ( self -> callbacks.window_will_close_handler != nil )
		self -> callbacks.window_will_close_handler ( self -> callbacks.window_will_close_handler_data );
	
}

@end

extern id argon_osal_macosx_macapplication_getsharedinstance ( id * delegate_instance )
{
	
	NSApplication * shared_application = [NSApplication sharedApplication];
	
	* delegate_instance = [shared_application delegate];
	
	if ( * delegate_instance == nil )
	{
		
		* delegate_instance =  [[Argon_OSAL_MacOSX_NSApplicationDelegateExt alloc] init];
		[shared_application setDelegate:* delegate_instance];
		
	}
	
	return shared_application;
	
}

extern void argon_osal_macosx_macapplication_set_did_finish_launching_callback ( void ( * callback ) ( void * ), void * data )
{
	
	Argon_OSAL_MacOSX_NSApplicationDelegateExt * delegate = nil;
	
	argon_osal_macosx_macapplication_getsharedinstance ( (id *) & delegate );
	
	delegate -> app_did_finish_launching_callback_data = data;
	delegate -> app_did_finish_launching_callback = callback;
	
}

extern void argon_osal_macosx_macapplication_set_activation_policy ( unsigned int activation_policy )
{
	
	NSApplicationActivationPolicy policy = NSApplicationActivationPolicyProhibited;
	
	switch ( activation_policy )
	{
		
	case MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_REGULAR:
		policy = NSApplicationActivationPolicyRegular;
		break;
		
	case MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_ACCESSORY:
		policy = NSApplicationActivationPolicyAccessory;
		break;
		
	default:
		break;
		
	}
	
	[NSApp setActivationPolicy:policy];
	
}

extern id argon_osal_macosx_macmenu_create_0 ()
{
	
	return [[NSMenu alloc] init];
	
}

extern id argon_osal_macosx_macmenu_create_1 ( const char * title )
{
	
	NSString * ns_string_title = [[NSString alloc] initWithUTF8String:title];
	
	id menu_out = [[NSMenu alloc] initWithTitle:ns_string_title];
	
	[ns_string_title release];
	
	return menu_out;
	
}

#include <string.h>

extern id argon_osal_macosx_macwindow_create_1 ( Argon_OSAL_MacOSX_WindowSystem_Rect content_rect, uint32_t style_flags, id * window_controller_instance, id * window_delegate_instance )
{
	
	NSRect content_frame = NSMakeRect ( content_rect.x, content_rect.y, content_rect.width, content_rect.height );
	
	NSWindowStyleMask style_mask =
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_BORDERLESS ) ? NSWindowStyleMaskBorderless : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_TITLED ) ? NSWindowStyleMaskTitled : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_CLOSABLE ) ? NSWindowStyleMaskClosable : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_MINIATURIZABLE ) ? NSWindowStyleMaskMiniaturizable : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_RESIZABLE ) ? NSWindowStyleMaskResizable : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_TEXTURED_BACKGROUND ) ? NSWindowStyleMaskTexturedBackground : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_UNIFIED_TITLE_AND_TOOLBAR ) ? NSWindowStyleMaskUnifiedTitleAndToolbar : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_FULLSCREEN ) ? NSWindowStyleMaskFullScreen : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_FULLSIZE_CONTENT_VIEW ) ? NSWindowStyleMaskFullSizeContentView : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_UTILITY_WINDOW ) ? NSWindowStyleMaskUtilityWindow : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_DOC_MODAL_WINDOW ) ? NSWindowStyleMaskDocModalWindow : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_NONACTIVATING_PANEL ) ? NSWindowStyleMaskNonactivatingPanel : 0 ) |
		( ( style_flags & MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_HUD_WINDOW ) ? NSWindowStyleMaskHUDWindow : 0 );
	
	NSWindow * ns_window_instance = [[NSWindow alloc] initWithContentRect:content_frame styleMask:style_mask backing:NSBackingStoreBuffered defer:NO];
	
	if ( ns_window_instance == nil )
		return nil;
	
	* window_controller_instance = [[NSWindowController alloc] initWithWindow:ns_window_instance];
	
	if ( * window_controller_instance == nil )
	{
		
		[ns_window_instance release];
		return nil;
		
	}
	
	* window_delegate_instance = [[Argon_OSAL_MacOSX_NSWindowDelegateExt alloc] init];
	
	if ( * window_delegate_instance == nil )
	{
		
		[ns_window_instance release];
		[* window_controller_instance release];
		* window_controller_instance = nil;
		return nil;
		
	}
	
	[ns_window_instance setDelegate:* window_delegate_instance];
	
	return ns_window_instance;
	
};

extern void argon_osal_macosx_macwindow_delegate_set_callbacks ( id ns_window_delegate_instance, const Argon_OSAL_MacOSX_WindowSystem_WindowDelegate_Event_Callbacks * callbacks )
{
	
	memcpy ( & ( ( (Argon_OSAL_MacOSX_NSWindowDelegateExt *) ns_window_delegate_instance ) -> callbacks ), callbacks, sizeof ( Argon_OSAL_MacOSX_WindowSystem_WindowDelegate_Event_Callbacks ) );
	
}

extern void argon_osal_macosx_macwindow_set_view ( id ns_window_instance, id view_instance )
{
	
	[(NSWindow *)ns_window_instance setContentView:view_instance];
	//[(NSWindow *)ns_window_instance setDelegate:view_instance];
	
};


extern void argon_osal_macosx_macwindow_set_title ( ObjcID ns_window_instance, const char * title )
{
	
	NSString * title_string = [[NSString alloc] initWithUTF8String:title];
	
	[(NSWindow *)ns_window_instance setTitle:title_string];
	
	[title_string release];
	
};

extern void argon_osal_macosx_macwindow_make_key_and_order_front ( id ns_window_instance )
{
	
	[(NSWindow *)ns_window_instance makeKeyAndOrderFront:nil];
	
};

extern void argon_osal_macosx_macwindow_order_front ( id ns_window_instance, bool regardless_of_application_focus )
{
	
	if ( regardless_of_application_focus )
		[(NSWindow *)ns_window_instance orderFrontRegardless];
	else
		[(NSWindow *)ns_window_instance orderFront:nil];
	
};

extern void argon_osal_macosx_macwindow_get_frame ( id ns_window_instance, Argon_OSAL_MacOSX_WindowSystem_Rect * frame_rect )
{
	
	NSRect frame = [(NSWindow *)ns_window_instance frame];
	
	frame_rect -> x = frame.origin.x;
	frame_rect -> y = frame.origin.y;
	frame_rect -> width = frame.size.width;
	frame_rect -> height = frame.size.height;
	
};

extern void argon_osal_macosx_macwindow_set_frame ( id ns_window_instance, Argon_OSAL_MacOSX_WindowSystem_Rect frame_rect )
{
	
	NSRect frame;
	frame.origin.x = frame_rect.x;
	frame.origin.y = frame_rect.y;
	frame.size.width = frame_rect.width;
	frame.size.height = frame_rect.height;
	
	[(NSWindow *)ns_window_instance setFrame:frame display:YES animate:NO];
	
};

extern void argon_osal_macosx_macwindow_set_frame_to_screen ( id ns_window_instance )
{
	
	NSRect main_display_rect = [[NSScreen mainScreen] frame];
	
	[(NSWindow *)ns_window_instance setFrame:main_display_rect display:YES animate:NO];
	[(NSWindow *)ns_window_instance setHidesOnDeactivate:YES];
	
};

extern void argon_osal_macosx_macwindow_set_hides_on_deactivate ( id ns_window_instance, bool hides_on_deactivate )
{
	
	[(NSWindow *)ns_window_instance setHidesOnDeactivate:hides_on_deactivate];
	
}

extern void argon_osal_macosx_macwindow_set_window_level_plus ( id ns_window_instance, uint32_t level, uint32_t addition )
{
	
	NSWindowLevel window_level;
	
	switch ( level )
	{
		
		case MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_NORMAL:
			window_level = NSNormalWindowLevel + addition;
			break;
			
		case MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_MAIN_MENU:
			window_level = NSMainMenuWindowLevel + addition;
			break;
			
		case MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_FLOATING:
			window_level = NSFloatingWindowLevel + addition;
			break;
			
		default:
			return;
		
	}
	
	[(NSWindow *)ns_window_instance setLevel:window_level];
	
};

extern id argon_osal_macosx_openglview_create ( unsigned int version, Argon_OSAL_MacOSX_WindowSystem_Rect frame_rect, ObjcID * ns_opengl_context_obj_instance )
{
	
	unsigned int version_code = NSOpenGLProfileVersionLegacy;
	
	switch ( version )
	{
	case MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_LEGACY:
		break;
		
	case MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_3_2:
		version_code = NSOpenGLProfileVersion3_2Core;
		break;
		
	case MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_4_1:
		version_code = NSOpenGLProfileVersion4_1Core;
		break;
		
	default:
		break;
		
	}
	
	NSOpenGLPixelFormatAttribute pixel_format_attributes [] =
	{
		NSOpenGLPFAOpenGLProfile, (NSOpenGLPixelFormatAttribute) version_code,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFANoRecovery,
		0
	};
	
	NSRect objc_frame_rect = NSMakeRect ( frame_rect.x, frame_rect.y, frame_rect.width, frame_rect.height );
	
	NSOpenGLPixelFormat * pixel_format = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixel_format_attributes];
	Argon_OSAL_MacOSX_ExtNSOpenGLView * ns_opengl_view_instance = [[Argon_OSAL_MacOSX_ExtNSOpenGLView alloc] initWithFrame:objc_frame_rect pixelFormat:pixel_format];
	* ns_opengl_context_obj_instance = [ns_opengl_view_instance openGLContext];
	[pixel_format release];
	
	return ns_opengl_view_instance;
	
};

extern void argon_osal_macosx_openglview_set_draw_callback ( id ns_opengl_view_instance, void ( * callback )( void * ), void * callback_data )
{
	
	( (Argon_OSAL_MacOSX_ExtNSOpenGLView *) ns_opengl_view_instance ) -> draw_callback = callback;
	( (Argon_OSAL_MacOSX_ExtNSOpenGLView *) ns_opengl_view_instance ) -> draw_callback_data = callback_data;
	
}

extern void argon_osal_macosx_openglview_set_resize_callback ( id ns_opengl_view_instance, void ( * callback )( void *, GLint, GLint, GLsizei, GLsizei ), void * callback_data )
{
	
	( (Argon_OSAL_MacOSX_ExtNSOpenGLView *) ns_opengl_view_instance ) -> resize_callback = callback;
	( (Argon_OSAL_MacOSX_ExtNSOpenGLView *) ns_opengl_view_instance ) -> resize_callback_data = callback_data;
	
}

extern id argon_osal_macosx_opengl_context_create_share ( id share_ns_opengl_context_obj )
{
	
	NSOpenGLPixelFormat * pixel_format = [ (NSOpenGLContext *) share_ns_opengl_context_obj pixelFormat];
	return [[NSOpenGLContext alloc] initWithFormat:pixel_format shareContext:share_ns_opengl_context_obj];
	
}

extern void argon_osal_macosx_opengl_context_make_current ( id ns_opengl_context_obj_instance )
{
	
	[ (NSOpenGLContext *) ns_opengl_context_obj_instance makeCurrentContext];
	
}

extern void argon_osal_macosx_opengl_context_flush ( id ns_opengl_context_obj_instance )
{
	
	[(NSOpenGLContext *)ns_opengl_context_obj_instance flushBuffer];
	
}

extern void argon_osal_macosx_openglview_update ( ObjcID ns_opengl_view_instance )
{
	
	[(NSOpenGLView *)ns_opengl_view_instance update];
	
}

extern void argon_osal_macosx_windowsystem_release ( id ns_window_instance )
{
	
	[ns_window_instance release];
	
}

extern void argon_osal_macosx_macapplication_run ()
{
	
	[NSApp run];
	
}

extern void argon_osal_macosx_macapplication_stop ()
{
	
	[NSApp stop:nil];
	
}
