#ifndef ARGON_OSAL_PLATFORMS_MACOSX_WINDOWSYSTEM_COMMON_H
#define ARGON_OSAL_PLATFORMS_MACOSX_WINDOWSYSTEM_COMMON_H

#include <argon/osal/osal.h>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_MACOSX)

#include <argon/osal/platforms/macosx/objc.h>

#include <stdint.h>

#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_BORDERLESS 0x00000001
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_TITLED 0x00000002
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_CLOSABLE 0x00000004
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_MINIATURIZABLE 0x00000008
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_RESIZABLE 0x00000010
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_TEXTURED_BACKGROUND 0x00000020
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_UNIFIED_TITLE_AND_TOOLBAR 0x00000040
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_FULLSCREEN 0x00000080
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_FULLSIZE_CONTENT_VIEW 0x00000100
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_UTILITY_WINDOW 0x00000200
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_DOC_MODAL_WINDOW 0x00000400
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_NONACTIVATING_PANEL 0x00000800
#define MACOSX_WINDOWSYSTEM_WINDOW_STYLE_MASK_HUD_WINDOW 0x00001000

#define MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_NORMAL 1
#define MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_MAIN_MENU 2
#define MACOSX_WINDOWSYSTEM_WINDOW_LEVEL_FLOATING 3

#define MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_LEGACY 0
#define MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_3_2 1
#define MACOSX_WINDOWSYSTEM_OPENGLVIEW_VERSION_4_1 2

#define MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_REGULAR 1
#define MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_ACCESSORY 2
#define MACOSX_WINDOWSYSTEM_APPLICATION_ACTIVATION_POLICY_PROHIBITED 3

typedef struct
{
	
	float x;
	float y;
	float width;
	float height;
	
} Argon_OSAL_MacOSX_WindowSystem_Rect;

#endif
#endif
