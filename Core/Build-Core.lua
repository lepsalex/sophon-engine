project "Core"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   defines {
      "GLFW_INCLUDE_NONE"
   }

   includedirs
   {
      "Source",
      "%{IncludeDir.SPDLOG}",
      "%{IncludeDir.GLFW}",
      "%{IncludeDir.Glad}",
      "%{IncludeDir.ImGui}"
   }

    links
   {
      "GLFW",
      "Glad",
      "ImGui"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   pchheader "sfnpch.h"
   pchsource "Source/sfnpch.cpp"

   filter "system:windows"
       systemversion "latest"
       defines { "SFN_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
       defines { "SFN_DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
