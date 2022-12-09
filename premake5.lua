require "cmake"

workspace "Agner Fog's Optimisation Guide"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Addition and Substraction"
    location "Addition and Substraction"
    kind "consoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.asm"
    }

    includedirs
    {
        "%{prj.name}/include",
        "%{prj.name}/include/Tests"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DIST"
        symbols "On"
