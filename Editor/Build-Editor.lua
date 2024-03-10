project "Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files {
        "Source/**.h",
        "Source/**.cpp",
        "Assets/**.glsl"
    }

    defines {
        "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
    }

    includedirs {
        "%{wks.location}/Core/Source"
    }

    externalincludedirs {
        "%{IncludeDir.SPDLOG}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.entt}",
    }

    links {
        "Core"
    }

    targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines {"SFN_DEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:DebugProfile"
        defines {"SFN_DEBUG", "SFN_PROFILE"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {"RELEASE"}
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines {"DIST"}
        runtime "Release"
        optimize "On"
        symbols "Off"
