#include "sfnpch.h"
#include "Application.h"

// TODO: TEMP RENDERING TEST
#include "Renderer/Renderer.h"

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

        // TODO: TEMP RENDERING TEST START
        m_TriangleVertexArray = VertexArray::Create();
        float triangle_vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.9f, 0.4f, 0.4f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.4f, 0.9f, 0.4f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.4f, 0.4f, 0.9f, 1.0f, // clang-format-ignore
        };
        auto triangleVertexBuffer = VertexBuffer::Create(triangle_vertices, sizeof(triangle_vertices));
        triangleVertexBuffer->SetLayout(BufferLayout {
            { BufferElement(ShaderDataType::Float3, "a_Position") },
            { BufferElement(ShaderDataType::Float4, "a_Color") } });
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
        uint32_t triangleIndices[3] = { 0, 1, 2 };
        m_TriangleVertexArray->SetIndexBuffer(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

        m_SquareVertexArray = VertexArray::Create();
        float square_vertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f, // clang-format-ignore
        };
        auto squareVertexBuffer = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
        squareVertexBuffer->SetLayout(BufferLayout {
            { BufferElement(ShaderDataType::Float3, "a_Position") } });
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        m_SquareVertexArray->SetIndexBuffer(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
			    #version 330 core
			
			    layout(location = 0) in vec3 a_Position;
                layout(location = 1) in vec4 a_Color;
			    
                out vec3 v_Position;
                out vec4 v_Color;
			    
                void main()
			    {
				    v_Position = a_Position;
                    v_Color = a_Color;
				    gl_Position = vec4(a_Position, 1.0);	
			    }
		    )";

        std::string fragmentSrc = R"(
			    #version 330 core
			
                layout(location = 0) out vec4 color;

			    in vec3 v_Position;
                in vec4 v_Color;

			    void main()
			    {
				    color = v_Color;
			    }
		    )";

        m_Shader = CreateRef<OpenGLShader>("Shader", vertexSrc, fragmentSrc);

        std::string simpleColorVertexSrc = R"(
			    #version 330 core
			
			    layout(location = 0) in vec3 a_Position;
			    
                out vec3 v_Position;
			    
                void main()
			    {
				    v_Position = a_Position;
				    gl_Position = vec4(a_Position, 1.0);	
			    }
		    )";

        std::string simpleColorFragmentSrc = R"(
			    #version 330 core
			
                layout(location = 0) out vec4 color;

			    in vec3 v_Position;

			    void main()
			    {
				    color = vec4(0.2, 0.3, 0.8, 1.0);
			    }
		    )";

        m_SimpleColorShader = CreateRef<OpenGLShader>("SimpleColorShader", simpleColorVertexSrc, simpleColorFragmentSrc);
        // TODO: TEMP RENDERING TEST END
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
            if (!m_Minimized) {

                // TODO: TEMP RENDERING TEST START
                RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
                RenderCommand::Clear();

                Renderer::Submit(m_SimpleColorShader, m_SquareVertexArray);
                Renderer::Submit(m_Shader, m_TriangleVertexArray);
                // TODO: TEMP RENDERING TEST END

                // call update on every layer (from bottom to top)
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate();

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
