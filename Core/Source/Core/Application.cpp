#include "sfnpch.h"
#include "Application.h"

// TODO: TEMP RENDERING TEST
#include <glad/glad.h>

namespace Sophon {

    // TODO: Move to OpenGL Platorm
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type) {
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        }

        SFN_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

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
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.9f, 0.4f, 0.4f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.4f, 0.9f, 0.4f, 1.0f,
            0.0f, 0.5f, 0.0f,  0.4f, 0.4f, 0.9f, 1.0f,
        };

        m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        {
            // In scope to check ownership
            auto layout = BufferLayout {
                { BufferElement(ShaderDataType::Float3, "a_Position") },
                { BufferElement(ShaderDataType::Float4, "a_Color") }
            };

            m_VertexBuffer->SetLayout(layout);
        }

        const auto& layout = m_VertexBuffer->GetLayout();
        uint32_t index = 0;
        for (const auto& elem : layout) {
            glEnableVertexAttribArray(index);

            glVertexAttribPointer(
                index,
                elem.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(elem.Type),
                elem.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)elem.Offset);

            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

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

        m_Shader = CreateRef<OpenGLShader>("ApplicationTest", vertexSrc, fragmentSrc);
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
                glClearColor(0.1f, 0.1f, 0.1f, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                m_Shader->Bind();
                glBindVertexArray(m_VertexArray);
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

                /*
                 glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);*/
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
