#include "sfnpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"

namespace Sophon {
Application::Application() { }

Application::~Application() { }
void Application::Run()
{
    WindowResizeEvent e(100, 100);
    SFN_CORE_ERROR(e);

    while (true);
}
}