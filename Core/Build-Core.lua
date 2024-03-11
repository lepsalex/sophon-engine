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

pchheader "sfnpch.h"

filter "system:windows"
  systemversion "latest"

  pchsource "Source/sfnpch.cpp"

  externalincludedirs {
    "%{IncludeDir.VulkanSDK}",
  }

filter "system:macosx"
  files {
    "Vendor/metal-cpp/**.hpp"
  }

  externalincludedirs {
    "%{IncludeDir.VulkanSDKmacOS}",
    "%{IncludeDir.metalCPP}",
  }

  links {
    "%{LibraryMacOS.Vulkan}",
		"%{LibraryMacOS.ShaderC}",
		"%{LibraryMacOS.SPIRV_Cross}",
		"%{LibraryMacOS.SPIRV_Tools}"
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
