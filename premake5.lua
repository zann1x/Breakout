workspace "Breakout"
    architecture "x86"
    configurations {
        "Debug",
        "Release"
    }
    startproject "Breakout"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

IncludeDir = {}
IncludeDir["SFML"] = "Dependencies/SFML/include"

LibDir = {}
LibDir["SFML"] = "Dependencies/SFML/lib"

project "Breakout"
    location "Breakout"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir)

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{IncludeDir.SFML}"
    }

    libdirs {
        "%{LibDir.SFML}"
    }

    links {
        "opengl32.lib",
        "freetype.lib",
        "winmm.lib",
        "gdi32.lib"
    }

    defines {
        "SFML_STATIC"
    }

    filter "configurations:Debug"
        defines { "_DEBUG" }
        links {
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib",
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        links {
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib",
        }
        runtime "Release"
        optimize "on"