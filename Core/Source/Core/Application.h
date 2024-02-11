#pragma once

#include "Base.h"

#include "LayerStack.h"

#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Sophon {
class Application {
public:
    Application();
    virtual ~Application();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    void Run();

private:
    bool OnWindowClose(WindowCloseEvent& e);

private:
    Scope<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
};

// To be defined in CLIENT
Application* CreateApplication();
}
