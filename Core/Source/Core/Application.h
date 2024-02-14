#pragma once

#include "Base.h"

#include "LayerStack.h"

#include "Events/ApplicationEvent.h"
#include "Window.h"
#include <ImGui/ImGuiLayer.h>

namespace Sophon {
class Application {
public:
    Application();
    virtual ~Application();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    Window& GetWindow() { return *m_Window; }

    void Run();

    void Close();

    ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

    static Application& Get() { return *s_Instance; }

private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

private:
    Scope<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bool m_Running = true;
    bool m_Minimized = false;
    LayerStack m_LayerStack;

private:
    static Application* s_Instance;
};

// To be defined in CLIENT
Application* CreateApplication();
}
