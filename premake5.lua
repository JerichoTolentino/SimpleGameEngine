workspace "Hazel"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SimpleGameEngine"
    location "SimpleGameEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    include
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.17134.0"

        defines
        {
            "GLEW_STATIC",
            "SGE_PLATFORM_WINDOWS",
            "SGE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "SGE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SGE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "SGE_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    include
    {
        "%{prj.name}/vendor/spdlog/include",
        "Hazel/src"
    }

    links
    {
        "SimpleGameEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.17134.0"

        defines
        {
            "SGE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SGE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SGE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "SGE_DIST"
        optimize "On"
