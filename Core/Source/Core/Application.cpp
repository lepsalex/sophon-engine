#include "sfnpch.h"

#include "Core/Application.h"
#include "Renderer/Renderer.h"
#include "Utils/PlatformUtils.h"

namespace Sophon {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        SFN_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(SFN_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
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
        while (m_Running) {

            float time = Time::GetTime();
            Timestep ts = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized) {
                // call update on every layer (from bottom to top)
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(ts);

                m_ImGuiLayer->Begin();

                for (Layer* layer : m_LayerStack)
                    layer->OnImGuiRender();

                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::OnEvent(Event& e)
    {
        // Dispatch events
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(SFN_BIND_EVENT_FN(Application::OnWindowClose));

        // Propagate event "down" through layers until it is handled
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

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;

        return false;
    }
}
