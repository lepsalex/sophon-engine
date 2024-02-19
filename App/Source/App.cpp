#include <Sophon.h>

class ExampleLayer : public Sophon::Layer {
public:
    ExampleLayer()
        : Layer("Example")
        , m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
        , m_CameraPosition(0.0f, 0.0f, 0.0f)
        , m_CameraSpeed(2.0f)
    {
        // TODO: TEMP RENDERING TEST START
        m_TriangleVertexArray = Sophon::VertexArray::Create();
        float triangle_vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.9f, 0.4f, 0.4f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.4f, 0.9f, 0.4f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.4f, 0.4f, 0.9f, 1.0f, // clang-format-ignore
        };
        auto triangleVertexBuffer = Sophon::VertexBuffer::Create(triangle_vertices, sizeof(triangle_vertices));
        triangleVertexBuffer->SetLayout(Sophon::BufferLayout {
            { Sophon::BufferElement(Sophon::ShaderDataType::Float3, "a_Position") },
            { Sophon::BufferElement(Sophon::ShaderDataType::Float4, "a_Color") } });
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
        uint32_t triangleIndices[3] = { 0, 1, 2 };
        m_TriangleVertexArray->SetIndexBuffer(Sophon::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

        m_SquareVertexArray = Sophon::VertexArray::Create();
        float square_vertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f // clang-format-ignore
        };
        auto squareVertexBuffer = Sophon::VertexBuffer::Create(square_vertices, sizeof(square_vertices));
        squareVertexBuffer->SetLayout(Sophon::BufferLayout {
            { Sophon::BufferElement(Sophon::ShaderDataType::Float3, "a_Position") } });
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        m_SquareVertexArray->SetIndexBuffer(Sophon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
			    #version 330 core
			
			    layout(location = 0) in vec3 a_Position;
                layout(location = 1) in vec4 a_Color;

                uniform mat4 u_ViewProjection;
                uniform mat4 u_Transform;
			    
                out vec3 v_Position;
                out vec4 v_Color;
			    
                void main()
			    {
				    v_Position = a_Position;
                    v_Color = a_Color;
				    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

        m_Shader = Sophon::Shader::Create("Shader", vertexSrc, fragmentSrc);

        std::string simpleColorVertexSrc = R"(
			    #version 330 core
			
			    layout(location = 0) in vec3 a_Position;
			    
                uniform mat4 u_ViewProjection;
                uniform mat4 u_Transform;

                out vec3 v_Position;
			    
                void main()
			    {
				    v_Position = a_Position;
				    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

        m_SimpleColorShader = Sophon::Shader::Create("SimpleColorShader", simpleColorVertexSrc, simpleColorFragmentSrc);
        // TODO: TEMP RENDERING TEST END
    }

    void OnUpdate(Sophon::Timestep ts) override
    {
        // CAMERA MOVE TEST
        if (Sophon::Input::IsKeyPressed(Sophon::Key::Left))
            m_CameraPosition.x -= m_CameraSpeed * ts;

        if (Sophon::Input::IsKeyPressed(Sophon::Key::Right))
            m_CameraPosition.x += m_CameraSpeed * ts;

        if (Sophon::Input::IsKeyPressed(Sophon::Key::Up))
            m_CameraPosition.y += m_CameraSpeed * ts;

        if (Sophon::Input::IsKeyPressed(Sophon::Key::Down))
            m_CameraPosition.y -= m_CameraSpeed * ts;

        // TODO: TEMP RENDERING TEST START
        Sophon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Sophon::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);

        Sophon::Renderer::BeginScene(m_Camera);

        auto squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        // Draw 16 small squares
        for (int y = -8; y < 8; y++) {
            for (int x = -8; x < 8; x++) {
                // Setup transform
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                auto transform = glm::translate(glm::mat4(1.0f), pos) * squareScale;

                // Draw
                Sophon::Renderer::Submit(m_SimpleColorShader, m_SquareVertexArray, transform);
            }
        }

        // Draw the triangle on top
        Sophon::Renderer::Submit(m_Shader, m_TriangleVertexArray);

        Sophon::Renderer::EndScene();
        // TODO: TEMP RENDERING TEST END
    }

    void OnEvent(Sophon::Event& event) override
    {
    }

private:
    // TODO: TEMP RENDERING TEST START
    Sophon::Ref<Sophon::VertexArray> m_TriangleVertexArray;
    Sophon::Ref<Sophon::VertexArray> m_SquareVertexArray;
    Sophon::Ref<Sophon::Shader> m_Shader;
    Sophon::Ref<Sophon::Shader> m_SimpleColorShader;
    Sophon::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed;
    // TODO: TEMP RENDERING TEST END
};

class App : public Sophon::Application {
public:
    App()
    {
        PushLayer(new ExampleLayer());
    }

    ~App()
    {
    }
};

Sophon::Application* Sophon::CreateApplication()
{
    return new App();
}
