#pragma once

#include "Base.h"
#include "Events/Event.h"
#include "Window.h"

namespace Sophon {
class Application {
public:
    Application();
    virtual ~Application();

    void Run();

private:
    Scope<Window> m_Window;
    bool m_Running = true;
};

// To be defined in CLIENT
Application* CreateApplication();
}
