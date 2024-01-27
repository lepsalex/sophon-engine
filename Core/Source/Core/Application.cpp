#include "sfnpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"

namespace Sophon {
Application::Application()
{
    m_Window = Window::Create();
}

Application::~Application() { }
void Application::Run()
{
    // Event Temp
    WindowResizeEvent e(100, 100);
    SFN_CORE_ERROR(e);

    // Window Temp
    while (m_Running) {
        m_Window->OnUpdate();
    }
}
}