#include "sfnpch.h"

#include "Application.h"

namespace Sophon {
Application::Application()
{
    m_Window = Window::Create();
    m_Window->SetEventCallback(SFN_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() { }

void Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::Run()
{
    // Event Temp
    WindowResizeEvent e(100, 100);
    SFN_CORE_ERROR(e);

    while (m_Running) {
        // call update on every layer (from bottom to top)
        for (Layer* layer : m_LayerStack)
            layer->OnUpdate();

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event& e)
{
    // Dispatch events
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(SFN_BIND_EVENT_FN(Application::OnWindowClose));

    // Propogate event "down" through layers until it is handled
    // (from top to bottom, ex: Overlay -> UI -> Debug -> Scene)
    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
        if (e.Handled)
            break;
        (*it)->OnEvent(e);
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}
}