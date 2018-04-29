#ifndef ARGON_OSAL_PLATFORMS_WINDOWS_WINDOWS_H
#define ARGON_OSAL_PLATFORMS_WINDOWS_WINDOWS_H

#include <argon/osal/osal.h>

#if(ARGON_PLATFORM_OS == ARGON_PLATFORM_OS_VALUE_WINDOWS)

#include <argon/osal/platforms/windows/main.h>

HINSTANCE argon_osal_platforms_windows_get_application_hinstance ();

#endif
#endif
