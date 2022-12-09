require "cmake"

workspace "AFOG"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Addition_and_Substraction"
    location "Addition_and_Substraction"
    kind "consoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",
        -- "%{prj.name}/include/Tests/**.h",
        "%{prj.name}/src/**.cpp",
        -- "%{prj.name}/src/Tests/**.cpp",
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
