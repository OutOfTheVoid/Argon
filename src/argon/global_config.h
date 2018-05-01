#ifndef ARGON_GLOBAL_CONFIG_H
#define ARGON_GLOBAL_CONFIG_H

/*
*===================================================*
* Render backend selection                          *
*===================================================*
* Selecting rendering backend means choosing the
* graphics API that Argon will use on a given system,
* such as opengl vs metal on osx, or directx 12 vs 
* vulkan on windows. This is done per-target os
* because different OSs support different APIs.
*/

/*
* ARGON_RENDERING_BACKEND_*: Rendering backend values
*
* Don't change these - these are the constants which
* backend to use on a given system (supposing it's
* available )
*/
#define ARGON_RENDERING_BACKEND_DUMMY 0
#define ARGON_RENDERING_BACKEND_OPENGL 1

// Select backends here:
#define ARGON_PLATFORM_RENDERING_BACKEND_WINDOWS ARGON_RENDERING_BACKEND_DUMMY
#define ARGON_PLATFORM_RENDERING_BACKEND_LINUX ARGON_RENDERING_BACKEND_DUMMY
#define ARGON_PLATFORM_RENDERING_BACKEND_MACOSX ARGON_RENDERING_BACKEND_DUMMY

#endif
