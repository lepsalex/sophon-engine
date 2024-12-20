#pragma once

#include "Core/Base.h"
#include "Debug/Instrumentor.h"

#if defined(SFN_PLATFORM_WINDOWS) || defined(SFN_PLATFORM_MACOS)

extern Sophon::Application* Sophon::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    Sophon::Log::Init();

    SFN_PROFILE_BEGIN_SESSION("Startup", "Sophon-Profiler-Data-Startup.json");
    auto app = Sophon::CreateApplication({ argc, argv });
    SFN_PROFILE_END_SESSION();

    SFN_PROFILE_BEGIN_SESSION("Runtime", "Sophon-Profiler-Data-Runtime.json");
    app->Run();
    SFN_PROFILE_END_SESSION();

    SFN_PROFILE_BEGIN_SESSION("Shutdown", "Sophon-Profiler-Data-Shutdown.json");
    delete app;
    SFN_PROFILE_END_SESSION();
}

#else
#error Sophon only supports Windows and macOS!
#endif
