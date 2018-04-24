-- premake5.lua
workspace "Argon"
   configurations { "Debug", "Release" }
   
project "GFXTest"
	kind "ConsoleApp"
	cppdialect "C++17"
	cdialect "C11"
	targetdir "bin/GFXDebug/%{cfg.buildcfg}"
	
	files { "src/argon/**.h", "src/argon/**.c", "src/argon/**.cpp", "src/tests/GFXTestMain.cpp" }
	includedirs { "src" }
	
	filter { "files:**.m" }
		buildmessage '%{file.basename}.m'
		prebuildcommands { 'llvm-gcc "%{file.relpath}" -c -o "%{cfg.objdir}/%{file.basename}.o"' }
		buildoutputs { "%{cfg.objdir}/%{file.basename}.o" }
	
	filter { "system:macosx" }
		files { "src/**.m" }
		links { "OpenGL.framework", "Cocoa.framework", "Foundation.framework", "AppKit.framework", "objc" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	