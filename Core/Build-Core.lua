project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files {
        "Source/**.h",
        "Source/**.cpp",
        "Vendor/stb/**.h",
        "Vendor/stb/**.cpp",
        "Vendor/glm/glm/**.hpp",
        "Vendor/glm/glm/**.inl"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs {
        "Source",
        "%{IncludeDir.SPDLOG}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.stb}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.VulkanSDK}"
    }

    links {
        "GLFW",
        "Glad",
        "ImGui"
    }

    targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    pchheader "sfnpch.h"
    pchsource "Source/sfnpch.cpp"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines {"SFN_DEBUG"}
        runtime "Debug"
        symbols "On"

        links {
			    "%{Library.ShaderC_Debug}",
			    "%{Library.SPIRV_Cross_Debug}",
			    "%{Library.SPIRV_Cross_GLSL_Debug}"
		    }

    filter "configurations:DebugProfile"
        defines {"SFN_DEBUG", "SFN_PROFILE"}
        runtime "Debug"
        symbols "On"

        links {
			    "%{Library.ShaderC_Debug}",
			    "%{Library.SPIRV_Cross_Debug}",
			    "%{Library.SPIRV_Cross_GLSL_Debug}"
		    }

    filter "configurations:Release"
        defines {"RELEASE"}
        runtime "Release"
        optimize "On"
        symbols "On"

        links	{
			    "%{Library.ShaderC_Release}",
			    "%{Library.SPIRV_Cross_Release}",
			    "%{Library.SPIRV_Cross_GLSL_Release}"
		    }

    filter "configurations:Dist"
        defines {"DIST"}
        runtime "Release"
        optimize "On"
        symbols "Off"

        links	{
			    "%{Library.ShaderC_Release}",
			    "%{Library.SPIRV_Cross_Release}",
			    "%{Library.SPIRV_Cross_GLSL_Release}"
		    }
