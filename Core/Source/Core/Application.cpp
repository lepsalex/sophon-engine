#include "sfnpch.h"

#include "Core/Application.h"
#include "Renderer/Renderer.h"
#include "Utils/PlatformUtils.h"

namespace Sophon {

    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification(specification)
    {
        SFN_PROFILE_FUNCTION();

        SFN_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        // Set working directory here
        if (!m_Specification.WorkingDirectory.empty())
            std::filesystem::current_path(m_Specification.WorkingDirectory);

        m_Window = Window::Create(WindowProps(m_Specification.Name));
        m_Window->SetEventCallback(SFN_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        // TODO: TEMP DISABLE
        //        m_ImGuiLayer = new ImGuiLayer();
        //        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        SFN_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        SFN_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        SFN_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::Run()
    {
        SFN_PROFILE_FUNCTION();

        while (m_Running) {
            SFN_PROFILE_SCOPE("RunLoop");

            float time = Time::GetTime();
            Timestep ts = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized) {
                {
                    SFN_PROFILE_SCOPE("LayerStack OnUpdate");
                    // call update on every layer (from bottom to top)
                    for (Layer* layer : m_LayerStack)
                        layer->OnUpdate(ts);
                }

//                TEMP DISABLED
//                m_ImGuiLayer->Begin();
//                {
//                    SFN_PROFILE_SCOPE("LayerStack OnImGuiRender");
//                    for (Layer* layer : m_LayerStack)
//                        layer->OnImGuiRender();
//                }
//
//                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        SFN_PROFILE_FUNCTION();

        // Dispatch events
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(SFN_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(SFN_BIND_EVENT_FN(Application::OnWindowResize));

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
        SFN_PROFILE_FUNCTION();

        if (e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }
}
