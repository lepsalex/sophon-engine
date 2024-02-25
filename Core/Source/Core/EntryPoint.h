#pragma once

#include "Core/Base.h"
#include "Debug/Instrumentor.h"

#ifdef SFN_PLATFORM_WINDOWS

extern Sophon::Application* Sophon::CreateApplication();

int main()
{
    Sophon::Log::Init();

    SFN_PROFILE_BEGIN_SESSION("Startup", "Sophon-Profiler-Data-Startup.json");
    auto app = Sophon::CreateApplication();
    SFN_PROFILE_END_SESSION();

    SFN_PROFILE_BEGIN_SESSION("Runtime", "Sophon-Profiler-Data-Runtime.json");
    app->Run();
    SFN_PROFILE_END_SESSION();

    SFN_PROFILE_BEGIN_SESSION("Shutdown", "Sophon-Profiler-Data-Shutdown.json");
    delete app;
    SFN_PROFILE_END_SESSION();
}

#else
#error Sophon only supports Windows!
#endif
