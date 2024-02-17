include "Dependencies.lua"

workspace "Sophon Engine"
  architecture "x64"
  startproject "App"

  configurations {
    "Debug",
    "Release",
    "Dist"
  }

	flags {
		"MultiProcessorCompile"
	}

  -- Workspace-wide build options for MSVC
  filter "system:windows"
    buildoptions {"/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
  include "Core/Vendor/GLFW"
  include "Core/Vendor/Glad"
  include "Core/Vendor/imgui"
group ""

group "Engine"
  include "Core/Build-Core.lua"
group ""

include "App/Build-App.lua"
