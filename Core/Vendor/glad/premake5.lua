project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    externalincludedirs {
        "include"
    }

    filter "system:windows"
        systemversion "latest"

   	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++20"

	filter "system:macosx"
		pic "On"
		cppdialect "C++20"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
