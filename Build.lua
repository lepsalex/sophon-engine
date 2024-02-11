include "Dependencies.lua"

workspace "Sophon Engine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
  include "Core/Vendor/GLFW"
  include "Core/Vendor/Glad"
group ""

group "Engine"
	include "Core/Build-Core.lua"
group ""

include "App/Build-App.lua"
