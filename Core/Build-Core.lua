project "Core"
kind "StaticLib"
language "C++"
cppdialect "C++20"
targetdir "Binaries/%{cfg.buildcfg}"
staticruntime "off"

files {
  "Source/**.h",
  "Source/**.hpp",
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
}

externalincludedirs {
  "%{IncludeDir.stb}",
  "%{IncludeDir.glm}",
  "%{IncludeDir.SPDLOG}",
  "%{IncludeDir.GLFW}",
  "%{IncludeDir.Glad}",
  "%{IncludeDir.ImGui}",
  "%{IncludeDir.entt}"
}

links {
  "GLFW",
  "Glad",
  "ImGui"
}

targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

filter "system:windows"
  systemversion "latest"

  pchheader "sfnpch.h"
  pchsource "Source/sfnpch.cpp"

  externalincludedirs {
    "%{IncludeDir.VulkanSDK}",
  }

filter "system:macosx"

    pchheader "Source/sfnpch.h"

    files {
        "Source/**.mm",
    }

    externalincludedirs {
        "%{IncludeDir.VulkanSDKmacOS}",
        "%{IncludeDir.metalCPP}",
    }

    links {
        "%{LibraryDirMacOS.VulkanFramework}/vulkan.framework",
        "%{LibraryMacOS.ShaderC}",
        "%{LibraryMacOS.SPIRV_Cross}",
    }

    sysincludedirs {
        "%{LibraryDirMacOS.VulkanFramework}/vulkan.framework/Headers", -- need to explicitly add path to framework headers
    }

    frameworkdirs {
        "%{LibraryDirMacOS.VulkanFramework}",
    }

    embedAndSign {
        "vulkan.framework" -- bundle the framework into the built .app and sign with your certificate
    }

    xcodebuildsettings {
        ["MACOSX_DEPLOYMENT_TARGET"] = "14.4",
        ["PRODUCT_BUNDLE_IDENTIFIER"] = 'com.projectsophon.sophonengine',
        ["CODE_SIGN_STYLE"] = "Automatic",
        ["LD_RUNPATH_SEARCH_PATHS"] = "$(inherited) @executable_path/../Frameworks", -- tell the executable where to find the frameworks. Path is relative to executable location inside .app bundle
    }

filter "Debug"
  defines {"SFN_DEBUG"}
  runtime "Debug"
  symbols "On"

filter {"Debug", "system:windows"}
  links {
		"%{Library.ShaderC_Debug}",
		"%{Library.SPIRV_Cross_Debug}",
		"%{Library.SPIRV_Cross_GLSL_Debug}"
	}

filter "DebugProfile"
  defines {"SFN_DEBUG", "SFN_PROFILE"}
  runtime "Debug"
  symbols "On"

filter {"DebugProfile", "system:windows"}
  links {
		"%{Library.ShaderC_Debug}",
		"%{Library.SPIRV_Cross_Debug}",
		"%{Library.SPIRV_Cross_GLSL_Debug}"
	}

filter "Release"
  defines {"RELEASE"}
  runtime "Release"
  optimize "On"
  symbols "On"

filter {"Release", "system:windows"}
  links	{
		"%{Library.ShaderC_Release}",
		"%{Library.SPIRV_Cross_Release}",
		"%{Library.SPIRV_Cross_GLSL_Release}"
	}

filter "Dist"
  defines {"DIST"}
  runtime "Release"
  optimize "On"
  symbols "Off"

filter {"Dist", "system:windows"}
  links	{
		"%{Library.ShaderC_Release}",
		"%{Library.SPIRV_Cross_Release}",
		"%{Library.SPIRV_Cross_GLSL_Release}"
	}
