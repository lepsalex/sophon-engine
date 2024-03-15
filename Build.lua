include "SolutionItems.lua"
include "Dependencies.lua"

workspace "Sophon Engine"
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

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

-- Workspace-wide build options for MSVC
filter "system:windows"
architecture "x64"
buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

-- Workspace-wide build options for MacOS Xcode
filter "system:macosx"
architecture "universal"
links {
    "Foundation.framework",
    "Metal.framework",
    "QuartzCore.framework",
    "Cocoa.framework",
    "IOKit.framework"
}

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
