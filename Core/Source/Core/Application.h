#pragma once

#include "Base.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Window.h"

namespace Sophon {
class Application {
public:
    Application();
    virtual ~Application();

    void OnEvent(Event& e);

    void Run();

private:
    bool OnWindowClose(WindowCloseEvent& e);

private:
    Scope<Window> m_Window;
    bool m_Running = true;
};

// To be defined in CLIENT
Application* CreateApplication();
}
