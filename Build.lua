include "SolutionItems.lua"
include "Dependencies.lua"

workspace "Sophon Engine"
  architecture "x64"
  startproject "Editor"

  solutionitems {
    "README.md",
	".editorconfig",
    ".gitignore",
    ".clang-format",
    ["Premake"] = {
      "./Build.lua",
      "./Dependencies.lua",
      "./Core/Build-Core.lua",
      "./Editor/Build-Editor.lua",
      "./App/Build-App.lua",
      "./SolutionItems.lua",
    }
  }

  configurations {
    "Debug",
    "DebugProfile",
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
  include "Editor/Build-Editor.lua"
group ""

include "App/Build-App.lua"
