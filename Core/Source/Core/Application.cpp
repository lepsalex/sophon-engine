#include "sfnpch.h"

#include "Application.h"

namespace Sophon {
Application::Application()
{
    m_Window = Window::Create();
    m_Window->SetEventCallback(SFN_BIND_EVENT_FN(Application::OnEvent));
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

void Application::OnEvent(Event& e)
{
    // Dispatch events
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(SFN_BIND_EVENT_FN(Application::OnWindowClose));

    // Trace log the event
    SFN_CORE_TRACE("{0}", e);
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}
}